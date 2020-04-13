#include "opts.h"

// TODO : remove this
#include <iostream>

using namespace std;

namespace lbv2i {

// declar a global Options object
Options opts = Options();

void set_opt(string option)
{
  if (option.rfind("--granularity=", 0) == 0) {
    uint32_t granularity = stoi(option.substr(14, option.length() - 14));
    if (granularity > 8) {
      cout << "granularity value " << granularity
           << " is too large and is unsupported." << endl;
      throw std::exception();
    }
    opts.granularity = granularity;
  } else if (option.rfind("--lazy-granularity=", 0) == 0) {
    uint32_t granularity = stoi(option.substr(19, option.length() - 19));
    opts.lazy_granularity = granularity;
  } else if (option == "--use-boolcomp-bvops") {
    opts.use_sum_bvops = false;
  } else if (option == "--lazy") {
    opts.lazy = true;
  } else if (option == "--full-refinement") {
    opts.full_refinement = true;
  } else if (option == "--print-values") {
    opts.print_values = true;
  } else if (option == "--print-sigma-values") {
    opts.print_sigma_values = true;
  } else if (option == "--cvc4" || option == "--msat") {
    opts.solver = option.erase(0, 2);
  } else if (option == "--dump") {
    opts.dump = true;
  } else if (option == "--toplevel-prop") {
    opts.toplevel_propagation = true;
  } else {
    cout << "Unrecognized option: " << option << endl;
    throw std::exception();
  }
}

void help_msg(string bin_name)
{
  cout
      << "usage: " << bin_name << " [options] <filename>"
      << "\noptions:"
      << "\n\t--granularity=[1-8] : sets granularity of int blocks"
      << "\n\t--lazy-granularity=[1-inf] : sets granularity of int blocks "
         "(works only with --lazy option)"
      << "\n\t--use-boolcomp-bvops : use comparisons between integer "
         "representation of bits instead of a sum"
      << "\n\t--lazy : lazily handle bitwise operators "
      << "\n\t--full-refinement : fallback to the eager translation if the "
         "lazy lemmas fail "
      << "\nt\t--print-values : print values of integer variables"
      << "\n\t--print-sigma-values : print values of introduced sigma variables"
      << "\n\t--cvc4 : use cvc4 (default) as the underlying solver "
      << "\n\t--msat : use mathsat as the underlying solver "
      << "\n\t--dump : dump the NIA translation file to tmp.solver.smt2 "
      << "\n\t--toplevel-prop : enable toplevel propagation in preprocessing "
      << endl;
}

}  // namespace lbv2i
