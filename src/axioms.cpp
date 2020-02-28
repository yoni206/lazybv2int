#include "axioms.h"

using namespace smt;

namespace lbv2i {

Axioms::Axioms(SmtSolver & solver) :
  solver_(solver)
{
}

Axioms::~Axioms()
{
}

} // namespace lbv2i
