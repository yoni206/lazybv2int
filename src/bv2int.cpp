#include "bv2int.h"

#include <assert.h>
#include <gmpxx.h>
#include <math.h>

#include "opts.h"

using namespace std;
using namespace smt;

namespace lbv2i {

static bool is_simple_op(Op op)
{
  vector<Op> simple_op = { And,  Or,     Xor,      Not,    Implies, Iff,
                           Ite,  Equal,  Distinct, Plus,   Minus,   Negate,
                           Mult, IntDiv, Lt,       Le,     Gt,      Ge,
                           Mod,  Abs,    Pow,      To_Real };
  for (auto o : simple_op) {
    if (o == op) {
      return true;
    }
  }
  return false;
}


BV2Int::BV2Int(SmtSolver & solver, bool clear_cache, bool lazy_bw)
    : super(solver, clear_cache), lazy_bw_(lazy_bw), utils_(solver)
{
  int_sort_ = solver_->make_sort(INT);
  int_zero_ = solver_->make_term(0, int_sort_);
  int_one_ = solver_->make_term(1, int_sort_);
  granularity_ = opts.granularity;
}

BV2Int::~BV2Int() {}

void BV2Int::push()
{
  stack_.push_back(stack_entry_t(
      cache_, extra_assertions_.size(), extra_vars_.size(), fterms_.size()));
}

void BV2Int::pop()
{
  stack_entry_t e = stack_.back();
  cache_ = std::get<0>(e);
  extra_assertions_.resize(std::get<1>(e));
  extra_vars_.resize(std::get<2>(e));
  fterms_.resize(std::get<3>(e));
  stack_.pop_back();
}


WalkerStepResult BV2Int::visit_term(Term & t)
{
  if (!preorder_) {
    Op op = t->get_op();
    if (!op.is_null()) {
      // term has children
      TermVec cached_children;
      for (auto c : t) {
        cached_children.push_back(cache_.at(c));
      }

      // std::cout << "visiting operator: " << op.to_string() << std::endl;
      if (is_simple_op(op)) {
        cache_[t] = solver_->make_term(op, cached_children);
      }

      else if (op.prim_op == BVAdd) {
        uint64_t bv_width = t->get_sort()->get_width();
        string name = "sigma_add_" + to_string(extra_vars_.size());
        Term sigma = solver_->make_symbol(name, int_sort_);
        extra_vars_.push_back(sigma);
        Term plus = solver_->make_term(Plus, cached_children);
        Term p = pow2(bv_width);
        Term multSig = solver_->make_term(Mult, sigma, p);
        Term res = solver_->make_term(Minus, plus, multSig);
        extra_assertions_.push_back(utils_.make_range_constraint(sigma, 1));
        extra_assertions_.push_back(utils_.make_range_constraint(res, bv_width));

        cache_[t] = res;

      } else if (op.prim_op == BVMul) {
        uint64_t bv_width = t->get_sort()->get_width();
        string name = "sigma_mul_" + to_string(extra_vars_.size());
        Term sigma = solver_->make_symbol(name, int_sort_);
        extra_vars_.push_back(sigma);
        Term mul = solver_->make_term(Mult, cached_children);
        Term p = pow2(bv_width);
        Term multSig = solver_->make_term(Mult, sigma, p);
        Term res = solver_->make_term(Minus, mul, multSig);

        extra_assertions_.push_back(utils_.make_range_constraint(res, bv_width));

        if (cached_children[0]->is_value() || cached_children[1]->is_value()) {
          // linear multiplication optimization
          Term c = cached_children[0]->is_value() ? cached_children[0]
                                                  : cached_children[1];
          extra_assertions_.push_back(solver_->make_term(Ge, sigma, int_zero_));
          extra_assertions_.push_back(solver_->make_term(Lt, sigma, c));
        } else {
          extra_assertions_.push_back(utils_.make_range_constraint(sigma, bv_width));
        }

        cache_[t] = res;

      } else if (op.prim_op == BVUdiv) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term div = utils_.gen_intdiv(cached_children[0], cached_children[1], extra_assertions_);
        Term condition =
            solver_->make_term(Equal, cached_children[1], int_zero_);
        Term res = solver_->make_term(Ite, condition, int_max(bv_width), div);
        cache_[t] = res;
      } else if (op.prim_op == BVUrem) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term res = utils_.gen_mod(cached_children[0], cached_children[1], extra_assertions_);
        cache_[t] = res;
      } else if (op.prim_op == BVNeg) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term is_zero = solver_->make_term(Equal, cached_children[0], int_zero_);
        Term p = pow2(bv_width);
        Term neg =
            solver_->make_term(Minus, p, cached_children[0]);
        Term res = solver_->make_term(Ite, is_zero, int_zero_, neg);
        cache_[t] = res;
      } else if (op.prim_op == BVNot) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term res = make_bvnot_term(cached_children[0], bv_width);
        cache_[t] = res;
      } else if (op.prim_op == BV_To_Nat) {
        cache_[t] = cached_children[0];
      } else if (op.prim_op == Concat) {
        TermVec original_children;
        for (auto c : t) {
          original_children.push_back(c);
        }
        // the extra width is that of the second argument
        uint64_t extra_width = original_children[1]->get_sort()->get_width();
        Term p = pow2(extra_width);
        Term left =
            solver_->make_term(Mult, cached_children[0], p);
        Term res = solver_->make_term(Plus, left, cached_children[1]);
        cache_[t] = res;
      } else if (op.prim_op == Extract) {
        // ((_ extract i j) a) is a / 2^j mod 2^{i-j+1}
        uint64_t upper = op.idx0;
        uint64_t lower = op.idx1;
        Term p = pow2(lower);
        Term div = lower > 0 ? utils_.gen_intdiv(cached_children[0], p, extra_assertions_)
                             : cached_children[0];
        uint64_t interval = upper - lower + 1;
        Term pwinterval = pow2(interval);
        Term res = utils_.gen_mod(div, pwinterval, extra_assertions_);
        cache_[t] = res;
      } else if (op.prim_op == BVUlt) {
        Term res = solver_->make_term(Lt, cached_children);
        cache_[t] = res;
      } else if (op.prim_op == BVUle) {
        Term res = solver_->make_term(Le, cached_children);
        cache_[t] = res;
      } else if (op.prim_op == BVUgt) {
        Term res = solver_->make_term(Gt, cached_children);
        cache_[t] = res;
      } else if (op.prim_op == BVUge) {
        Term res = solver_->make_term(Ge, cached_children);
        cache_[t] = res;
      } else if (is_bw_op(op)) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term res = handle_bw_op(t, bv_width, cached_children);
        cache_[t] = res;
      } else if (is_shift_op(op)) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term res = handle_shift_eager(t, bv_width, cached_children);
        cache_[t] = res;
      } else {
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
          int_vars_.insert(res);

          extra_assertions_.push_back(utils_.make_range_constraint(res, bv_width));
          cache_[t] = res;
        } else {
          assert(sk == SortKind::BOOL || sk == SortKind::FUNCTION);
          cache_[t] = t;
        }
      } else if (t->is_value()) {
        // a constant
        if (sk == SortKind::BV) {
          string smtlib_string = t->to_string();
          // smtlib_string has the form (_ bv*** k).
          // We want to fetch ***
          size_t last_space_location = smtlib_string.find_last_of(" ");
          size_t decimal_begin = 5;  // "(_ bv" has 5 charecters
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

Term BV2Int::convert(Term & t)
{
  visit(t);
  Term res = cache_[t];
  //  cout << "panda t " << t << endl;
  //  cout << "panda res " << res << endl;
  size_t r_begin_idx = 0;
  if (stack_.size() > 0) {
    stack_entry_t e = stack_.back();
    size_t r_begin_idx = std::get<1>(e);
  }
  
  for (size_t i = r_begin_idx; i < extra_assertions_.size(); ++i) {
    res = solver_->make_term(And, res, extra_assertions_[i]);
  }

 // cout << "panda with extra: " << res << endl;
  if (opts.solver == "msat") {
    solver_->assert_formula(res);
    FILE * f = fopen("tmp.smt2", "w");
    solver_->dump_smt2(f);
    fclose(f);
  }
  return res;
}

inline Term BV2Int::pow2(uint64_t k)
{
  return utils_.pow2(k);
}


Term BV2Int::make_bvnot_term(const Term & x, uint64_t k)
{
  return solver_->make_term(Minus, int_max(k), x);
}

Term BV2Int::int_max(uint64_t k)
{
  mpz_t base, p;
  mpz_inits(base, p, NULL);
  mpz_set_str(base, "2", 10);
  mpz_pow_ui(p, base, k);

  mpz_class res(p);
  res--;

  mpz_clear(p);
  mpz_clear(base);

  return solver_->make_term(res.get_str(), int_sort_);
}

bool BV2Int::is_bw_op(Op op)
{
  return (op == BVAnd || op == BVOr || op == BVXor);
}

Term BV2Int::get_explicit_bw(Op op,
                                     uint64_t bv_width,
                                     const TermVec & cached_children)
{
  assert(granularity_ > 0);
  uint64_t block_size = granularity_;
  if (block_size > bv_width) {
    block_size = bv_width;
  }
  while (bv_width % block_size != 0) {
    block_size = block_size - 1;
  }
  return utils_.gen_bw(op, bv_width, block_size, cached_children[0], cached_children[1], extra_assertions_);
}



Term BV2Int::handle_bw_op(const Term & t,
                               uint64_t bv_width,
                               const TermVec & cached_children)
{
  Op op = t->get_op();
  assert(cached_children.size() == 2);
  Term x = cached_children[0];
  Term y = cached_children[1];
  Term bv_width_term = solver_->make_term(to_string(bv_width), int_sort_);

  // sort args (to handle symmetry)
  if (x->hash() > y->hash()) {
    Term tmp = x;
    x = y;
    y = tmp;
  }

  Term res;
  if (op.prim_op == BVAnd) {
    TermVec args = { fbv_and(), bv_width_term, x, y };
    res = solver_->make_term(Apply, args);
  } else if (op.prim_op == BVOr) {
    TermVec args = { fbv_or(), bv_width_term, x, y };
    res = solver_->make_term(Apply, args);
  } else if (op.prim_op == BVXor) {
    TermVec args = { fbv_xor(), bv_width_term, x, y };
    res = solver_->make_term(Apply, args);
  } else {
    assert(false);
  }

  fterms_.push_back(res);

  if (!lazy_bw_) {
    //eagerly add equations defining the term
    Term uf_app = res;
    Term explicit_sum = get_explicit_bw(op, bv_width, TermVec({x,y}));
    Term eq = solver_->make_term(Equal, uf_app, explicit_sum);
    extra_assertions_.push_back(eq);
  }
  return res;
}

bool BV2Int::is_shift_op(Op op) { return (op == BVShl || op == BVLshr); }

Term BV2Int::handle_shift_eager(const Term & t,
                                uint64_t bv_width,
                                const TermVec & cached_children)
{
  Op op = t->get_op();
  Term x = cached_children[0];
  Term y = cached_children[1];
  // this will be the case where y is geq the bitwidth or is equal to zero.
  Term y_is_zero = solver_->make_term(Equal, y, int_zero_);
  Term ite = solver_->make_term(Ite, y_is_zero, x, int_zero_);
  // all other cases
  for (uint64_t i = 1; i < bv_width; i++) {
    Term i_term = solver_->make_term(i, int_sort_);
    Term div_mul_term;
    Term p = pow2(i);
    if (op.prim_op == BVShl) {
      div_mul_term = solver_->make_term(Mult, x, p);
    } else {
      assert(op == BVLshr);
      div_mul_term = utils_.gen_intdiv(x, p, extra_assertions_);
    }
    Term condition = solver_->make_term(Equal, y, i_term);
    ite = solver_->make_term(Ite, condition, div_mul_term, ite);
  }
  Term res = ite;
  if (op.prim_op == BVShl) {
    Term p = pow2(bv_width);
    res = utils_.gen_mod(res, p, extra_assertions_);
  }
  return res;
}


}  // namespace lbv2i
