#pragma once

#include "smt-switch/smt.h"

namespace lbv2i {

class Axioms
{
 public:
  Axioms(smt::SmtSolver &solver);
  ~Axioms();

  // we assume that the term t looks like "fbvand(x, y)"
  // note the function name
  bool check_bvand_base_case(smt::Term t, smt::TermVec &outlemmas);

 private:
  smt::SmtSolver &solver_;

}; // class axioms

} // namespace lbv2i
