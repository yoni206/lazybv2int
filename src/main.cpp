#include <assert.h>

#include "opts.h"
#include "smt-switch/cvc4_factory.h"
#include "smt-switch/msat_factory.h"
#include "smtlibsolver.h"

using namespace lbv2i;
using namespace std;
using namespace smt;

int main(int argc, char ** argv)
{
  string filename;
  size_t num_files = 0;
  string opt;
  for (size_t i = 1; i < argc; ++i) {
    // cout << "processing " << argv[i] << endl;
    opt = argv[i];
    if (opt == "--help" || opt == "-h") {
      help_msg(argv[0]);
      return 0;
    } else if (opt.rfind("--", 0) == 0) {
      set_opt(opt);
    } else {
      if (num_files > 0) {
        cout << "Got more than one non-option arguments: " << filename << ", "
             << argv[i] << endl;
        cout << "usage: " << argv[0] << "[--options] <filename>" << endl;
        return 0;
      }
      filename = argv[i];
      ++num_files;
    }
  }

  smt::SmtSolver underlying_solver;
  if (opts.solver == "cvc4") {
    underlying_solver = smt::CVC4SolverFactory::create();
    underlying_solver->set_opt("nl-ext-tplanes", "true");
    underlying_solver->set_opt("produce-models", "true");
  } else if (opts.solver == "msat") {
    underlying_solver = smt::MsatSolverFactory::create();
  } else {
    assert(false);
  }

  LBV2ISolver solver = LBV2ISolver(underlying_solver, opts.lazy);
  solver.run(filename);

  return 0;
}
