#pragma once

#include <gmpxx.h>
#include "smt-switch/smt.h"

namespace utils {
smt::Term pow2(uint64_t k, smt::SmtSolver s);
}
