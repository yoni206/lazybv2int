#include "lbv2isolver.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <streambuf>

#include "msat/include/msat_term.h"

#include "smt-switch/cvc4_factory.h"
#include "smt-switch/msat_factory.h"

#include "opts.h"
#include "smtlibmsatparser.h"

using namespace smt;
using namespace std;

namespace lbv2i {

static void get_vars(Term term, TermVec & out)
{
  TermVec to_visit({ term });
  UnorderedTermSet visited;

  Term t;
  while (to_visit.size()) {
    t = to_visit.back();
    to_visit.pop_back();

    if (visited.find(t) == visited.end()) {
      visited.insert(t);

      if (t->is_symbolic_const()) {
        out.push_back(t);
      } else {// add children to queue
        for (auto tt : t) {
          to_visit.push_back(tt);
        }
      }
    }
  }
}


LBV2ISolver::LBV2ISolver(SmtSolver & solver, bool lazy)
    : bv2int_(new BV2Int(solver, false, lazy)),
      prepro_(new Preprocessor(solver)),
      postpro_(new Postprocessor(solver, &(bv2int_->get_utils()))),
      axioms_(
          solver, bv2int_->fbv_and(), bv2int_->fbv_or(), bv2int_->fbv_xor()),
      solver_(solver),
      tr_sat_checker_(sat_checker_),
      sat_checker_(NULL),
      lazy_(lazy)
{
  if (opts.print_values || opts.print_sigma_values || opts.lazy) {
    solver_->set_opt("produce-models", "true");
  }

  if (opts.solver == "cvc4") {
    sat_checker_ = CVC4SolverFactory::create();
  } else if (opts.solver == "msat") {
    sat_checker_ = MsatSolverFactory::create();
  }
}

LBV2ISolver::~LBV2ISolver()
{
  delete bv2int_;
  delete prepro_;
  delete postpro_;
}

Result LBV2ISolver::check_sat() { return solve(); }

Result LBV2ISolver::check_sat_assuming(const TermVec & assumptions)
{
  push();
  for (auto a : assumptions) {
    assert_formula(a);
  }
  Result r = solve();
  pop();
  return r;
}

Result LBV2ISolver::solve()
{
  do_assert_formula();

  if (!lazy_) {
    dump_smt2();
    return solver_->check_sat();
  }

  // lazy version
  TermVec lemmas;
  UnorderedTermSet seen;

  Result r = Result(ResultType::UNKNOWN);

  while (true) {
    r = solver_->check_sat();

    if (r.is_unsat()) {
      break;
    } else if (lazy_ && opts.sat_checker) {
      if (try_sat_check()) {
        return r;
      }
    }

    lemmas.clear();
    if (!refine(lemmas)) {
      if (bv2int_->fbv_terms().size() > 0 && !opts.full_refinement) {
        r = Result(ResultType::UNKNOWN, "Refinement Failure");
      }
      break;
    }

    for (auto l : lemmas) {
      //cout << "<--------> " << endl;
      //cout << "LAZY LEMMA : " << l << endl;
      if (seen.find(l) == seen.end()) {
        solver_->assert_formula(l);
        seen.insert(l);
      }
    }
  }
  dump_smt2();
  return r;
}

void LBV2ISolver::dump_smt2() {
  if (opts.dump) {
    if (opts.solver == "msat") {
      solver_->dump_smt2("tmp.solver.smt2");
    } else {
      cout << "no dumping with --cvc4, only with --msat." << endl;
    }
  }
}

void LBV2ISolver::set_logic(const string logic_name)
{
  solver_->set_logic(logic_name);
}

void LBV2ISolver::reset_assertions() { solver_->reset_assertions(); }

Term LBV2ISolver::make_term(bool b) const { return solver_->make_term(b); }

Term LBV2ISolver::make_term(int64_t i, const Sort & sort) const
{
  return solver_->make_term(i, sort);
}

Term LBV2ISolver::make_term(const Term & val, const Sort & sort) const
{
  return solver_->make_term(val, sort);
}

Term LBV2ISolver::make_term(const std::string val,
                            const Sort & sort,
                            uint64_t base) const
{
  return solver_->make_term(val, sort, base);
}

Term LBV2ISolver::make_term(const Op op, const TermVec & terms) const
{
  return solver_->make_term(op, terms);
}

Term LBV2ISolver::make_term(const Op op, const Term & t) const
{
  return solver_->make_term(op, t);
}

Term LBV2ISolver::make_term(const Op op, const Term & t0, const Term & t1) const
{
  return solver_->make_term(op, t0, t1);
}

Term LBV2ISolver::make_term(const Op op,
                            const Term & t0,
                            const Term & t1,
                            const Term & t2) const
{
  return solver_->make_term(op, t0, t1, t2);
}

Term LBV2ISolver::make_term(const string val, const Sort & sort, uint64_t base)
{
  return solver_->make_term(val, sort, base);
}

Term LBV2ISolver::make_symbol(const std::string name, const Sort & sort)
{
  return solver_->make_symbol(name, sort);
}

Sort LBV2ISolver::make_sort(const std::string name, uint64_t arity) const
{
  return solver_->make_sort(name, arity);
}

Sort LBV2ISolver::make_sort(const SortKind sk) const
{
  return solver_->make_sort(sk);
}

Sort LBV2ISolver::make_sort(const SortKind sk, uint64_t size) const
{
  return solver_->make_sort(sk, size);
}

Sort LBV2ISolver::make_sort(const SortKind sk, const Sort & sort1) const
{
  return solver_->make_sort(sk, sort1);
}

Sort LBV2ISolver::make_sort(const SortKind sk,
                            const Sort & sort1,
                            const Sort & sort2) const
{
  return solver_->make_sort(sk, sort1, sort2);
}

Sort LBV2ISolver::make_sort(const SortKind sk,
                            const Sort & sort1,
                            const Sort & sort2,
                            const Sort & sort3) const
{
  return solver_->make_sort(sk, sort1, sort2, sort3);
}

Sort LBV2ISolver::make_sort(const SortKind sk, const SortVec & sorts) const
{
  return solver_->make_sort(sk, sorts);
}

void LBV2ISolver::set_opt(string op, string value)
{
  solver_->set_opt(op, value);
}

Term LBV2ISolver::get_value(Term & t) const
{
  // Need to do this by translating back to bv...
  assert(false);
}

void LBV2ISolver::push(uint64_t num)
{
  do_assert_formula();

  for (size_t i = 0; i < num; i++) {
    bv2int_->push();
    stack_.push_back(stack_entry_t(orig_assertions_.size(), assertions_.size(),
                                   extra_assertions_.size()));
  }

  solver_->push(num);

  if (opts.lazy && opts.sat_checker) {
    sat_checker_->push(num);
  }
}

void LBV2ISolver::pop(uint64_t num)
{
  stack_entry_t e;

  for (size_t i = 0; i < num; i++) {
    bv2int_->pop();
    e = stack_.back();
    stack_.pop_back();
  }

  orig_assertions_.resize(std::get<0>(e));
  assertions_.resize(std::get<1>(e));
  extra_assertions_.resize(std::get<2>(e));

  solver_->pop(num);

  if (opts.lazy && opts.sat_checker) {
    sat_checker_->pop(num);
  }
}

void LBV2ISolver::reset()
{
  bv2int_->reset();
  solver_->reset();
  orig_assertions_.clear();
  assertions_.clear();
  extra_assertions_.clear();
  stack_.clear();
}

void LBV2ISolver::assert_formula(const Term & f)
{
  orig_assertions_.push_back(f);
}

void LBV2ISolver::do_assert_formula()
{
  Term f;
  if (stack_.size() == 0 || std::get<0>(stack_.back()) < orig_assertions_.size()) {
    size_t i = stack_.size() == 0 ? 0 : std::get<0>(stack_.back());
    f = orig_assertions_[i++];
    for (; i < orig_assertions_.size(); ++i) {
      f = solver_->make_term(And, f, orig_assertions_[i]);
    }

    // preprocess the formula
    Term pre_f = prepro_->process(f);

    if (opts.lazy && opts.sat_checker) {
      sat_checker_->assert_formula(tr_sat_checker_.transfer_term(pre_f));
    }
    // translate
    Term t_f = bv2int_->convert(pre_f);

    //postprocess
    //TODO this doesn't work currently, and requires more work and thinking. factoring out `mod` isn't trivial in the presense of side effects, and isn't useful unless terms like (a+b)+c are taken into account.
    //t_f = postpro_->process(t_f);
  
    //cout << t_f << endl;
    solver_->assert_formula(t_f);
    assertions_.push_back(t_f);

    // extra constraints
    UnorderedTermSet seen;
    const TermVec &extra_cons = bv2int_->get_extra_assertions();
    for (size_t i = extra_assertions_.size(); i < extra_cons.size(); ++i) {
      Term t = extra_cons[i];
      if (seen.find(t) == seen.end()) {
        //Term t_p = postpro_->process(t);
        solver_->assert_formula(t);
        seen.insert(t);
      } else {
        //cout << "skipping" << endl;
      }
      extra_assertions_.push_back(t);
    }
  }
}

bool LBV2ISolver::refine(TermVec & outlemmas)
{
  const TermVec & fbv_terms = bv2int_->fbv_terms();
  const Term & fbv_and = bv2int_->fbv_and();
  const Term & fbv_or = bv2int_->fbv_or();
  const Term & fbv_xor = bv2int_->fbv_xor();

  TermVec fbvand_terms, fbvor_terms, fbvxor_terms;
  for (Term f : fbv_terms) {
    // TODO: check for spurious terms
    Term fsymbol = *(f->begin());
    if (fsymbol == fbv_and) {
      fbvand_terms.push_back(f);
    } else if (fsymbol == fbv_or) {
      fbvor_terms.push_back(f);
    } else if (fsymbol == fbv_xor) {
      fbvxor_terms.push_back(f);
    } else {
      assert(false);
    }
  }

  bool ret = false;

  ret |= refine_bvand(fbvand_terms, outlemmas);
  ret |= refine_bvor(fbvor_terms, outlemmas);
  ret |= refine_bvxor(fbvxor_terms, outlemmas);

  return ret;
}

bool LBV2ISolver::refine_bvand(const TermVec & fterms, TermVec & outlemmas)
{
  size_t n = outlemmas.size();

  for (const Term & f : fterms) {
    bool found = axioms_.check_bvand_base_case(f, outlemmas);
    if (!found) {
      found = axioms_.check_bvand_range(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvand_idempotence(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvand_contradiction(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvand_minmax(f, false, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvand_minmax(f, true, outlemmas);
    }
  }

  if (outlemmas.size() == n) {
    const TermVec & fbv_terms = bv2int_->fbv_terms();
    const Term & fbv_and = bv2int_->fbv_and();

    TermVec all_fbvand_terms;
    for (const Term & f : fbv_terms) {
      Term fsymbol = *(f->begin());
      if (fsymbol == fbv_and) {
        all_fbvand_terms.push_back(f);
      }
    }

    for (const Term & f1 : fterms) {
      for (const Term & f2 : all_fbvand_terms) {
        if (f1 == f2) {
          continue;
        }
        bool found = axioms_.check_bvand_difference(f1, f2, outlemmas);
        if (found) {
          break;
        }
      }
    }
  }

  if (opts.full_refinement && outlemmas.size() == n) {
    refine_final(BVAnd, fterms, outlemmas);
  }

  return outlemmas.size() > n;
}

bool LBV2ISolver::refine_bvor(const TermVec & fterms, TermVec & outlemmas)
{
  size_t n = outlemmas.size();

  for (const Term & f : fterms) {
    bool found = axioms_.check_bvor_base_case(f, outlemmas);
    if (!found) {
      found = axioms_.check_bvor_range(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvor_idempotence(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvor_excluded_middle(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvor_minmax(f, false, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvor_minmax(f, true, outlemmas);
    }
  }

  if (outlemmas.size() == n) {
    const TermVec & fbv_terms = bv2int_->fbv_terms();
    const Term & fbv_or = bv2int_->fbv_and();

    TermVec all_fbvor_terms;
    for (const Term & f : fbv_terms) {
      Term fsymbol = *(f->begin());
      if (fsymbol == fbv_or) {
        all_fbvor_terms.push_back(f);
      }
    }

    for (const Term & f1 : fterms) {
      for (const Term & f2 : all_fbvor_terms) {
        if (f1 == f2) {
          continue;
        }
        bool found = axioms_.check_bvor_difference(f1, f2, outlemmas);
        if (found) {
          break;
        }
      }
    }
  }

  if (opts.full_refinement && outlemmas.size() == n) {
    refine_final(BVOr, fterms, outlemmas);
  }

  return outlemmas.size() > n;
}

bool LBV2ISolver::refine_bvxor(const TermVec & fterms, TermVec & outlemmas)
{
  size_t n = outlemmas.size();

  for (const Term & f : fterms) {
    bool found = axioms_.check_bvxor_base_case(f, outlemmas);
    if (!found) {
      found = axioms_.check_bvxor_zero(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvxor_one(f, outlemmas);
    }
    if (!found) {
      found = axioms_.check_bvxor_range(f, outlemmas);
    }
  }

  if (opts.full_refinement && outlemmas.size() == n) {
    refine_final(BVXor, fterms, outlemmas);
  }

  return outlemmas.size() > n;
}

static void get_fbv_args(const Term & f,
                         uint64_t & bv_width,
                         Term & a,
                         Term & b)
{
  TermIter it = f->begin();
  ++it;  // first child is the function name

  const Term & tmp = *it;
  assert(tmp->is_value());
  bv_width = tmp->to_int();

  ++it;
  a = *it;

  ++it;
  b = *it;
}

bool LBV2ISolver::refine_final(Op op, const TermVec &fterms, TermVec &outlemmas)
{
  size_t n = outlemmas.size();
  Term false_term = solver_->make_term(false);
  Sort int_sort = solver_->make_sort(INT);
  Term one = solver_->make_term("1", int_sort);
  utils & utils = bv2int_->get_utils();
  TermVec side_effects;

  for (const Term & f : fterms) {
    Term a, b;
    uint64_t bv_width;
    get_fbv_args(f, bv_width, a, b);

    if (opts.lazy_granularity == 0) {
      Term full_def = utils.gen_bw_sum(op,
                                       bv_width,
                                       bv2int_->granularity(),
                                       a,
                                       b,
                                       side_effects);
      Term l = solver_->make_term(Equal, f, full_def);
      Term se = solver_->make_term(true);
      for (auto t : side_effects) {
        se = solver_->make_term(And, se, t);
      }
      Term res = solver_->make_term(And, l, se);
      if (solver_->get_value(res) == false_term) {
        outlemmas.push_back(res);
      }

    } else if (opts.use_sum_bvops) {
      // TODO: optimize the loop below
      // TODO: cache the lemmas added in the last refinement

      uint64_t block_size = opts.lazy_granularity;
      if (block_size > bv_width) {
        block_size = bv_width;
      }
      while (bv_width % block_size != 0) {
        block_size = block_size - 1;
      }

      bool found = false;
      for (uint64_t k = block_size; k <= bv_width && !found; k += block_size) {
        // ((_ extract i j) a) is a / 2^j mod 2^{i-j+1}

        // lower bound
        side_effects.clear();
        uint64_t i = k;
        uint64_t j = 0;
        Term a_least_block = utils.gen_intdiv(a, utils.pow2(j), side_effects);
        a_least_block =
            utils.gen_mod(a_least_block, utils.pow2(i - j + 1), side_effects);
        Term b_least_block = utils.gen_intdiv(b, utils.pow2(j), side_effects);
        b_least_block =
            utils.gen_mod(b_least_block, utils.pow2(i - j + 1), side_effects);
        Term lower_bound = utils.gen_bw_sum(op,
                                            k,
                                            bv2int_->granularity(),
                                            a_least_block,
                                            b_least_block,
                                            side_effects);
        Term lower_lemma = solver_->make_term(Le, lower_bound, f);
        for (Term & t : side_effects) {
          lower_lemma = solver_->make_term(And, lower_lemma, t);
        }
        if (solver_->get_value(lower_lemma) == false_term) {
          outlemmas.push_back(lower_lemma);
          found = true;
        }

        // upper bound
        side_effects.clear();
        i = bv_width - 1;
        j = i - k + 1;
        Term a_most_block = utils.gen_intdiv(a, utils.pow2(j), side_effects);
        a_most_block =
            utils.gen_mod(a_most_block, utils.pow2(i - j + 1), side_effects);
        Term b_most_block = utils.gen_intdiv(b, utils.pow2(j), side_effects);
        b_most_block =
            utils.gen_mod(b_most_block, utils.pow2(i - j + 1), side_effects);
        Term upper_bound = utils.gen_bw_sum(op,
                                            k,
                                            bv2int_->granularity(),
                                            a_most_block,
                                            b_most_block,
                                            side_effects);
        uint64_t slack_width = bv_width - k;
        Term two_to_the_slack_width = utils.pow2(slack_width);
        Term slack =
            solver_->make_term(Minus, two_to_the_slack_width, one);
        //simulate concatenation -- a concat b = a*2^{k}+b, with
        //k=width(b)
        upper_bound = solver_->make_term(Mult, upper_bound, two_to_the_slack_width);
        upper_bound = solver_->make_term(Plus, upper_bound, slack);
        Term upper_lemma = solver_->make_term(Le, f, upper_bound);
        for (Term & t : side_effects) {
          upper_lemma = solver_->make_term(And, upper_lemma, t);
        }
        if (solver_->get_value(upper_lemma) == false_term) {
          outlemmas.push_back(upper_lemma);
          found = true;
        }
      }
    } else {
      // in the boolcomp bvops mode
      // each block of the UF representation and the integer version of the
      // applied op are equated e.g. fbvand(a, b)[0] = min(a[0], b[0])
      side_effects.clear();
      Term bvop_uf = utils.gen_bw(
          op, bv_width, bv2int_->granularity(), a, b, side_effects);
      for (auto ax : side_effects) {
        if (solver_->get_value(ax) == false_term) {
          outlemmas.push_back(ax);
        }
      }
    }
  }
  return outlemmas.size() > n;
}

void LBV2ISolver::run(string filename)
{
  ifstream file(filename);
  string smtlib((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
  // HACK keep the previously read smt-lib around
  // it seems like MathSAT sometimes complains when parsing files in pieces like this
  // this hack just re-reads the whole file again up to the current point
  // but it also removes old assertions so that they're not asserted twice
  // index zero contains processed smtlib, everything else is unprocessed
  // so before reading it, everything should be processed and appended to the
  // string in index 0
  vector<string> previous_smtlib;
  previous_smtlib.push_back("");

  // NOTE: not a perfect regex accepts (check-sat 2) but ignores the two
  //       shouldn't matter for our purposes
  regex re(
      "\\((push|pop|check-sat|check-sat-assuming)(\\s(\\d+|\\((.*)\\)\\s))?"
      "\\)");

  msat_config cfg = msat_create_config();
  msat_env env = msat_create_env(cfg);
  msat_destroy_config(cfg);

  TermTranslator tr(solver_);

  // Read input until a push/pop/check-sat/check-sat-assuming call
  while (smtlib.length()) {
    smatch match;
    if (regex_search(smtlib, match, re) && match.size() > 1) {
      msat_term msat_assertions =
          msat_from_smtlib2(env, smtlib.substr(0, match.position()).c_str());
      if (MSAT_ERROR_TERM(msat_assertions)) {
        // fallback on HACK by reading whole file up to this point (without commands)
        for (size_t i = 1; i < previous_smtlib.size(); ++i)
        {
          previous_smtlib[0] += remove_asserts(previous_smtlib[i]);
        }
        // remove all but the first element
        previous_smtlib.erase(++(previous_smtlib.begin()), previous_smtlib.end());
        string input = previous_smtlib[0] + smtlib.substr(0, match.position());
        msat_assertions = msat_from_smtlib2(env, input.c_str());
        if (MSAT_ERROR_TERM(msat_assertions))
        {
          cout << "Failed to read first part of smt-lib file:" << endl;
          // cout << smtlib.substr(0, match.position()) << endl;
          throw std::exception();
        }
      }
      Term mterm(new MsatTerm(env, msat_assertions));
      Term assertions = tr.transfer_term(mterm);
      assert_formula(assertions);

      // run command
      std::string command = match.str(1);
      if (command == "push") {
        size_t num = match.size() > 3 ? stoi(match.str(3)) : 1;
        push(num);
      } else if (command == "pop") {
        size_t num = match.size() > 3 ? stoi(match.str(3)) : 1;
        pop(num);
      } else if (command == "check-sat") {
        Result res = check_sat();
        print_result(res);
      } else if (command == "check-sat-assuming") {
        // split on whitespace
        istringstream buffer(match.str(4));
        vector<string> str_assumptions{ istream_iterator<string>(buffer),
                                        istream_iterator<string>() };
        TermVec assumptions;
        for (size_t i = 0; i < str_assumptions.size(); i++) {
          string str_term = str_assumptions[i];
          if (str_term == "(not") {
            if (i >= str_assumptions.size()) {
              cout << "unexpected end of text after '" << str_term
                   << "' in check-sat-assuming" << endl;
            }
            str_term += " " + str_assumptions[i + 1];
            i++;
          }
          msat_term m_assump = msat_from_string(env, str_term.c_str());
          if (MSAT_ERROR_TERM(m_assump)) {
            cout << "error parsing check-sat-assuming argument: " << str_term
                 << endl;
            throw std::exception();
          }
          Term mterm_assump(new MsatTerm(env, m_assump));
          assumptions.push_back(tr.transfer_term(mterm_assump));
        }

        Result res = check_sat_assuming(assumptions);
        print_result(res);
      } else {
        cout << "Unhandled command in smt-lib input" << endl;
        throw std::exception();
      }

      // save first part
      previous_smtlib.push_back(smtlib.substr(0, match.position()));

      // update string (remove up until past command)
      size_t start = match.position() + match.length();
      smtlib = smtlib.substr(start, smtlib.length() - start);
    }
    else
    {
      // no match
      // NOTE: might miss the last part of the file if there's no check-sat
      //       shouldn't matter
      smtlib = "";
    }
  }

  // Previous implementation: No incremental support
  // TermTranslator tr(solver_);
  // FILE * f = fopen(filename.c_str(), "r");
  // Term assert_term = parse_smt2(f, tr);
  // assert_formula(assert_term);
  // Result res = check_sat();
  // cout << res << endl;

  // if (res.is_sat()) {
  //   if (opts.print_values) {
  //     for (auto s : bv2int_->get_int_vars()) {
  //       cout << "\t" << s << " := " << solver_->get_value(s) << endl;
  //     }
  //   }
  //   if (opts.print_sigma_values) {
  //     for (auto s : bv2int_->get_extra_vars()) {
  //       cout << "\t" << s << " := " << solver_->get_value(s) << endl;
  //     }
  //   }
  // }
}

bool LBV2ISolver::try_sat_check()
{
  //cout << "SAT CHECKER" << endl;
  Term formula = solver_->make_term(true);
  for (auto &t : orig_assertions_) {
    formula = solver_->make_term(And, formula, t);
  }

  const UnorderedTermMap& map = bv2int_->get_cache();
  TermVec vars;
  get_vars(formula, vars);

  UnorderedTermSet filter_vars;
  if (opts.sat_checker_filter) {
    TermVec tmp_vars;
    for (auto &t : bv2int_->fbv_terms()) {
      get_vars(t, tmp_vars);
    }
    for (auto &v : tmp_vars) {
      filter_vars.insert(v);
    }
  }

  TermVec assumptions;
  utils & utils = bv2int_->get_utils();

  for (auto &v : vars) {
    Sort s = v->get_sort();
    SortKind sk = s->get_sort_kind();
    assert(map.find(v) != map.end());
    if (opts.sat_checker_filter &&
        filter_vars.find(map.at(v)) != filter_vars.end()) {
      //cout << "Dropping " << v << endl;
      continue;
    }
    if (sk == SortKind::BV && s->get_width() > opts.sat_checker_limit) {
      Term int_v = map.at(v);
      Term int_val = solver_->get_value(int_v);
      Term bv_val = utils.int_val_to_bv_val(int_val, s->get_width());
      Term v_eq_val = solver_->make_term(Equal, v, bv_val);
      assumptions.push_back(tr_sat_checker_.transfer_term(v_eq_val));
    }
  }

  sat_checker_->push();
  for (auto &a : assumptions) {
    //cout << a << endl;
    sat_checker_->assert_formula(a);
  }
  Result r = sat_checker_->check_sat();
  sat_checker_->pop();
  //  cout << "SAT CHECKER DONE" << endl;
  return r.is_sat();
}

void LBV2ISolver::print_result(Result res) const
{
  cout << res << endl;
  if (res.is_sat()) {
    if (opts.print_values) {
      for (auto s : bv2int_->get_int_vars()) {
        cout << "\t" << s << " := " << solver_->get_value(s) << endl;
      }
    }
  }
}

}  // namespace lbv2i
