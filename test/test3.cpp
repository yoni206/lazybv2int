#include "lbv2isolver.h"
#include "assert.h"

#include "smt-switch/cvc4_factory.h"
#include "smt-switch/smt.h"
#include "smt-switch/result.h"

using namespace lbv2i;
using namespace smt;

int main() {
  SmtSolver s = smt::CVC4SolverFactory::create();

  s->set_logic("QF_NIA");
  Sort int_sort = s->make_sort(INT);
  Term two = s->make_term(2, int_sort);
  Term x = s->make_symbol("x", int_sort);
  Term y = s->make_symbol("y", int_sort);
  Term x_div_2 = s->make_term(IntDiv, x, y);
  Term f1 = s->make_term(Equal, x, s->make_term("8", int_sort));
  Term f2 = s->make_term(Equal, y, s->make_term("3", int_sort));
  s->assert_formula(s->make_term(And, f1, f2));
  s->assert_formula(s->make_term(Equal, x_div_2, s->make_term("2", int_sort)));
  Result r = s->check_sat();
  cout << "panda " << x_div_2 << endl;
  cout << "panda " << r << endl;
}
