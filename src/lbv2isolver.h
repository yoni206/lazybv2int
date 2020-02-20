#pragma once

#include "smt-switch/smt.h"
#include "bv2int.h"
#include "preprocessor.h"

namespace lbv2i {

  class LBV2ISolver
  {
  public:
    LBV2ISolver();
    ~LBV2ISolver();

    smt::Result solve();

    bool push();
    bool pop();
    bool reset();

    bool assert_formula(smt::Term f);

  private:

    bool refine(smt::TermVec &outlemmas);

    // BV2Int Translator
    BV2Int bv2int_;

    // Preprocessor that will eliminate some bv operators. Note: keep in mind
    // while writing the preprocessor that we want to use it also in the
    // incremental setting (push/pop)
    Preprocessor prepro_;

    // smt-switch solver
    smt::SmtSolver solver_;

  };
}
