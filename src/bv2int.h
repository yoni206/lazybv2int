#pragma once

#include "smt-switch/smt.h"
#include "smt-switch/identity_walker.h"

namespace lbv2i {



class BV2Int : smt::IdentityWalker
{
 public:
  BV2Int(smt::SmtSolver &solver, bool clear_cache, bool abstract=false);
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

  bool abstract_;

  smt::TermVec range_assertions_;
  smt::TermVec sigma_vars_;

  typedef std::tuple<smt::UnorderedTermMap, size_t, size_t> stack_entry_t;
  std::vector<stack_entry_t> stack_;

  smt::Sort int_sort_;
  smt::Sort fbvand_sort_;

  smt::Term int_zero_;

};
}  // namespace lbv2i
