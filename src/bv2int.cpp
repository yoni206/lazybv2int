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

static bool is_simple_op(Op op)
{
  vector<Op> simple_op =
    {And, Or, Xor, Not, Implies, Iff, Ite, Equal, Distinct, Plus, Minus,
     Negate, Mult, Div, Lt, Le, Gt, Ge, Mod, Abs, Pow, To_Real};
  for (auto o : simple_op) {
    if (o == op) {
      return true;
    }
  }
  return false;
}

BV2Int::BV2Int(SmtSolver & solver, bool clear_cache, bool abstract) :
  super(solver, clear_cache),
  abstract_(abstract)
{
  int_sort_ = solver_->make_sort(INT);
  fbvand_sort_ =
    solver_->make_sort(FUNCTION,
                       SortVec{int_sort_, int_sort_, int_sort_, int_sort_});
  int_zero_ = solver_->make_term(0, int_sort_);
  granularity_ = 1;
}

BV2Int::~BV2Int() {}

void BV2Int::push()
{
  stack_.push_back(stack_entry_t(cache_,
                                 range_assertions_.size(),
                                 sigma_vars_.size()));
}

void BV2Int::pop()
{
  stack_entry_t e = stack_.back();
  cache_ = std::get<0>(e);
  range_assertions_.resize(std::get<1>(e));
  sigma_vars_.resize(std::get<2>(e));
  stack_.pop_back();
}

WalkerStepResult BV2Int::visit_term(Term& t) {
  if (!preorder_) {
    Op op = t->get_op();
    if (!op.is_null()) {
      //term has children
      TermVec cached_children;
      for (auto c : t) {
        cached_children.push_back(cache_.at(c));
      }

      Term zero = solver_->make_term(string("0"), int_sort_);
      Term one = solver_->make_term(string("1"), int_sort_);

      std::cout << "visiting operator: " << op.to_string() << std::endl;

      if (is_simple_op(op)) {
        cache_[t] = solver_->make_term(op, cached_children);
      } 

      else if (op == BVAdd) {
        uint64_t bv_width = t->get_sort()->get_width();
        string name = "sigma_" + to_string(sigma_vars_.size());
        Term sigma = solver_->make_symbol(name, int_sort_);
        Term plus = solver_->make_term(Plus, cached_children);
        Term multSig = solver_->make_term(Mult, sigma, pow2(bv_width));

        Term res = solver_->make_term(Minus, plus, multSig);

        range_assertions_.push_back(make_range_constraint(sigma, 1));
        range_assertions_.push_back(make_range_constraint(res, bv_width));

        cache_[t] = res;
      } else if (op == BVMul) {
        uint64_t bv_width = t->get_sort()->get_width();
        string name = "sigma_" + to_string(sigma_vars_.size());
        Term sigma = solver_->make_symbol(name, int_sort_);
        Term mul = solver_->make_term(Plus, cached_children);
        Term multSig = solver_->make_term(Mult, sigma, pow2(bv_width));
        Term res = solver_->make_term(Minus, mul, multSig);

        range_assertions_.push_back(make_range_constraint(sigma, bv_width));
        range_assertions_.push_back(make_range_constraint(res, bv_width));
        cache_[t] = res;
      } else if (op == BVUdiv) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term div = solver_->make_term(Div, cached_children);
        Term condition = solver_->make_term(Equal, cached_children[1], int_zero_);
        Term res = solver_->make_term(Ite, condition, int_max(bv_width), div);
        cache_[t] = res;
      } else if (op == BVUrem) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term mod = solver_->make_term(Mod, cached_children);
        Term condition = solver_->make_term(Equal, cached_children[1], int_zero_);
        Term res = solver_->make_term(Ite, condition, cached_children[0], mod);
        cache_[t] = res;
      } else if (op == BVNeg) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term is_zero = solver_->make_term(Equal, cached_children[0], int_zero_);
        Term neg = solver_->make_term(Minus, pow2(bv_width), cached_children[0]);
        Term res = solver_->make_term(Ite, is_zero, int_zero_, neg); 
        cache_[t] = res;
      } else if (op == BVNot) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term res = make_bvnot_term(cached_children[0], bv_width);
        cache_[t] = res;
      } else if (op == BV_To_Nat) {
        cache_[t] = cached_children[0];
      } else if (op == Concat) {
         uint64_t bv_width = t->get_sort()->get_width();
         Term left = solver_->make_term(Mult, cached_children[0], pow2(bv_width));
         Term res = solver_->make_term(Plus, left, cached_children[1]);
         cache_[t] = res;
      } else if (op == Extract) {
        uint64_t upper = op.idx0;
        uint64_t lower = op.idx1;
        
        Term upper_term = solver_->make_term(upper, int_sort_);
        Term lower_term = solver_->make_term(lower, int_sort_);

        Term div = solver_->make_term(Div, cached_children[0], lower_term);
        uint64_t interval = upper - lower;
        Term res = solver_->make_term(Mod, div, pow2(interval));
        cache_[t] = res;
      } else if (op == BVUlt) {
        Term res = solver_->make_term(Lt, cached_children);
        cache_[t] = res;
      } else if (op == BVUle) {
        Term res = solver_->make_term(Le, cached_children);
        cache_[t] = res;
      } else if (op == BVUgt) {
        Term res = solver_->make_term(Gt, cached_children);
        cache_[t] = res;
      } else if (op == BVUge) {
        Term res = solver_->make_term(Ge, cached_children);
        cache_[t] = res;
      } else if (is_bw_op(op)) {
         uint64_t bv_width = t->get_sort()->get_width();
        Term res = handle_bw_op(t, bv_width, cached_children);
        cache_[t] = res;
      } else  {
        assert(false);
      }

    } else {
      // leaf now
      Sort s = t->get_sort();
      SortKind sk = s->get_sort_kind();
      if (t->is_symbolic_const()) {
        // a variable
        if (sk == SortKind::BV) {
          uint64_t bv_width = t->get_sort()->get_width();
          string name = "bv2int_" + t->to_string();
          Term res = solver_->make_symbol(name, int_sort_);

          range_assertions_.push_back(make_range_constraint(res, bv_width));
          cache_[t] = res;
        } else {
          assert(sk == SortKind::BOOL ||
                 sk == SortKind::FUNCTION);
          cache_[t] = t;
        }
      } else if(t->is_value()) {
        // a constant
        if (sk == SortKind::BV) {
          string smtlib_string = t->to_string();
          //smtlib_string has the form (_ bv*** k). 
          //We want to fetch ***
          size_t last_space_location = smtlib_string.find_last_of(" ");
          size_t decimal_begin = 5; // "(_ bv" has 5 charecters
          size_t decimal_length = last_space_location - decimal_begin;
          string decimal = smtlib_string.substr(5, decimal_length);
          cache_[t] = solver_->make_term(decimal, int_sort_);
        } else {
          assert(sk == SortKind::BOOL || sk == SortKind::FUNCTION);
          cache_[t] = t;
        }
      }
    }
  }
  return Walker_Continue;
}

Term BV2Int::convert(Term t)
{
  visit(t);
  Term res = cache_[t];
  stack_entry_t e = stack_.back();
  size_t r_begin_idx = std::get<1>(e);

  for (size_t i = r_begin_idx; i < range_assertions_.size(); ++i) {
    res = solver_->make_term(And, res, range_assertions_[i]);
  }

  return res;
}

inline Term BV2Int::pow2(uint64_t k)
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

Term BV2Int::make_bvnot_term(Term x, uint64_t k) {
  return solver_->make_term(Minus, int_max(k), x);
}

Term BV2Int::int_max(uint64_t k) {
  assert(k <= 64);
  uint64_t val;
  if (k == 64) {
    val = -1;
  } else {
    val = pow(2, k) - 1;
  }
  return solver_->make_term(val, int_sort_);
}

bool BV2Int::is_bw_op(Op op) {
  return (op == BVAnd || op == BVOr || op == BVXor || op == BVNand || op == BVNor || op == BVXnor|| op == BVLshr || op == BVShl);
}

Term BV2Int::handle_bw_op(Term t, uint64_t bv_width, TermVec cached_children) {
  if (lazy_bw_) {
    return handle_bw_op_lazy(t, bv_width);
  } else {
    return handle_bw_op_eager(t, bv_width, cached_children);
  }
}

Term BV2Int::handle_boolean_bw_eager(Term t, uint64_t bv_width) {
  assert(false);
  return t;
}

Term BV2Int::handle_bw_op_lazy(Term t, uint64_t bv_width) {
  return t;
}

Term BV2Int::handle_bw_op_eager(Term t, uint64_t bv_width, TermVec cached_children) {
  if (is_shift_op(t->get_op())) {
    handle_shift_eager(t, bv_width, cached_children);
  } else {
    handle_boolean_bw_eager(t, bv_width);
  }
  return t;
}

bool BV2Int::is_shift_op(Op op) {
  return (op == BVShl || op == BVLshr);
}

Term BV2Int::handle_shift_eager(Term t, uint64_t bv_width, TermVec cached_children) {
  Term ite = int_zero_;
  Term x = cached_children[0];
  Term y = cached_children[1];
  for (uint64_t i=0; i<bv_width; i++) {
    Term i_term = solver_->make_term(i, int_sort_);
    Term condition = solver_->make_term(Equal, y, i_term);
    ite = solver_->make_term(Ite, condition, i_term, ite);
  }
  Term res;
  Op op = t->get_op();
  if (op == BVShl) {
    res = solver_->make_term(Mult, x, ite);
  } else {
    assert(op == BVLshr);
    res = solver_->make_term(Div, x, ite);
  }
  res = solver_->make_term(Mod, res, pow2(bv_width));
  return res;
}

}
