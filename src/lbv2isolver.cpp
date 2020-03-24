#include "lbv2isolver.h"

#include <assert.h>

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
  for (const Term & f : fterms) {
    Term a, b;
    uint64_t bv_width;
    get_fbv_args(f, bv_width, a, b);

    TermVec children = {a, b};
    Term full_def = bv2int_->get_explicit_bw(op, bv_width, children);
    Term l = solver_->make_term(Equal, f, full_def);
    if (solver_->get_value(l) == false_term) {
      outlemmas.push_back(l);
    }
  }

  return outlemmas.size() > n;
}

void LBV2ISolver::run(string filename)
{
  TermTranslator tr(solver_);
  FILE * f = fopen(filename.c_str(), "r");
  Term assert_term = parse_smt2(f, tr);
  assert_formula(assert_term);
  Result res = check_sat();
  cout << res << endl;

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
}

}  // namespace lbv2i
