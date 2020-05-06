#pragma once

#include "smt-switch/smt.h"

namespace lbv2i {

class Axioms
{
 public:
  Axioms(smt::SmtSolver & solver,
         const smt::Term & fbvand);
  ~Axioms();

  // we assume that the term t looks like "fbvand(bitwidth, x, y)"
  // note the function name
  bool check_bvand_symmetry(const smt::Term & t, smt::TermVec & outlemmas);
  bool check_bvand_base_case(const smt::Term & t, smt::TermVec & outlemmas);
  bool check_bvand_minmax(const smt::Term & t,
                          bool is_max,
                          smt::TermVec & outlemmas);
  bool check_bvand_idempotence(const smt::Term & t, smt::TermVec & outlemmas);
  bool check_bvand_contradiction(const smt::Term & t, smt::TermVec & outlemmas);
  // we don't need symmetry if we sort the arguments

  bool check_bvand_difference(const smt::Term & t1,
                              const smt::Term & t2,
                              smt::TermVec & outlemmas);
  // t1 and t2 have same bitwidth and also have a common argument

  bool check_bvand_range(const smt::Term & t, smt::TermVec & outlemmas);

  bool check_bvand_bnw(const smt::Term & t, smt::TermVec & outlemmas);

  bool check_bvshift_zero(const smt::Term & t, smt::TermVec & outlemmas);

  bool check_bvlshift_range(const smt::Term & t, smt::TermVec & outlemmas);
  bool check_bvlshift_zero(const smt::Term & t, smt::TermVec & outlemmas);

  bool check_bvrshift_range(const smt::Term & t, smt::TermVec & outlemmas);
  bool check_bvrshift_zero(const smt::Term & t, smt::TermVec & outlemmas);

 private:
  smt::Term pow2_minus_one(uint64_t k);

  smt::Term make_eq(const smt::Term & x, const smt::Term & y);
  smt::Term make_neq(const smt::Term & x, const smt::Term & y);
  smt::Term make_implies(const smt::Term & x, const smt::Term & y);

  void add_if_voilated(smt::Term & l, smt::TermVec & out);

  smt::SmtSolver & solver_;

  smt::Term fbvand_;

  smt::Sort int_sort_;

  smt::Term false_;
  smt::Term zero_;

};  // class axioms

}  // namespace lbv2i
