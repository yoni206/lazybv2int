#include "bv2int.h"

using namespace smt;

namespace lbv2i {

BV2Int::BV2Int(SmtSolver & solver, bool clear_cache) :
  super(solver, clear_cache)
{}

BV2Int::~BV2Int() {}


WalkerStepResult BV2Int::visit_term(Term& term) {
  return Walker_Continue;
}

Term BV2Int::convert(Term t)
{
  Term res;
  return t;
}

}  // namespace lbv2i
