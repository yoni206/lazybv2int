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

static void get_fbv_args(Term f, uint64_t &bv_width, Term &a, Term &b)
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
  zero_ = solver_->make_term("0", int_sort_);
}

Axioms::~Axioms()
{
}

bool Axioms::check_bvand_base_case(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  if (bv_width == 1) {
    Term mul = solver_->make_term(Mult, a, b);
    Term l = make_eq(t, mul);
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > 0;
}

bool Axioms::check_bvand_minmax(Term t, bool is_max, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term r = is_max ? make_eq(t, a) : make_eq(t, zero_);
  if (!b->is_value()) {
    Term pre = is_max ? make_eq(b, pow2_minus_one(bv_width)) :
      make_eq(b, zero_);
    Term l = make_implies(pre, r);
    add_if_voilated(l, outlemmas);
  } else {
    uint64_t b_val = b->to_int();
    if (is_max && b_val == (pow(2, bv_width) - 1)) {
      add_if_voilated(r, outlemmas);
    } else if (!is_max && b_val == 0) {
      add_if_voilated(r, outlemmas);
    }
  }

  return outlemmas.size() > 0;
}

bool Axioms::check_bvand_idempotence(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term l = make_eq(t, a);
  if (a != b) {
    Term pre = make_eq(a, b);
    l = make_implies(pre, l);
  }

  add_if_voilated(l, outlemmas);

  return outlemmas.size() > 0;
}

bool Axioms::check_bvand_contradiction(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term not_b = solver_->make_term(Minus, pow2_minus_one(bv_width), b); 
  Term pre = make_eq(a, not_b);
  Term l = make_implies(pre, make_eq(t, zero_));
  add_if_voilated(l, outlemmas);

  return outlemmas.size() > 0;
}

bool Axioms::check_bvand_difference(Term t1, Term t2, TermVec &outlemmas)
{
  uint64_t bv_width1;
  Term a1, b1;
  get_fbv_args(t1, bv_width1, a1, b1);
  uint64_t bv_width2;
  Term a2, b2;
  get_fbv_args(t2, bv_width2, a2, b2);

  assert(bv_width1 == bv_width2);

  Term x, y, z; // same as in the paper
  if (a1 == a2) {
    z = a1;
    x = b1;
    y = b2;
  } else if (a1 == b2) {
    z = a1;
    x = b1;
    y = a2;
  } else if (b1 == a2) {
    z = b1;
    x = a1;
    y = b2;
  } else if (b1 == b2) {
    z = b1;
    x = a1;
    y = a2;
  } else {
    assert(false);
  }

  Term pre = make_neq(x, y);
  Term neq1 = make_neq(t1, y);
  Term neq2 = make_neq(t2, x);
  Term l = make_implies(pre, solver_->make_term(Or, neq1, neq2));

  add_if_voilated(l, outlemmas);

  return outlemmas.size() > 0;
}

bool Axioms::check_bvand_range(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  if (a == b) {
    return false;
  }

  Term l = solver_->make_term(Le, zero_, t);
  add_if_voilated(l, outlemmas);

  if (outlemmas.size() == 0) {
    Term pre = solver_->make_term(Le, a, b);
    l = make_implies(pre, solver_->make_term(Le, t, a));
    add_if_voilated(l, outlemmas);
  }

  if (outlemmas.size() == 0) {
    Term pre = solver_->make_term(Gt, a, b);
    l = make_implies(pre, solver_->make_term(Le, t, b));
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > 0;
}

bool Axioms::check_bvor_base_case(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  if (bv_width == 1) {
    Term p = solver_->make_term(Plus, a, b);
    Term l = make_eq(t, p);
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > 0;
}

bool Axioms::check_bvor_minmax(Term t, bool is_max, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term r = is_max ? make_eq(t, pow2_minus_one(bv_width))
    : make_eq(t, a);
  if (!b->is_value()) {
    Term pre = is_max ? make_eq(b, pow2_minus_one(bv_width)) :
      make_eq(b, zero_);
    Term l = make_implies(pre, r);
    add_if_voilated(l, outlemmas);
  } else {
    uint64_t b_val = b->to_int();
    if (is_max && b_val == (pow(2, bv_width) - 1)) {
      add_if_voilated(r, outlemmas);
    } else if (!is_max && b_val == 0) {
      add_if_voilated(r, outlemmas);
    }
  }

  return outlemmas.size() > 0;
}

bool Axioms::check_bvor_idempotence(Term t, TermVec &outlemmas)
{
  return check_bvand_idempotence(t, outlemmas);
}

bool Axioms::check_bvor_excluded_middle(smt::Term t, smt::TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term not_b = solver_->make_term(Minus, pow2_minus_one(bv_width), b); 
  Term pre = make_eq(a, not_b);
  Term l = make_implies(pre, make_eq(t, pow2_minus_one(bv_width)));
  add_if_voilated(l, outlemmas);

  return outlemmas.size() > 0;
}

bool Axioms::check_bvor_difference(Term t1, Term t2, TermVec &outlemmas)
{
  return check_bvand_difference(t1, t2, outlemmas);
}

bool Axioms::check_bvor_range(Term t, TermVec &outlemmas)
{
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  if (a == b) {
    return false;
  }

  Term pre = solver_->make_term(Le, a, b);
  Term l = make_implies(pre, solver_->make_term(Le, b, t));
  add_if_voilated(l, outlemmas);

  if (outlemmas.size() == 0) {
    pre = solver_->make_term(Gt, a, b);
    l = make_implies(pre, solver_->make_term(Le, a, t));
    add_if_voilated(l, outlemmas);
  }

  if (outlemmas.size() == 0) {
    l = solver_->make_term(Le, t, pow2_minus_one(bv_width));
    add_if_voilated(l, outlemmas);
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

inline Term Axioms::make_neq(Term x, Term y)
{
  return solver_->make_term(Not, make_eq(x, y));
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
