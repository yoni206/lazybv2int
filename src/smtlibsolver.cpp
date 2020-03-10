#include "smtlibsolver.h"

using namespace std;

namespace lbv2i {

SmtLibSolver::SmtLibSolver(smt::SmtSolver & solver) : super(solver) {}

SmtLibSolver::~SmtLibSolver() {}

void SmtLibSolver::run(string filename) {}

}  // namespace lbv2i
