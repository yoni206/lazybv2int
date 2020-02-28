#pragma once

#include "smt-switch/smt.h"

namespace lbv2i {

class Axioms
{
 public:
  Axioms(smt::SmtSolver &solver);
  ~Axioms();

 private:
  smt::SmtSolver &solver_;

}; // class axioms

} // namespace lbv2i
