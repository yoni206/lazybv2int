#pragma once

#include <string>

namespace lbv2i {

struct Options
{
  uint32_t granularity;
  bool use_sum_bvops;
  bool introduce_bvop_symbols;

  Options()
  {
    granularity = 1;
    use_sum_bvops = true;
    introduce_bvop_symbols = false;
  }
};

// Expose one options object to be used throughout codebase
extern Options opts;

void set_opt(std::string option);

void help_msg(std::string bin_name);

}  // namespace lbv2i
