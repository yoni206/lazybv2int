#pragma once

#include <string>

#include "lbv2isolver.h"

namespace lbv2i {

/*
 * This class is a solver with SMTLIB parser as a wrapper. It's main job is to
 * parse the SMTLIB file (also incremental files) and call the right functions
 * in solver_.
 */

class SmtLibSolver
{
 public:
  SmtLibSolver(smt::SmtSolver & solver);
  ~SmtLibSolver();

  // main method. it will read the file and prints the results on the standard
  // output.
  void run(std::string filename);

 private:
  LBV2ISolver solver_;
};
}  // namespace lbv2i
