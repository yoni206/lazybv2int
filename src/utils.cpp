#include <assert.h>
#include "utils.h"
#include "bw_functions.h"
#include "opts.h"

using namespace smt;
using namespace std;
using namespace lbv2i;




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
  Sort fbv_sort = solver_->make_sort(
      FUNCTION, SortVec{ int_sort_, int_sort_, int_sort_, int_sort_ });
  fbvand_ = solver_->make_symbol("fbv_and", fbv_sort);
  fbvor_ = solver_->make_symbol("fbv_or", fbv_sort);
  fbvxor_ = solver_->make_symbol("fbv_xor", fbv_sort);
}


Term utils::pow2(uint64_t k) {
  string pow_bv_width_str = pow2_str(k);
  return solver_->make_term(pow_bv_width_str, int_sort_);
}


Term utils::make_range_constraint(const Term & var, uint64_t bv_width)
{
  // returns 0<= var < 2^bv_width as a constraint
  Term l = solver_->make_term(Le, int_zero_, var);
  Term p = pow2(bv_width);
  Term u = solver_->make_term(Lt, var, p);
  return solver_->make_term(And, l, u);
}


Term utils::create_fresh_var(string name, Sort st)
{
  unsigned i = 0;
  Term res;

  while(true) {
    try {
      res = solver_->make_symbol(name + to_string(i), st);
      break;
    } catch (IncorrectUsageException & e){
      ++i;
    } catch (SmtException & e) {
      throw e;
    }
  }

  return res;
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
  if (n->is_value()) {
    if (n != int_zero_) {
      return right;
    } else {
      return solver_->make_term(true);
    } 
  } else {
    Term res = solver_->make_term(Implies, left, right);
    return res;
  }
}

Term utils::gen_bitwise_int(Op op, uint64_t k, const Term & x, const Term & y)
{
  if (op.prim_op == BVAnd) {
    switch (k) {
      case 1: return int_bvand_1(x, y, solver_);
      case 2: return int_bvand_2(x, y, solver_);
      case 3: return int_bvand_3(x, y, solver_);
      case 4: return int_bvand_4(x, y, solver_);
      case 5: return int_bvand_5(x, y, solver_);
      case 6: return int_bvand_6(x, y, solver_);
      default: assert(false);
    }
  } else if (op.prim_op == BVOr) {
    switch (k) {
      case 1: return int_bvor_1(x, y, solver_);
      case 2: return int_bvor_2(x, y, solver_);
      case 3: return int_bvor_3(x, y, solver_);
      case 4: return int_bvor_4(x, y, solver_);
      case 5: return int_bvor_5(x, y, solver_);
      case 6: return int_bvor_6(x, y, solver_);
      default: assert(false);
    }
  } else if (op.prim_op == BVXor) {
    switch (k) {
      case 1: return int_bvxor_1(x, y, solver_);
      case 2: return int_bvxor_2(x, y, solver_);
      case 3: return int_bvxor_3(x, y, solver_);
      case 4: return int_bvxor_4(x, y, solver_);
      case 5: return int_bvxor_5(x, y, solver_);
      default: assert(false);
    }
  }
  assert(false);
}

Term utils::gen_block(Op op,
                       const smt::Term& a,
                       const smt::Term& b,
                       uint64_t i,
                       uint64_t block_size,
                       TermVec& side_effects)
{
  Term p =  pow2(i * block_size);
  Term left_a = gen_intdiv(a, p, side_effects);
  Term left_b = pow2(block_size);
  Term left = gen_mod(left_a, left_b, side_effects);

  Term right_a = gen_intdiv(b, p, side_effects);
  Term right_b = pow2(block_size);
  Term right = gen_mod(right_a, right_b, side_effects);
  return gen_bitwise_int(op, block_size, left, right);
}

Term utils::gen_bw_uf(const Op op, uint64_t bv_width, const Term & a, const Term & b)
{
  Term bv_width_term = solver_->make_term(to_string(bv_width), int_sort_);
  if (op.prim_op == BVAnd) {
    TermVec args = { fbvand_, bv_width_term, a, b };
    return solver_->make_term(Apply, args);
  } else if (op.prim_op == BVOr) {
    TermVec args = { fbvor_, bv_width_term, a, b };
    return solver_->make_term(Apply, args);
  } else if (op.prim_op == BVXor) {
    TermVec args = { fbvxor_, bv_width_term, a, b };
    return solver_->make_term(Apply, args);
  } else {
    assert(false);
  }
}

Term utils::gen_bw_sum(const Op op, uint64_t bv_width, uint64_t granularity, const Term &a, const Term & b, TermVec& side_effects)
{
  assert(granularity > 0);

  uint64_t block_size = granularity;
  if (block_size > bv_width) {
    block_size = bv_width;
  }
  while (bv_width % block_size != 0) {
    block_size = block_size - 1;
  }

  uint64_t num_of_blocks = bv_width / block_size;
  Term sum = int_zero_;
  for (uint64_t i = 0; i < num_of_blocks; i++) {
    Term block = gen_block(op, a, b, i, block_size, side_effects);
    Term power_of_two = pow2(i);
    Term sum_part = solver_->make_term(Mult, block, power_of_two);
    sum = solver_->make_term(Plus, sum, sum_part);
  }
  return sum;
}

void utils::gen_bw_equalities(const Op op,
                              uint64_t bv_width,
                              uint64_t granularity,
                              const Term & a,
                              const Term & b,
                              const Term & sigma,
                              TermVec & side_effects)
{
  assert(granularity > 0);

  uint64_t block_size = granularity;
  if (block_size > bv_width) {
    block_size = bv_width;
  }
  while (bv_width % block_size != 0) {
    block_size = block_size - 1;
  }

  uint64_t num_of_blocks = bv_width / block_size;

  Sort intsort = solver_->make_sort(INT);

  // add bitwise equality assertions over integers
  // e.g. introduce bvand_x_y := (bvand x y)
  // and assert bvand_x_y[i] = min(x[i], y[i]) for each i up to width-1
  // using division and mod to extract bits
  side_effects.push_back(make_range_constraint(sigma, bv_width));

  uint64_t i, j;
  Term block;
  Term sigma_ext;
  for (uint64_t n = 0; n < num_of_blocks; n++) {
    block = gen_block(op, a, b, n, block_size, side_effects);
    j = n * block_size;
    i = j + block_size - 1;
    // now extract the corresponding bits of sigma
    // ((_ extract i j) a) is a / 2^j mod 2^{i-j+1}
    Term p = pow2(j);
    sigma_ext = gen_intdiv(sigma, p, side_effects);
    p = pow2(i - j + 1);
    sigma_ext = gen_mod(sigma_ext, p, side_effects);
    // add equality between blocks
    side_effects.push_back(solver_->make_term(Equal, sigma_ext, block));
  }
}

Term utils::gen_bw(const Op op, const uint64_t bv_width, uint64_t granularity, const Term &a, const Term &b, TermVec& side_effects) {
  assert(granularity > 0);


  // sigma is the term, e.g., f_bvand(a,b)
  Term sigma = gen_bw_uf(op, bv_width, a, b);

  uint64_t block_size = granularity;
  if (block_size > bv_width) {
    block_size = bv_width;
  }
  while (bv_width % block_size != 0) {
    block_size = block_size - 1;
  }
  uint64_t num_of_blocks = bv_width / block_size;
  if (opts.use_sum_bvops) {
    Term sum = gen_bw_sum(op, bv_width, granularity, a, b, side_effects);
    // add equality to extra assertions
    side_effects.push_back(solver_->make_term(Equal, sigma, sum));
  } else {
    gen_bw_equalities(op, bv_width, granularity, a, b, sigma, side_effects);
  }

  // sigma is the new term for this bitwise operator
  // and depending on the setting we've either
  // 1. asserted it's equal to the sum
  // 2. asserted it's within the range constraints and each bit is equal
  return sigma;
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

