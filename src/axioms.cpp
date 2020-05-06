#include "axioms.h"

#include "utils.h"

#include <assert.h>
#include <gmpxx.h>
#include <math.h>

using namespace std;
using namespace smt;

namespace lbv2i {

static string pow2_minus_one_str(uint64_t k)
{
  mpz_t base, p;
  mpz_inits(base, p, NULL);
  mpz_set_str(base, "2", 10);
  mpz_pow_ui(p, base, k);

  mpz_class res(p);
  --res;

  mpz_clear(p);
  mpz_clear(base);

  return res.get_str();
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

Axioms::Axioms(SmtSolver & solver,
               const Term & fbvand)
    : solver_(solver), fbvand_(fbvand)
{
  int_sort_ = solver_->make_sort(INT);
  false_ = solver_->make_term(false);
  zero_ = solver_->make_term("0", int_sort_);
}

Axioms::~Axioms() {}

bool Axioms::check_bvand_symmetry(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  TermVec args = {fbvand_, solver_->make_term(bv_width, int_sort_), b, a};
  Term sym_t = solver_->make_term(Apply, args);
  Term l = make_eq(t, sym_t);
  add_if_voilated(l, outlemmas);

  return outlemmas.size() > n;
}

bool Axioms::check_bvand_base_case(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  if (bv_width == 1) {
    Term mul = solver_->make_term(Mult, a, b);
    Term l = make_eq(t, mul);
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > n;
}

bool Axioms::check_bvand_minmax(const Term & t,
                                bool is_max,
                                TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term r = is_max ? make_eq(t, a) : make_eq(t, zero_);
  if (!b->is_value()) {
    Term pre =
        is_max ? make_eq(b, pow2_minus_one(bv_width)) : make_eq(b, zero_);
    Term l = make_implies(pre, r);
    add_if_voilated(l, outlemmas);
  } else {
    if (is_max && b == pow2_minus_one(bv_width)) {
      add_if_voilated(r, outlemmas);
    } else if (!is_max && b == zero_) {
      add_if_voilated(r, outlemmas);
    }
  }

  return outlemmas.size() > n;
}

bool Axioms::check_bvand_idempotence(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term l = make_eq(t, a);
  if (a != b) {
    Term pre = make_eq(a, b);
    l = make_implies(pre, l);
  }

  add_if_voilated(l, outlemmas);

  return outlemmas.size() > n;
}

bool Axioms::check_bvand_contradiction(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  Term not_b = solver_->make_term(Minus, pow2_minus_one(bv_width), b);
  Term pre = make_eq(a, not_b);
  Term l = make_implies(pre, make_eq(t, zero_));
  add_if_voilated(l, outlemmas);

  return outlemmas.size() > n;
}

bool Axioms::check_bvand_difference(const Term & t1,
                                    const Term & t2,
                                    TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width1;
  Term a1, b1;
  get_fbv_args(t1, bv_width1, a1, b1);
  uint64_t bv_width2;
  Term a2, b2;
  get_fbv_args(t2, bv_width2, a2, b2);

  if (bv_width1 != bv_width2) {
    return false;
  }

  Term x, y, z;  // same as in the paper
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
    return false;
  }

  Term pre = make_neq(x, y);
  Term neq1 = make_neq(t1, y);
  Term neq2 = make_neq(t2, x);
  Term l = make_implies(pre, solver_->make_term(Or, neq1, neq2));

  add_if_voilated(l, outlemmas);

  return outlemmas.size() > n;
}

bool Axioms::check_bvand_range(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  if (a == b) {
    return false;
  }

  Term l = solver_->make_term(Le, zero_, t);
  add_if_voilated(l, outlemmas);

  if (outlemmas.size() == n) {
    l = solver_->make_term(Le, t, a);
    add_if_voilated(l, outlemmas);
  }

  if (outlemmas.size() == n) {
    l = solver_->make_term(Le, t, b);
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > n;
}

bool Axioms::check_bvand_bnw(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  // lemma1 would be preconditioned a - b >= 0
  // lemma2 would be preconditioned a - b < 0

  Term a_minus_b = solver_->make_term(Minus, a, b);
  Term b_minus_a = solver_->make_term(Minus, b, a);
  /*
      |
   UL | UR
  ____|____
      |   
   LL | LR
      |   
  */

  Term pow2_width_minus_one = solver_->make_term(utils::pow2_str(bv_width - 1),
                                                 int_sort_);
  Term UL = solver_->make_term(Lt, a, pow2_width_minus_one);
  UL = solver_->make_term(And, UL, 
                          solver_->make_term(Ge, b, pow2_width_minus_one));
  Term UR = solver_->make_term(Ge, a, pow2_width_minus_one);
  UR = solver_->make_term(And, UR,
                          solver_->make_term(Ge, b, pow2_width_minus_one));
  Term LR = solver_->make_term(Ge, a, pow2_width_minus_one);
  LR = solver_->make_term(And, LR,
                          solver_->make_term(Lt, b, pow2_width_minus_one));

  // black part: bvand(a, b) > |a - b|
  Term pre = solver_->make_term(And, UR,
                               solver_->make_term(Ge, a_minus_b, zero_));
  Term l = make_implies(pre, solver_->make_term(Gt, t, a_minus_b));
  add_if_voilated(l, outlemmas);

  // if the l was not add in outlemmas
  if (outlemmas.size() == n) {
    // (pre and a-b < 0) -> bvand(a,b) <= b - a
    pre = solver_->make_term(And, UR,
                             solver_->make_term(Lt, a_minus_b, zero_));
    l = make_implies(pre, solver_->make_term(Gt, t, b_minus_a));
    add_if_voilated(l, outlemmas);
  }

  // white part: bvand(a, b) <= |a - b|
  for (int i = 0; i < 2; ++i) {
    if (outlemmas.size() == n) {
      pre = solver_->make_term(And, i==0 ? LR : UL,
                               solver_->make_term(Ge, a_minus_b, zero_));
      l = make_implies(pre, solver_->make_term(Le, t, a_minus_b));
      add_if_voilated(l, outlemmas);
    }
    if (outlemmas.size() == n) {
      pre = solver_->make_term(And, i==0 ? LR : UL,
                               solver_->make_term(Lt, a_minus_b, zero_));
      l = make_implies(pre, solver_->make_term(Le, t, b_minus_a));
      add_if_voilated(l, outlemmas);
    }
  }

  return outlemmas.size() > n;
}

bool Axioms::check_bvlshift_range(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  // t >= 0
  Term l = solver_->make_term(Ge, t, zero_);
  add_if_voilated(l, outlemmas);

  if (outlemmas.size() == n) {
    // t <= 2^bitwidth - 1
    l = solver_->make_term(Le, t, pow2_minus_one(bv_width));
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > n;
}

bool Axioms::check_bvshift_zero(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  // b = 0 -> t = a
  Term b_eq_zero = make_eq(b, zero_);
  Term t_eq_a = make_eq(t, a);
  Term b_ge_width = solver_->make_term(Ge, b,
                                       solver_->make_term(to_string(bv_width),
                                                          int_sort_));
  Term l = make_implies(b_eq_zero, t_eq_a);
  add_if_voilated(l, outlemmas);

  if (outlemmas.size() == n) {
    // b >= bv_width -> t = 0
    l = make_implies(b_ge_width, make_eq(t, zero_));
    add_if_voilated(l, outlemmas);
  }

  if (outlemmas.size() == n) {
    // t = a /\ a > 0 -> b = 0
    Term pre = solver_->make_term(And, t_eq_a,
                                  solver_->make_term(Gt, a, zero_));
    l = make_implies(pre, b_eq_zero);
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > n;
}

bool Axioms::check_bvlshift_zero(const Term & t, TermVec & outlemmas)
{
  return check_bvshift_zero(t, outlemmas);
}

bool Axioms::check_bvrshift_range(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  // t <= x
  Term l = solver_->make_term(Le, t, a);
  add_if_voilated(l, outlemmas);

  if (outlemmas.size() == n) {
    check_bvlshift_range(t, outlemmas);
  }

  return outlemmas.size() > n;
}

bool Axioms::check_bvrshift_zero(const Term & t, TermVec & outlemmas)
{
  const size_t n = outlemmas.size();
  uint64_t bv_width;
  Term a, b;
  get_fbv_args(t, bv_width, a, b);

  // a <= b -> t = 0
  Term a_le_b = solver_->make_term(Le, a, b);
  Term t_eq_zero = make_eq(t, zero_);
  Term l = make_implies(a_le_b, t_eq_zero);
  add_if_voilated(l, outlemmas);

  if (outlemmas.size() == n) {
    check_bvshift_zero(t, outlemmas);
  }

  return outlemmas.size() > n;
}

inline Term Axioms::pow2_minus_one(uint64_t k)
{
  string p = pow2_minus_one_str(k);
  return solver_->make_term(p, int_sort_);
}

inline Term Axioms::make_eq(const Term & x, const Term & y)
{
  return solver_->make_term(Equal, x, y);
}

inline Term Axioms::make_neq(const Term & x, const Term & y)
{
  return solver_->make_term(Not, make_eq(x, y));
}

inline Term Axioms::make_implies(const Term & x, const Term & y)
{
  Term nx = solver_->make_term(Not, x);
  return solver_->make_term(Or, nx, y);
}

inline void Axioms::add_if_voilated(Term & l, TermVec & out)
{
  if (solver_->get_value(l) == false_) {
    out.push_back(l);
  }
}

}  // namespace lbv2i
