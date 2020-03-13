#pragma once

#include <string>

namespace lbv2i {

struct Options
{
  uint32_t granularity;
  bool use_sum_bvops;
  bool lazy;

  Options()
  {
    granularity = 1;
    use_sum_bvops = true;
    lazy = false;
  }
};

// Expose one options object to be used throughout codebase
extern Options opts;

void set_opt(std::string option);

void help_msg(std::string bin_name);

}  // namespace lbv2i
