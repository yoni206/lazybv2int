#include <iostream>
#include "stdio.h"

#include "msat/include/msat_term.h"
#include "smtlibmsatparser.h"

using namespace smt;
using namespace std;

namespace lbv2i {

Term parse_smt2(FILE * f, TermTranslator tr)
{
  msat_config cfg = msat_create_config();
  msat_env env = msat_create_env(cfg);
  msat_term res = msat_from_smtlib2_file(env, f);

  if (MSAT_ERROR_TERM(res)) {
    std::cout << "got error term after parsing" << std::endl;
    throw std::exception();
  }

  Term mterm(new MsatTerm(env, res));
  Term transferred_term = tr.transfer_term(mterm);
  msat_destroy_env(env);
  msat_destroy_config(cfg);
  return transferred_term;
}

}  // namespace lbv2i
