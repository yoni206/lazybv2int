#include <assert.h>
#include <fstream>

#include "opts.h"
#include "lbv2isolver.h"
#include "smt-switch/cvc4_factory.h"
#include "smt-switch/msat_factory.h"
#include "smt-switch/smtlib_reader.h"

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
    // create CVC4 Solver without a shadow DAG (e.g. LoggingSolver wrapper)
    underlying_solver = smt::CVC4SolverFactory::create(false);
    underlying_solver->set_opt("nl-ext-tplanes", "true");
  } else if (opts.solver == "msat") {
    // create MathSAT Solver without a shadow DAG (e.g. LoggingSolver wrapper)
    underlying_solver = smt::MsatSolverFactory::create(false);
  } else {
    assert(false);
  }

  smt::SmtSolver solver = std::make_shared<LBV2ISolver>(underlying_solver, opts.lazy);
  SmtLibReader parser(solver);

  if (num_files == 1) {
    // ifstream ifile(filename);
    // if (!ifile) {
    //   cout << "file does not exist" << endl;
    //   return 1;
    // }
    parser.parse(filename);
  } else {
    cout << "usage: lazybv2int <filename>" << endl;
    // can add a run on stdin option if needed
  }

  return 0;
}
