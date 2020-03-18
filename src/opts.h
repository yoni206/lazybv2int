#pragma once

#include <string>

namespace lbv2i {

struct Options
{
  uint32_t granularity;
  bool use_sum_bvops;
  bool lazy;
  bool full_refinement;
  bool print_values;
  bool print_sigma_values;
  std::string solver;

  Options()
  {
    granularity = 1;
    use_sum_bvops = true;
    lazy = false;
    full_refinement = false;
    print_values = false;
    print_sigma_values = false;
    solver = "cvc4";
  }
};

// Expose one options object to be used throughout codebase
extern Options opts;

void set_opt(std::string option);

void help_msg(std::string bin_name);

}  // namespace lbv2i
