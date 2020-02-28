#include "axioms.h"

#include <assert.h>

using namespace smt;

namespace lbv2i {

Axioms::Axioms(SmtSolver & solver) :
  solver_(solver)
{
}

Axioms::~Axioms()
{
}

bool Axioms::check_bvand_base_case(Term t, TermVec &outlemmas)
{
  TermIter it = t->begin();
  Term tmp = *it;

  assert(tmp->is_value());
  uint64_t bv_width = tmp->to_int();
  ++it;

  Term a = *it;
  ++it;
  Term b = *it;

  if (bv_width == 1) {
    Term l = solver_->make_term(Mult, a, b);
    outlemmas.push_back(l);
  }
  return outlemmas.size() > 0;
}

} // namespace lbv2i
