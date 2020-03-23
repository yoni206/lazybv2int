#include "utils.h"

using namespace smt;
using namespace std;




string utils::pow2_str(uint64_t k)
{
  mpz_t base, p;
  mpz_inits(base, p, NULL);
  mpz_set_str(base, "2", 10);
  mpz_pow_ui(p, base, k);

  mpz_class res(p);

  mpz_clear(p);
  mpz_clear(base);

  return res.get_str();
}

utils::utils(SmtSolver& solver) : solver_(solver) {
  int_sort_ = solver_->make_sort(INT);
  Sort euclid_sort = solver_->make_sort(
      FUNCTION, SortVec{int_sort_, int_sort_, int_sort_ }
      );
  fintdiv_ = solver_->make_symbol("fint_div", euclid_sort);
  fintmod_ = solver_->make_symbol("fint_mod", euclid_sort);
  int_zero_ = solver_->make_term(0, int_sort_);
  int_one_ = solver_->make_term(1, int_sort_);
}


Term utils::pow2(uint64_t k) {
  string pow_bv_width_str = pow2_str(k);
  return solver_->make_term(pow_bv_width_str, int_sort_);
}


Term utils::gen_euclid(Term m, Term n) {
  TermVec div_args = {fintdiv_, m, n};
  TermVec mod_args = {fintmod_, m, n};
  Term q = solver_->make_term(Apply, div_args);
  Term r = solver_->make_term(Apply, mod_args);
  
  Term ne = solver_->make_term(Distinct, n, int_zero_);
  Term mul = solver_->make_term(Mult, n, q);
  Term plus = solver_->make_term(Plus, mul, r);
  Term eq = solver_->make_term(Equal, m, plus);
  Term le1 = solver_->make_term(Le, int_zero_, r);
  //we actually know n >= 0. All int terms are supposed to be.
  Term minus = solver_->make_term(Minus, n, int_one_);
  Term le2 = solver_->make_term(Le, r, minus);
  Term le3 = solver_->make_term(Le, int_zero_, q);
  Term le4 = solver_->make_term(Le, q, m);
  Term le = solver_->make_term(And, le1, le2);
  le = solver_->make_term(And, le, le3);
  le = solver_->make_term(And, le, le4);
  Term left = ne;
  Term right = solver_->make_term(And, eq, le); 
  Term res = solver_->make_term(Implies, left, right);
  return res;
}


Term utils::gen_intdiv(const Term &a, const Term &b, TermVec& side_effects)
{

  // this is specific intdiv
  // it assumes b to be positive
  if (b == int_one_) {
    return a;
  }
  TermVec args = { fintdiv_, a, b };
  Term res = solver_->make_term(Apply, args);
  Term euclid = gen_euclid(a,b);
  side_effects.push_back(euclid);
  return res;
}

Term utils::gen_mod(const Term &a, const Term &b, TermVec& side_effects)
{
  if (b == int_one_) {
    return int_zero_;
  }

  TermVec args = { fintmod_, a, b };
  Term res = solver_->make_term(Apply, args);
  Term euclid = gen_euclid(a,b);
  side_effects.push_back(euclid);
  
  return res;
}

