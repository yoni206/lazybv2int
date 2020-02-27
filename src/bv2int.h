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

 private:

  smt::Term pow2(uint64_t k);
  smt::Term make_range_constraint(smt::Term var, uint64_t bv_width);
  
  smt::TermVec range_assertions_;
  smt::TermVec sigma_vars_;
  smt::Sort int_sort_;
};
}  // namespace lbv2i
