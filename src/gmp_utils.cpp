#include "gmp_utils.h"

using namespace smt;
using namespace std;
namespace utils {
static string pow2_str(uint64_t k)
{
  mpz_t base, p;
  mpz_inits(base, p, NULL);
  mpz_set_str(base, "2", 10);
  mpz_pow_ui(p, base, k);

  mpz_class res(p);

  mpz_clear(p);
  mpz_clear(base);

  return res.get_str();
}

Term pow2(uint64_t k, SmtSolver s) {
  string pow_bv_width_str = pow2_str(k);
  Sort int_sort = s->make_sort(INT);
  return s->make_term(pow_bv_width_str, int_sort);
}
}
