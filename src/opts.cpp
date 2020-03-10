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
    if (granularity > 8)
    {
      cout << "granularity value " << granularity << " is too large and is unsupported." << endl;
      throw std::exception();
    }
    opts.granularity = granularity;
  } else if (option == "--use-boolcomp-bvops") {
    opts.use_sum_bvops = false;
  } else if (option == "--introduce-bvop-symbols") {
    opts.introduce_bvop_symbols = true;
  } else {
    cout << "Unrecognized option: " << option << endl;
    throw std::exception();
  }
}

void help_msg(string bin_name)
{
  cout << "usage: " << bin_name << " [options] <filename>"
       << "\noptions:"
       << "\n\t--granularity=[1-8] : sets granularity of int blocks"
       << "\n\t--use-boolcomp-bvops : use comparisons between integer "
          "representation of bits instead of a sum"
       << "\n\t--introduce-bvop-symbols : introduce a new symbol for each bv op"
       << endl;
}

}  // namespace lbv2i
