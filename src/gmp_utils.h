#pragma once

#include <gmpxx.h>
#include "smt-switch/smt.h"

namespace utils {
  std::string pow2_str(uint64_t k);
  smt::Term pow2(uint64_t k, smt::SmtSolver s);
}
