#pragma once

#include "smt-switch/smt.h"
#include "smt-switch/identity_walker.h"

namespace lbv2i {

using namespace smt;

class BV2Int : IdentityWalker
{
 public:
  BV2Int(smt::SmtSolver &solver, bool clear_cache);
  ~BV2Int();

  typedef IdentityWalker super;
  // it will also use the walker infrastructure

  WalkerStepResult visit_term(Term& term);
  Term convert(Term t);

  void push();
  void pop();

 private:

  smt::Term pow2(uint64_t k);
  smt::Term make_range_constraint(smt::Term var, uint64_t bv_width);
  smt::Term make_bvnot_term(smt::Term x, uint64_t k);
  smt::Term int_max(uint64_t k);

  smt::TermVec range_assertions_;
  smt::TermVec sigma_vars_;

  typedef std::tuple<smt::UnorderedTermMap, size_t, size_t> stack_entry_t;
  std::vector<stack_entry_t> stack_;

  smt::Sort int_sort_;
  smt::Term int_zero_;
};
}  // namespace lbv2i
