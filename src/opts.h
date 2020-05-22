#pragma once

#include <string>

namespace lbv2i {

struct Options
{
  uint32_t granularity;
  uint32_t lazy_granularity;
  bool use_sum_bvops;
  bool lazy;
  bool full_refinement;
  bool print_values;
  bool print_sigma_values;
  bool dump;
  bool toplevel_propagation;
  bool s_checker;
  uint32_t s_checker_limit;
  bool s_checker_filter;
  std::string solver;

  Options()
  {
    granularity = 1;
    lazy_granularity = 1;
    use_sum_bvops = true;
    lazy = false;
    full_refinement = false;
    print_values = false;
    print_sigma_values = false;
    solver = "cvc4";
    dump = false;
    toplevel_propagation = false;
    s_checker = false;
    s_checker_limit = 0;
    s_checker_filter = false;
  }
};

// Expose one options object to be used throughout codebase
extern Options opts;

void set_opt(std::string option);

void help_msg(std::string bin_name);

}  // namespace lbv2i
