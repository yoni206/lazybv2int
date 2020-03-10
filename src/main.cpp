#include "smtlibsolver.h"

#include "smt-switch/msat_factory.h"

using namespace lbv2i;
using namespace std;
using namespace smt;

int main(int argc, char ** argv)
{
  string filename = string(argv[1]);
  smt::SmtSolver underlying_solver = smt::MsatSolverFactory::create();
  LBV2ISolver solver = LBV2ISolver(underlying_solver, false);
  solver.run(filename);
}
