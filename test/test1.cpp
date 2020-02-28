#include "lbv2isolver.h"
#include "assert.h"

#include "smt-switch/msat_factory.h"
#include "smt-switch/smt.h"
#include "smt-switch/result.h"

using namespace lbv2i;
using namespace smt;

int main() {
  SmtSolver underlying_solver = smt::MsatSolverFactory::create();

  LBV2ISolver s = LBV2ISolver(underlying_solver);
  s.push();
  s.set_logic("QF_BV");
  Sort bvsort8 = s.make_sort(BV, 8);
  string val = string("01010101");
  Term c = s.make_term(val, bvsort8, 2);

  Term x = s.make_symbol("x", bvsort8);
  Term y = s.make_symbol("y", bvsort8);
  Term z = s.make_symbol("z", bvsort8);
  Term a = s.make_term(Equal, z, s.make_term(BVAdd, y, z));
  Term b = s.make_term(Equal, z, s.make_term(BVAdd, y, z));
  s.assert_formula(a);
  s.assert_formula(b);
  Result r = s.solve();
  assert(r.is_sat());
}
