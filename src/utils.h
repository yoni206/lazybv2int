#pragma once

#include <gmpxx.h>
#include "smt-switch/smt.h"


class utils{

public:
  utils(smt::SmtSolver& solver);
  ~utils() {};
  smt::Term pow2(uint64_t k);
  smt::Term gen_intdiv(const smt::Term &a, const smt::Term &b, smt::TermVec& side_effects);
  smt::Term gen_mod(const smt::Term &a, const smt::Term &b, smt::TermVec& side_effects);
  static std::string pow2_str(uint64_t k);

private:
  smt::Term gen_euclid(smt::Term m, smt::Term n);



  smt::SmtSolver & solver_;
  smt::Sort int_sort_;
  smt::Term fintdiv_;
  smt::Term fintmod_;
  smt::Term int_zero_;
  smt::Term int_one_;

};
