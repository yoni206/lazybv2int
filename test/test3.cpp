#include "lbv2isolver.h"
#include "assert.h"

#include "smt-switch/cvc4_factory.h"
#include "smt-switch/smt.h"
#include "smt-switch/result.h"

using namespace lbv2i;
using namespace smt;
using namespace std;

int main() {
  SmtSolver underlying_solver = smt::CVC4SolverFactory::create(false);

  underlying_solver->set_logic("QF_NIA");
  Sort int_sort = underlying_solver->make_sort(INT);
  Term two = underlying_solver->make_term(2, int_sort);
  Term x = underlying_solver->make_symbol("x", int_sort);
  Term x_div_2 = underlying_solver->make_term(IntDiv, x, two);
  cout << "panda " << x_div_2 << endl;;
}
