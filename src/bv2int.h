#pragma once

#include "smt-switch/smt.h"

namespace lbv2i {

  class BV2Int {
  public:
    // it will also use the walker infrastructure
    BV2Int();
    ~BV2Int();

    smt::Term convert(smt::Term t);

  private:

  };
}
