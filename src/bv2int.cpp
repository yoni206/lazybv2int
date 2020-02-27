#include "bv2int.h"

#include <math.h>
#include <assert.h>

using namespace std;
using namespace smt;

namespace lbv2i {

static string pow2_str(uint64_t k)
{
  assert(k <= 64);
  assert(k >= 0);

  uint64_t p = pow(2, k);
  // make sure there is no overflow
  assert(p > 0);

  return to_string(p);
}

BV2Int::BV2Int(SmtSolver & solver, bool clear_cache) :
  super(solver, clear_cache)
{
  int_sort_ = solver->make_sort(INT);
}

BV2Int::~BV2Int() {}

WalkerStepResult BV2Int::visit_term(Term& term) {
  if (!preorder_) {
    Op op = term->get_op();
    if (!op.is_null()) {
      //term has children
      TermVec cached_children;
      for (auto t : term) {
        cached_children.push_back(cache_.at(t));
      }

      uint64_t bv_width = term->get_sort()->get_width();
      Term zero = solver_->make_term(string("0"), int_sort_);
      Term one = solver_->make_term(string("1"), int_sort_);
      if (op == BVAdd) { 
        string name = "sigma_" + to_string(sigma_vars_.size());
        Term sigma = solver_->make_symbol(name, int_sort_);
        Term plus = solver_->make_term(Plus, cached_children);
        Term multSig = solver_->make_term(Mult, sigma, pow2(bv_width));

        Term res = solver_->make_term(Minus, plus, multSig);

        range_assertions_.push_back(solver_->make_term(Ge, sigma, zero));
        range_assertions_.push_back(solver_->make_term(Le, sigma, one));
        range_assertions_.push_back(make_range_constraint(res, bv_width));

        cache_[term] = res;
      } else {
        assert(false);
      }
    
    }
  }
}

Term BV2Int::convert(Term t)
{
  visit_term(t);
  return cache_[t];
}

Term BV2Int::pow2(uint64_t k)
{
  string pow_bv_width_str = pow2_str(k);
  return solver_->make_term(pow_bv_width_str, int_sort_);
}
  
Term BV2Int::make_range_constraint(Term var, uint64_t bv_width)
{
  // returns 0<= var < 2^bv_width as a constraint
  Term zero = solver_->make_term("0", int_sort_);
  Term l = solver_->make_term(Le, zero, var);
  Term u = solver_->make_term(Lt, var, pow2(bv_width));
  return solver_->make_term(And, l, u);
}

}
