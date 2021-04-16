#include "lbv2isolver.h"

#include <assert.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <streambuf>

#include "opts.h"
#include "smt-switch/boolector_factory.h"
#include "smt-switch/cvc4_factory.h"
#include "smt-switch/msat_factory.h"
#include "smt-switch/msat_term.h"
#include "smt-switch/solver_enums.h"
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


LBV2ISolver::LBV2ISolver(SmtSolver & solver, bool lazy)
    : bv2int_(new BV2Int(solver, false, lazy)),
      prepro_(new Preprocessor(solver)),
      postpro_(new Postprocessor(solver, &(bv2int_->get_utils()))),
      axioms_(
          solver, bv2int_->fbv_and()),
      solver_(solver),
      tr_s_checker_(s_checker_),
      s_checker_(NULL),
      lazy_(lazy),
      AbsSmtSolver(opts.solver=="CVC4" ? CVC4 : MSAT)
{
  last_asserted_size_ = 0;
  if (opts.print_values || opts.print_sigma_values || opts.lazy) {
    solver_->set_opt("produce-models", "true");
  }

  // create MathSAT Solver without a shadow DAG (e.g. LoggingSolver wrapper)
  s_checker_ = MsatSolverFactory::create(false);
  s_checker_->set_opt("produce-unsat-cores", "true");
  s_checker_base_assump_ = s_checker_->make_symbol("s_checker_base_assump",
                                                   s_checker_->make_sort(BOOL));
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
  for (auto &a : assumptions) {
    assert_formula(a);
  }
  Result r = solve();
  pop();
  return r;
}

void LBV2ISolver::get_unsat_assumptions(UnorderedTermSet & core)
{
  solver_->get_unsat_assumptions(core);
}

Term LBV2ISolver::substitute(const Term term,
                const UnorderedTermMap & substitution_map) const
{
  return solver_->substitute(term, substitution_map);
}

Result LBV2ISolver::solve()
{
  do_assert_formula();

  if (!lazy_) {
    dump_smt2();
    return solver_->check_sat();
  }

  // lazy version
  TermVec lemmas, tmp;
  UnorderedTermSet seen;

  Result r = Result(ResultType::UNKNOWN);

  while (true) {
    lemmas.clear();

    r = solver_->check_sat();

    if (r.is_unsat()) {
      break;
    } else if (lazy_ && opts.s_checker) {
      if (try_sat_check(lemmas)) {
        return r;
      }
    }

    if (!refine(lemmas)) {
      if (bv2int_->fbv_terms().size() > 0 && !opts.full_refinement) {
        r = Result(ResultType::UNKNOWN, "Refinement Failure");
      }
      break;
    }


    for (auto &l : lemmas) {
      //cout << "<--------> " << endl;
      tmp.clear();
      utils::conjunctive_partition(l, tmp);
      //cout << tmp.size() << endl;
      for (auto &c : tmp) {
        if (seen.find(c) == seen.end()) {
          //cout << "LAZY LEMMA : " << c << endl;
          solver_->assert_formula(c);
          seen.insert(c);
        } else {
          //cout << "Skipping : " << c << endl;
        }
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

Term LBV2ISolver::make_param(const string name, const Sort & sort)
{
  throw SmtException("LBV2ISolver does not support quantifiers");
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

Sort LBV2ISolver::make_sort(const Sort & sort_con, const SortVec & sorts) const
{
  return solver_->make_sort(sort_con, sorts);
}

void LBV2ISolver::set_opt(string op, string value)
{
  solver_->set_opt(op, value);
}

Term LBV2ISolver::get_value(const Term & t) const
{
  // handle special case of booleans
  // useful for cosa
  if (t->get_sort()->get_sort_kind() == BOOL)
  {
    Term pre_t = prepro_->process(t);
    Term final_t = bv2int_->convert(pre_t);
    return solver_->get_value(final_t);
  }
  // Need to do this by translating back to bv...
  assert(false);
}

UnorderedTermMap LBV2ISolver::get_array_values(const Term & arr,
                                               Term & out_const_base) const
{
  throw NotImplementedException("Does not support getting array values.");
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

  if (opts.lazy && opts.s_checker) {
    s_checker_->push(num);
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
  if (last_asserted_size_ > orig_assertions_.size()) {
    last_asserted_size_ = orig_assertions_.size();
  }

  solver_->pop(num);

  if (opts.lazy && opts.s_checker) {
    s_checker_->pop(num);
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
  last_asserted_size_ = 0;
}

void LBV2ISolver::assert_formula(const Term & f)
{
  orig_assertions_.push_back(f);
}

void LBV2ISolver::do_assert_formula()
{
  Term f;
  if (last_asserted_size_ < orig_assertions_.size()) {
    f = solver_->make_term(true);
    for (size_t i = last_asserted_size_; i < orig_assertions_.size(); ++i) {
      f = solver_->make_term(And, f, orig_assertions_[i]);
      if (opts.lazy && opts.s_checker) {
        Term t = s_checker_->make_term(Implies, s_checker_base_assump_,
                                       tr_s_checker_.transfer_term(orig_assertions_[i]));
        s_checker_->assert_formula(t);
      }
    }

    // preprocess the formula
    Term pre_f = prepro_->process(f);

    // translate
    Term t_f = bv2int_->convert(pre_f);

    //postprocess
    //TODO this doesn't work currently, and requires more work and thinking. factoring out `mod` isn't trivial in the presense of side effects, and isn't useful unless terms like (a+b)+c are taken into account.
    //t_f = postpro_->process(t_f);

    //cout << t_f << endl;
    solver_->assert_formula(t_f);
    assertions_.push_back(t_f);
    last_asserted_size_ = orig_assertions_.size();

    // extra constraints
    UnorderedTermSet seen;
    TermVec tmp;
    const TermVec &extra_cons = bv2int_->get_extra_assertions();
    for (size_t i = extra_assertions_.size(); i < extra_cons.size(); ++i) {
      tmp.clear();
      utils::conjunctive_partition(extra_cons[i], tmp);
      for (auto &t : tmp) {
        if (seen.find(t) == seen.end()) {
          //Term t_p = postpro_->process(t);
          solver_->assert_formula(t);
          seen.insert(t);
        } else {
          //cout << "skipping" << endl;
        }
      }
      extra_assertions_.push_back(extra_cons[i]);
    }
  }
}

bool LBV2ISolver::refine(TermVec & outlemmas)
{
  const TermVec & fbv_terms = bv2int_->fbv_terms();
  const Term & fbv_and = bv2int_->fbv_and();
  const Term & fbv_lshift = bv2int_->fbv_lshift();
  const Term & fbv_rshift = bv2int_->fbv_rshift();

  UnorderedTermSet seen;
  TermVec fbvand_terms;
  TermVec fbvlshift_terms;
  TermVec fbvrshift_terms;
  for (Term f : fbv_terms) {
    if (seen.find(f) != seen.end()) {
      continue;
    }
    seen.insert(f);
    // TODO: check for spurious terms
    Term fsymbol = *(f->begin());
    if (fsymbol == fbv_and) {
      fbvand_terms.push_back(f);
    } else if (fsymbol == fbv_lshift) {
      fbvlshift_terms.push_back(f);
    } else if (fsymbol == fbv_rshift) {
      fbvrshift_terms.push_back(f);
    } else {
      assert(false);
    }
  }

  bool ret = false;

  ret |= refine_bvand(fbvand_terms, outlemmas);
  ret |= refine_bvlshift(fbvlshift_terms, outlemmas);
  ret |= refine_bvrshift(fbvrshift_terms, outlemmas);

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
      found = axioms_.check_bvand_symmetry(f, outlemmas);
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
    if (!found) {
      found = axioms_.check_bvand_bnw(f, outlemmas);
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
    refine_final_bw(BVAnd, fterms, outlemmas);
  }

  return outlemmas.size() > n;
}

void LBV2ISolver::refine_final_shift(const TermVec & fterms, TermVec & outlemmas)
{
  Term false_term = solver_->make_term(false);
  utils & utils = bv2int_->get_utils();
  for (auto & f : fterms) {
    Term f_sym = *(f->begin());
    Term a, b;
    uint64_t bv_width;
    get_fbv_args(f, bv_width, a, b);

    TermVec side_effects;
    Term b_val = solver_->get_value(b);
    string b_val_str = b_val->to_string();
    if (utils.compare(b_val_str, bv_width) < 0) {
      uint64_t b_int = strtoul(b_val_str.c_str(), NULL, 10);
      Term two_pow_b = utils.pow2(b_int);
      Term div_mul_term;
      if (f_sym == bv2int_->fbv_lshift()) {
        div_mul_term = utils.gen_mod(solver_->make_term(Mult, a, two_pow_b), utils.pow2(bv_width), side_effects);
      } else {
        assert(f_sym == bv2int_->fbv_rshift());
        div_mul_term = utils.gen_intdiv(a, two_pow_b, side_effects);
      }

      Term b_eq_bval = solver_->make_term(Equal, b, b_val);
      Term lemma = solver_->make_term(Implies, b_eq_bval,
                                      solver_->make_term(Equal, f,
                                                         div_mul_term));
      side_effects.push_back(lemma);
      for (auto &l : side_effects) {
        if (solver_->get_value(l) == false_term) {
          outlemmas.push_back(l);
        }
      }
    }
  }
}

bool LBV2ISolver::refine_bvlshift(const TermVec & fterms, TermVec & outlemmas)
{
  size_t n = outlemmas.size();

  for (const Term & f : fterms) {
    bool found = axioms_.check_bvlshift_range(f, outlemmas);
    if (!found) {
      found = axioms_.check_bvlshift_zero(f, outlemmas);
    }
  }

  if (opts.full_refinement && outlemmas.size() == n) {
    refine_final_shift(fterms, outlemmas);
  }

  return outlemmas.size() > n;
}

bool LBV2ISolver::refine_bvrshift(const TermVec & fterms, TermVec & outlemmas)
{
  size_t n = outlemmas.size();

  for (const Term & f : fterms) {
    bool found = axioms_.check_bvrshift_range(f, outlemmas);
    if (!found) {
      found = axioms_.check_bvrshift_zero(f, outlemmas);
    }
  }

  if (opts.full_refinement && outlemmas.size() == n) {
    refine_final_shift(fterms, outlemmas);
  }

  return outlemmas.size() > n;
}

bool LBV2ISolver::refine_final_bw(Op op, const TermVec &fterms, TermVec &outlemmas)
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
      for (auto &t : side_effects) {
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
      for (auto &ax : side_effects) {
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

void LBV2ISolver::run_on_stdin()
{
  // This is a quick implementation for running on stdin
  // it copies most of the code from run
  // TODO: refactor these methods to avoid repeated code

  // HACK keep the previously read smt-lib around
  // it seems like MathSAT sometimes complains when parsing files in pieces like
  // this this hack just re-reads the whole file again up to the current point
  // but it also removes old assertions so that they're not asserted twice
  // index zero contains processed smtlib, everything else is unprocessed
  // so before reading it, everything should be processed and appended to the
  // string in index 0
  vector<string> previous_smtlib;
  previous_smtlib.push_back("");

  // NOTE: not a perfect regex accepts (check-sat 2) but ignores the two
  //       shouldn't matter for our purposes
  regex re(
      "\\((push|pop|check-sat|exit|check-sat-assuming|set-option\\s:print-"
      "success\\strue)(\\s(\\d+|\\((.*)\\)\\s))"
      "?"
      "\\)");

  msat_config cfg = msat_create_config();
  msat_env env = msat_create_env(cfg);
  msat_destroy_config(cfg);

  TermTranslator tr(solver_);

  // gets set to true by (set-option :print-success true)
  bool print_success = false;

  // Read input until a push/pop/check-sat/check-sat-assuming call
  SExprBuffer seb;

  // store all the input in smtlib
  string smtlib = "";
  for (std::string input_line; std::getline(std::cin, input_line);) {
    seb.add_string(input_line);
    if (seb.any_new_commands()) {
      string command;
      for (auto c : seb.get_commands()) {
        smatch match;
        command = "";
        if (regex_search(c, match, re) && match.size() > 1) {
          msat_term msat_assertions = msat_from_smtlib2(env, smtlib.c_str());
          if (MSAT_ERROR_TERM(msat_assertions)) {
            // fallback on HACK by reading whole file up to this point (without
            // commands)
            for (size_t i = 1; i < previous_smtlib.size(); ++i) {
              previous_smtlib[0] += remove_asserts(previous_smtlib[i]);
            }
            // remove all but the first element
            previous_smtlib.erase(++(previous_smtlib.begin()),
                                  previous_smtlib.end());
            string input =
              previous_smtlib[0] + "\n" + smtlib;
            msat_assertions = msat_from_smtlib2(env, input.c_str());
            if (MSAT_ERROR_TERM(msat_assertions)) {
              cout << "Failed to read first part of smt-lib file:" << endl;
              throw std::exception();
            }
          }

          Term mterm(new MsatTerm(env, msat_assertions));
          Term assertions = tr.transfer_term(mterm);
          assert_formula(assertions);

          // run command
          command = match.str(1);
          if (command == "push") {
            size_t num = match.size() > 3 ? stoi(match.str(3)) : 1;
            push(num);
          } else if (command == "pop") {
            size_t num = match.size() > 3 ? stoi(match.str(3)) : 1;
            pop(num);
          } else if (command == "exit") {
            return;
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
                cout << "error parsing check-sat-assuming argument: "
                     << str_term << endl;
                throw std::exception();
              }
              Term mterm_assump(new MsatTerm(env, m_assump));
              assumptions.push_back(tr.transfer_term(mterm_assump));
            }

            Result res = check_sat_assuming(assumptions);
            print_result(res);
          } else if (command.find(":print-success") != std::string::npos) {
            print_success = true;
          } else {
            cout << "Unhandled command in smt-lib input" << endl;
            throw std::exception();
          }

          // save smtlib in case needed for the fallback HACK -- mathsat parse
          // failure
          previous_smtlib.push_back(smtlib);

          // now clear smtlib
          smtlib = "";

        } else {
          // if not one of the commands processed at lbv2isolver level,
          // just append to smtlib
          smtlib += c;
          smtlib += "\n";
        }

        if (print_success && command != "check-sat"
            && command != "check-sat-assuming") {
          std::cout << "success" << std::endl;
        }
      }

      // clear the commands in the buffer
      seb.clear_commands();
    }
  }
}

bool LBV2ISolver::try_sat_check(TermVec &outlemmas)
{
  const TermVec &fterms = bv2int_->fbv_terms();
  if (fterms.size() == 0) {
    return false;
  }

  //cout << "SAT CHECKER" << endl;
  Term formula = solver_->make_term(true);
  for (auto &t : orig_assertions_) {
    formula = solver_->make_term(And, formula, t);
  }

  const UnorderedTermMap& map = bv2int_->get_cache();
  TermVec vars;
  get_vars(formula, vars);

  UnorderedTermSet filter_vars;
  if (opts.s_checker_filter) {
    TermVec tmp_vars;
    for (auto &t : fterms) {
      get_vars(t, tmp_vars);
    }
    for (auto &v : tmp_vars) {
      filter_vars.insert(v);
    }
  }

  TermVec assumptions, orig_assump, bool_assump;
  utils & utils = bv2int_->get_utils();

  for (auto &v : vars) {
    Sort s = v->get_sort();
    SortKind sk = s->get_sort_kind();

    if (map.find(v) == map.end()) {
      continue;
    }
    if (opts.s_checker_filter &&
        filter_vars.find(map.at(v)) != filter_vars.end()) {
      //cout << "Dropping " << v << endl;
      continue;
    }

    if (sk == SortKind::BV && s->get_width() > opts.s_checker_limit) {
      Term int_v = map.at(v);
      Term int_val = solver_->get_value(int_v);
      Term bv_val = utils.int_val_to_bv_val(int_val, s->get_width());
      Term v_eq_val = solver_->make_term(Equal, v, bv_val);
      //cout << v_eq_val << endl;
      assumptions.push_back(tr_s_checker_.transfer_term(v_eq_val));
      orig_assump.push_back(solver_->make_term(Equal, int_v, int_val));
    }
  }

  assert(assumptions.size() == orig_assump.size());

  s_checker_->push();
  for (auto &a : assumptions) {
    //cout << a << endl;
    unsigned i = 0;

    Term b;
    while(true) {
      try {
        b = s_checker_->make_symbol("assump_" + to_string(a->hash()) + "_" + to_string(i),
                                      s_checker_->make_sort(BOOL));
        break;
      } catch (IncorrectUsageException & e){
        ++i;
      } catch (SmtException & e) {
        throw e;
      }
    }
    bool_assump.push_back(b);
    s_checker_->assert_formula(s_checker_->make_term(Implies, b, a));
  }

  // adding base assumption as the last element
  bool_assump.push_back(s_checker_base_assump_);

  Result r = s_checker_->check_sat_assuming(bool_assump);
  bool lemma_failed = false;
  //cout << bool_assump.size() << endl;
  if (r.is_unsat()) {
    Term lemma = solver_->make_term(false);
    if (bool_assump.size() > 0) {
      try {
        UnorderedTermSet core_set;
        s_checker_->get_unsat_assumptions(core_set);

        assert(orig_assump.size() == bool_assump.size());

        for (size_t j = 0; j+1 < bool_assump.size(); ++j) {
          // skipping last element
          if (core_set.find(bool_assump[j]) != core_set.end()) {
            lemma = solver_->make_term(Or, lemma,
                                     solver_->make_term(Not, orig_assump[j]));
          }
        }
      } catch (...) {
        lemma_failed = true;
      }
    }

    if (!lemma_failed) {
      outlemmas.push_back(lemma);
      //cout << lemma << endl;
    }
  }

  s_checker_->pop();
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
