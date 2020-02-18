#include "lbv2intsolver.h"

using namespace smt;

namespace lbv2i {

  LBV2INTSolver::LBV2INTSolver()
  {
  }

  LBV2INTSolver::~LBV2INTSolver()
  {
  }

  Result solve()
  {
    TermVec lemmas;

    while (true) {
      Result r = solver_.check_sat();

      if (r == UNSAT) {
        return r;
      }

      lemmas.clear();
      if (!refine(lemmas)) {
        return r;
      }

      for (auto l : lemmas) {
        solver_.assert_formula(l);
      }
    }
  }

  bool LBV2INTSolver::push()
  {
    return false;
  }

  bool LBV2INTSolver::pop()
  {
    return false;
  }

  bool LBV2INTSolver::reset()
  {
    solver_.reset_assertions();

    return false;
  }

  bool LBV2INTSolver::assert_formula(Term f)
  {
    // preprocess the formula
    Term pre_f = prepro_.process(f);
    
    // translate
    Term t_f = bv2int_.convert(pre_f);

    solver_.assert_formula(t_f);

    return true;
  }

  bool LBV2INTSolver::refine(smt::TermVec &outlemmas)
  {
    return true;
  }

} // namespace lbv2i
