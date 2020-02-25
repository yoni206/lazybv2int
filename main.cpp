#include "smtlibsolver.h"

#include "smt-switch/msat_factory.h"

using namespace lbv2i;
using namespace std;

int main(int argc, char ** argv)
{
  string filename = string(argv[1]);

  smt::SmtSolver underlying_solver = smt::MsatSolverFactory::create();

  SmtLibSolver solver(underlying_solver);

  solver.run(filename);
}
