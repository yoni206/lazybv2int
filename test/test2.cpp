#include "lbv2isolver.h"
#include "assert.h"

#include "smt-switch/cvc4_factory.h"
#include "smt-switch/smt.h"
#include "smt-switch/result.h"

using namespace lbv2i;
using namespace smt;

int main() {
  SmtSolver underlying_solver = smt::CVC4SolverFactory::create(false);

  LBV2ISolver s = LBV2ISolver(underlying_solver);
  s.set_logic("QF_UFBVNIA");
  Sort bvsort2 = s.make_sort(BV, 2);
  Term zero = underlying_solver->make_term(0, bvsort2);

  Term x = s.make_symbol("x", bvsort2);
  Term y = s.make_symbol("y", bvsort2);
  Term x_and_y = s.make_term(BVAnd, x, y);
  Term a = s.make_term(Equal, x_and_y, x);
  s.assert_formula(a);
  Result r = s.solve();
  assert(r.is_sat());
}
