#pragma once

#include "smt-switch/smt.h"

namespace lbv2i {

  class LBV2ISolver
  {
  public:
    LBV2ISolver();
    ~LBV2ISolver();

    typedef struct {
      UNSAT = 0;
      SAT = 1;
      UNKNOWN = 2;
    } solver_result;

    solver_result solve();

    bool push();
    bool pop();
    bool reset();

    bool assert_formula(smt::Term f);

  private:

    bool refine();

    // BV2Int Translator
    BV2Int bv2int_;

    // smt-switch solver
    smt::SmtSolver solver_;

  };
}
