#pragma once

#include "smt-switch/smt.h"

namespace lbv2i {
  class Preprocessor {
  public:
    // probably this class will inherit form SMT-Switch-Walker
    Preprocessor();
    ~Preprocessor();

    smt::Term process(smt::Term t);

  private:

    // binarizer
    Binarizer bin_;

    // operator eliminator
    OpEliminator opelim_;
  };
}
