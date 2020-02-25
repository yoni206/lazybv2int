#include "smtlibsolver.h"

using namespace std;

namespace lbv2i {

SmtLibSolver::SmtLibSolver(smt::SmtSolver & solver) :
  solver_(solver)
{}

SmtLibSolver::~SmtLibSolver() {}

void SmtLibSolver::run(string filename) {}

}  // namespace lbv2i
