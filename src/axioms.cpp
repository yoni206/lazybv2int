#include "axioms.h"

#include <assert.h>

using namespace smt;

namespace lbv2i {

Axioms::Axioms(SmtSolver & solver) :
  solver_(solver)
{
  false_ = solver_->make_term(false);
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
    Term mul = solver_->make_term(Mult, a, b);
    Term l = solver_->make_term(Equal, t, mul);
    add_if_voilated(l, outlemmas);
  }

  return outlemmas.size() > 0;
}

inline void Axioms::add_if_voilated(Term l, TermVec &out)
{
  if (solver_->get_value(l) == false_) {
    out.push_back(l);
  }
}

} // namespace lbv2i
