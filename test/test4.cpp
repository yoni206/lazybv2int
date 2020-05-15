#include "lbv2isolver.h"
#include "assert.h"

#include "smt-switch/msat_factory.h"
#include "smt-switch/cvc4_factory.h"
#include "smt-switch/smt.h"
#include "smt-switch/result.h"

using namespace lbv2i;
using namespace smt;
using namespace std;

int main() {
  SmtSolver underlying_solver = smt::CVC4SolverFactory::create(false);
  utils u(underlying_solver);
  Sort int_sort = underlying_solver->make_sort(INT);
  Term int_x = underlying_solver->make_term(10, int_sort);
  Term bv_x = u.int_val_to_bv_val(int_x, 4);
  cout << "panda int_x = " << int_x << endl;
  cout << "panda bv_x = " << bv_x << endl;
}
