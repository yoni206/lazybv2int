#pragma once

#include "smt-switch/smt.h"
#include "smt-switch/identity_walker.h"

namespace lbv2i {

using namespace smt;

class BV2Int : IdentityWalker 
{
 public:
  // it will also use the walker infrastructure
  
  WalkerStepResult visit_term(Term& term);
  Term convert(Term t);

 private:
};
}  // namespace lbv2i
