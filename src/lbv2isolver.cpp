#include "lbv2isolver.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <streambuf>

#include "msat/include/msat_term.h"

#include "opts.h"
#include "smtlibmsatparser.h"

using namespace smt;
using namespace std;

namespace lbv2i {

LBV2ISolver::LBV2ISolver(SmtSolver & solver, bool lazy)
    : bv2int_(new BV2Int(solver, true, lazy)),
      prepro_(new Preprocessor(solver)),
      axioms_(
          solver, bv2int_->fbv_and(), bv2int_->fbv_or(), bv2int_->fbv_xor()),
      solver_(solver),
      lazy_(lazy)
{
  if (opts.solver == "cvc4" &&
      (opts.print_values || opts.print_sigma_values || opts.lazy) ) {
    solver_->set_opt("produce-models", "true");
  }
}

LBV2ISolver::~LBV2ISolver()
{
  delete bv2int_;
  delete prepro_;
}

Result LBV2ISolver::check_sat() { return solve(); }

Result LBV2ISolver::check_sat_assuming(const TermVec & assumptions)
{
  push();
  for (auto a : assumptions) {
    assert_formula(a);
  }
  Result r = check_sat();
  pop();
  return r;
}

Result LBV2ISolver::solve()
{
  if (!lazy_) {
    return solver_->check_sat();
  }

  // lazy version
  TermVec lemmas;

  Result r = Result(ResultType::UNKNOWN);

  while (true) {
    r = solver_->check_sat();

    if (r.is_unsat()) {
      break;
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
      solver_->assert_formula(l);
    }
  }

  if (opts.solver == "msat") {
    FILE * f = fopen("tmp.smt2", "w");
    solver_->dump_smt2(f);
    fclose(f);
  }

  return r;
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
  for (size_t i = 0; i < num; i++) {
    bv2int_->push();
  }
  solver_->push(num);
}

void LBV2ISolver::pop(uint64_t num)
{
  for (size_t i = 0; i < num; i++) {
    bv2int_->pop();
  }
  solver_->pop(num);
}

void LBV2ISolver::reset() { solver_->reset(); }

void LBV2ISolver::assert_formula(const Term & f) const
{
  // preprocess the formula
  Term pre_f = prepro_->process(f);

  // translate
  Term t_f = bv2int_->convert(pre_f);
  //cout << t_f << endl;
  solver_->assert_formula(t_f);
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
      Term full_def = utils.gen_bw(
          op, bv_width, bv2int_->granularity(), a, b, side_effects);
      Term l = solver_->make_term(Equal, f, full_def);
      Term se = solver_->make_term(true);
      for (auto t : side_effects) {
        se = solver_->make_term(And, se, t);
      }
      Term res = solver_->make_term(And, l, se);
      if (solver_->get_value(res) == false_term) {
        outlemmas.push_back(res);
      }

    } else {
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
        Term lower_bound = utils.gen_bw(op,
                                        block_size,
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
        Term upper_bound = utils.gen_bw(op,
                                        block_size,
                                        bv2int_->granularity(),
                                        a_most_block,
                                        b_most_block,
                                        side_effects);

        Term slack =
            solver_->make_term(Minus, utils.pow2(bv_width - block_size), one);
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
    }
  }

  return outlemmas.size() > n;
}

void LBV2ISolver::run(string filename)
{
  ifstream file(filename);
  string smtlib((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

  regex re(
      "\\((push|pop)(\\s(\\d+))?\\)|\\((check-sat)\\)|\\((check-sat-assuming) "
      "\\((.*)\\)\\)");
  vector<Result> results;

  msat_config cfg = msat_create_config();
  msat_env env = msat_create_env(cfg);

  SmtSolver self_solver(this);
  TermTranslator tr(self_solver);

  // Read input until a push/pop/check-sat/check-sat-assuming call
  while (smtlib.length()) {
    smatch match;
    if (regex_search(smtlib, match, re) && match.size() > 1) {
      msat_term msat_assertions =
          msat_from_smtlib2(env, smtlib.substr(0, match.position()).c_str());
      Term mterm(new MsatTerm(env, msat_assertions));
      Term assertions = tr.transfer_term(mterm);
      assert_formula(assertions);

      // run command
      std::string command = match.str(1);
      cout << "got command: " << command << endl;
      if (command == "push") {
        size_t num = match.size() > 3 ? stoi(match.str(3)) : 1;
        push(num);
      } else if (command == "pop") {
        size_t num = match.size() > 3 ? stoi(match.str(3)) : 1;
        pop(num);
      } else if (command == "check-sat") {
        Result res = check_sat();
        results.push_back(res);
        if (res.is_sat()) {
          if (opts.print_values) {
            for (auto s : bv2int_->get_int_vars()) {
              cout << "\t" << s << " := " << solver_->get_value(s) << endl;
            }
          }
          if (opts.print_sigma_values) {
            for (auto s : bv2int_->get_extra_vars()) {
              cout << "\t" << s << " := " << solver_->get_value(s) << endl;
            }
          }
        }
      } else if (command == "check-sat-assuming") {
        cout << "Parser doesn't handle check-sat-assuming yet" << endl;
        throw std::exception();
      } else {
        cout << "Unhandled command in smt-lib input" << endl;
        throw std::exception();
      }

      // update string (remove up until past command)
      size_t start = match.position() + match.length();
      smtlib = smtlib.substr(start, smtlib.length() - start);
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

}  // namespace lbv2i
