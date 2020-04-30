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

void BV2Int::reset()
{
  cache_.clear();
  extra_assertions_.clear();
  f_bv_terms_.clear();
  stack_.clear();
}

void BV2Int::push()
{
  stack_.push_back(stack_entry_t(
      cache_, extra_assertions_.size(), f_bv_terms_.size()));
}

void BV2Int::pop()
{
  assert(stack_.size() > 0);
  stack_entry_t e = stack_.back();
  cache_ = std::get<0>(e);
  extra_assertions_.resize(std::get<1>(e));
  f_bv_terms_.resize(std::get<2>(e));
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
        Term sigma = utils_.gen_add_sigma(cached_children, extra_assertions_, bv_width);
        Term plus = solver_->make_term(Plus, cached_children);
        Term p = pow2(bv_width);
        Term multSig = solver_->make_term(Mult, sigma, p);
        Term res = solver_->make_term(Minus, plus, multSig);
        extra_assertions_.push_back(utils_.make_range_constraint(res, bv_width));
        cache_[t] = res;
      } else if (op.prim_op == BVMul) {
        uint64_t bv_width = t->get_sort()->get_width();
        Term sigma = utils_.gen_mul_sigma(cached_children, extra_assertions_, bv_width);
        Term mul = solver_->make_term(Mult, cached_children);
        Term p = pow2(bv_width);
        Term multSig = solver_->make_term(Mult, sigma, p);
        Term res = solver_->make_term(Minus, mul, multSig);
        extra_assertions_.push_back(utils_.make_range_constraint(res, bv_width));
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
        Term mod = utils_.gen_mod(cached_children[0], cached_children[1], extra_assertions_);
        Term condition = 
            solver_->make_term(Equal, cached_children[1], int_zero_);
        Term res = solver_->make_term(Ite, condition, cached_children[0], mod);
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
        Term res = handle_shift_op(t, bv_width, cached_children);
        cache_[t] = res;
      } else if (op.prim_op == Apply) {
        Term uf = *(t->begin());
        TermVec app_children(cached_children.begin(), cached_children.end());
        assert(cache_.find(uf) != cache_.end());
        Term intuf = cache_[uf];
        app_children.at(0) = intuf;
        cache_[t] = solver_->make_term(Apply, app_children);
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
          Term res = utils_.create_fresh_var(name, int_sort_);
          int_vars_.insert(res);

          extra_assertions_.push_back(utils_.make_range_constraint(res, bv_width));
          cache_[t] = res;
        } else if (sk == SortKind::FUNCTION) {
           if (internal(t)) {
              cache_[t] = t;
           } else {
               std::vector<Sort> bv_domain_sorts = t->get_sort()->get_domain_sorts();
               //list of sorts for the translated function
               //The last sort is the co-domain sort
               std::vector<Sort> int_sorts;
               for (auto s : bv_domain_sorts) {
                  assert(s->get_sort_kind() == BV);
                  int_sorts.push_back(int_sort_);
               }
               assert(t->get_sort()->get_codomain_sort()->get_sort_kind() == BV);
               int_sorts.push_back(int_sort_);
               Sort int_fun_sort = solver_->make_sort(FUNCTION, int_sorts);
               //cache fun symbol
               cache_[t] = solver_->make_symbol(t->to_string() + "_bv2int", int_fun_sort);
           }
        } else {
          assert(sk == SortKind::BOOL);
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
        } else if (sk == SortKind::BOOL)  {
          cache_[t] = t;
        } else {
          assert(false);
        }
      }
    }
  }
  return Walker_Continue;
}

bool BV2Int::internal(Term uf) {
  std::vector<Sort> domain_sorts = uf->get_sort()->get_domain_sorts();
  for (auto s : domain_sorts) {
    if (s != int_sort_) {
      return false;
    }
  }
  if (uf->get_sort()->get_codomain_sort() != int_sort_) {
    return false;
  }
  return true;
}

Term BV2Int::convert(Term & t)
{
  visit(t);
  Term res = cache_.at(t);
  //  cout << "panda t " << t << endl;
  //  cout << "panda res " << res << endl;

  // cout << "panda with extra: " << res << endl;

#if 0
  if (opts.solver == "msat") {
    solver_->assert_formula(res);
    FILE * f = fopen("tmp.bv2int.smt2", "w");
    solver_->dump_smt2(f);
    fclose(f);
  }
#endif

  return res;
}

inline Term BV2Int::pow2(uint64_t k)
{
  return utils_.pow2(k);
}


inline Term BV2Int::make_bvnot_term(const Term & x, uint64_t k)
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

inline bool BV2Int::is_bw_op(Op op)
{
  return (op == BVAnd); 
}


Term BV2Int::handle_bw_op(const Term & t,
                          uint64_t bv_width,
                          const TermVec & cached_children)
{
  Op op = t->get_op();
  assert(cached_children.size() == 2);
  Term x = cached_children[0];
  Term y = cached_children[1];

  // sort args (to handle symmetry)
  if (x->hash() > y->hash()) {
    Term tmp = x;
    x = y;
    y = tmp;
  }

  Term res;
  if (lazy_bw_) {
    // in lazy mode, don't want to add anything to extra_assertions_
    // just get the uf representation
    res = utils_.gen_bw_uf(op, bv_width, x, y);
    f_bv_terms_.push_back(res);
  } else {
    res = utils_.gen_bw(op, bv_width, granularity_, x, y, extra_assertions_);
  }

  return res;
}

inline bool BV2Int::is_shift_op(Op op) { return (op == BVShl || op == BVLshr); }


Term BV2Int::handle_shift_op(const Term & t,
                                uint64_t bv_width,
                                const TermVec & cached_children)
{
  Op op = t->get_op();
  assert(cached_children.size() == 2);
  Term x = cached_children[0];
  Term y = cached_children[1];

  Term res;
  if (lazy_bw_) {
    //TODO currently lazy and eager do the same for shift. 
    //Once there is a proper handling of shift in lazy,
    //the following line should be uncommented and the one that follows deleted.
    res = utils_.gen_shift_uf(op, bv_width, x, y);
    f_bv_terms_.push_back(res);
    //res = utils_.gen_shift(op, bv_width, x, y, extra_assertions_);
  } else {
    res = utils_.gen_shift(op, bv_width, x, y, extra_assertions_);
  }
  return res;
}


}  // namespace lbv2i
