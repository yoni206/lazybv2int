#include "lbv2isolver.h"

using namespace smt;

namespace lbv2i {

  LBV2ISolver::LBV2ISolver()
  {
  }

  LBV2ISolver::~LBV2ISolver()
  {
  }

  Result LBV2ISolver::solve()
  {
    TermVec lemmas;

    while (true) {
      Result r = solver_->check_sat();

      if (r.is_unsat()) {
        return r;
      }

      lemmas.clear();
      if (!refine(lemmas)) {
        return r;
      }

      for (auto l : lemmas) {
        solver_->assert_formula(l);
      }
    }
  }

  bool LBV2ISolver::push()
  {
    return false;
  }

  bool LBV2ISolver::pop()
  {
    return false;
  }

  bool LBV2ISolver::reset()
  {
    solver_->reset_assertions();

    return false;
  }

  bool LBV2ISolver::assert_formula(Term f)
  {
    // preprocess the formula
    Term pre_f = prepro_.process(f);
    
    // translate
    Term t_f = bv2int_.convert(pre_f);

    solver_->assert_formula(t_f);

    return true;
  }

  bool LBV2ISolver::refine(smt::TermVec &outlemmas)
  {
    return true;
  }

} // namespace lbv2i
