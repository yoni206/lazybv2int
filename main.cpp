
#include "smtlibsolver.h"

using namespace lbv2i;
using namespace std;

int main(int argc, char ** argv)
{
  string filename = string(argv[1]);

  SmtLibSolver solver = SmtLibSolver();

  solver.run(filename);
}
