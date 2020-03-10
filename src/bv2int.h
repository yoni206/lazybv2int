#pragma once

#include "smt-switch/smt.h"
#include "smt-switch/identity_walker.h"

namespace lbv2i {



class BV2Int : smt::IdentityWalker
{
 public:
  BV2Int(smt::SmtSolver &solver, bool clear_cache, bool lazy_bw=false);
  ~BV2Int();

  typedef smt::IdentityWalker super;
  // it will also use the walker infrastructure

  smt::WalkerStepResult visit_term(smt::Term& term);
  smt::Term convert(smt::Term t);

  void push();
  void pop();

 private:

  smt::Term pow2(uint64_t k);
  smt::Term make_range_constraint(smt::Term var, uint64_t bv_width);
  smt::Term make_bvnot_term(smt::Term x, uint64_t k);
  smt::Term int_max(uint64_t k);
  smt::Term handle_bw_op(smt::Term t, uint64_t bv_width, smt::TermVec cached_children);
  smt::Term handle_bw_op_lazy(smt::Term t, uint64_t bv_width);
  smt::Term handle_bw_op_eager(smt::Term t, uint64_t bv_width, smt::TermVec cached_children);
  smt::Term handle_shift_eager(smt::Term t, uint64_t bv_width, smt::TermVec cached_children);
  smt::Term handle_boolean_bw_eager(smt::Term t, uint64_t bv_width, smt::TermVec cached_children);
  bool is_shift_op(smt::Op op);
  smt::Term gen_block(smt::Op op, smt::TermVec cached_children, uint64_t i, uint64_t block_size);
  smt::Term gen_bitwise_int(smt::Op op, uint64_t k, smt::Term a, smt::Term b);
  smt::Term gen_mod(uint64_t bv_width, smt::Term a, smt::Term b);



  bool is_bw_op(smt::Op op);

  smt::TermVec range_assertions_;
  smt::TermVec sigma_vars_;

  typedef std::tuple<smt::UnorderedTermMap, size_t, size_t> stack_entry_t;
  std::vector<stack_entry_t> stack_;

  smt::Sort int_sort_;
  smt::Sort fbvand_sort_;

  smt::Term int_zero_;

  //flag that determines if we handle
  //bitwise operators (and/or/shift/...) 
  //lazily or eagerly.
  bool lazy_bw_;
  uint64_t granularity_;

};
}  // namespace lbv2i
