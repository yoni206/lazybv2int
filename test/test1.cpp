#include "lbv2isolver.h"

#include "smt-switch/msat_factory.h"

using namespace lbv2i;

int main() {
  smt::SmtSolver underlying_solver = smt::MsatSolverFactory::create();

  LBV2ISolver s = LBV2ISolver(s);
  //s.push();
}
