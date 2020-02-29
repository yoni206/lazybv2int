#include "axioms.h"

#include <math.h>
#include <assert.h>

using namespace std;
using namespace smt;

namespace lbv2i {

static string pow2_minus_one_str(uint64_t k)
{
  assert(k <= 64);
  assert(k >= 0);
 
  uint64_t p = pow(2, k);
  // make sure there is no overflow
  assert(p > 0);

  return to_string(p);
}

static void get_fbvand_args(Term f, uint64_t &bv_width, Term &a, Term &b)
{
  TermIter it = f->begin();
  Term tmp = *it;

  assert(tmp->is_value());
  bv_width = tmp->to_int();
  ++it;

  a = *it;
  ++it;
  b = *it;
}

Axioms::Axioms(SmtSolver & solver) :
  solver_(solver)
{
  int_sort_ = solver_->make_sort(INT);
  false_ = solver_->make_term(false);
}

Axioms::~Axioms()
{
}

bool Axioms::check_bvand_base_case(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbvand_args(t, bv_width, a, b);

  if (bv_width == 1) {
    Term mul = solver_->make_term(Mult, a, b);
    Term l = make_eq(t, mul);
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > 0;
}

bool Axioms::check_bvand_max(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbvand_args(t, bv_width, a, b);

  Term r = make_eq(t, a);
  if (!b->is_value()) {
    Term pre = make_eq(b, pow2_minus_one(bv_width));
    Term l = make_implies(pre, r);
    add_if_voilated(l, outlemmas);
  } else {
    uint64_t b_val = b->to_int();
    if (b_val == (pow(2, bv_width) - 1)) {
      add_if_voilated(r, outlemmas);
    }
  }

  return outlemmas.size() > 0;
}

inline Term Axioms::pow2_minus_one(uint64_t k)
{
  string p = pow2_minus_one_str(k);
  return solver_->make_term(p, int_sort_);
}

inline Term Axioms::make_eq(Term x, Term y)
{
  return solver_->make_term(Equal, x, y);
}

inline Term Axioms::make_implies(Term x, Term y)
{
  Term nx = solver_->make_term(Not, x);
  return solver_->make_term(Or, nx, y);
}

inline void Axioms::add_if_voilated(Term l, TermVec &out)
{
  if (solver_->get_value(l) == false_) {
    out.push_back(l);
  }
}

} // namespace lbv2i
