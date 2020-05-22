#pragma once

#include <iostream>

#include "axioms.h"
#include "bv2int.h"
#include "preprocessor.h"
#include "postprocessor.h"
#include "smt-switch/result.h"
#include "smt-switch/smt.h"

namespace lbv2i {

class LBV2ISolver : public smt::AbsSmtSolver
{
 public:
  LBV2ISolver(smt::SmtSolver & solver, bool lazy = false);
  ~LBV2ISolver();

  smt::Result solve();

  void push(uint64_t num = 1);
  void pop(uint64_t num = 1);
  void reset();
  void reset_assertions();
  void set_logic(const std::string logic_name);
  void set_opt(std::string op, std::string value);
  void assert_formula(const smt::Term & f);
  void do_assert_formula();
  void dump_smt2();
  smt::Term get_value(const smt::Term & t) const;
  smt::UnorderedTermMap get_array_values(const smt::Term & arr,
                                         smt::Term & out_const_base) const;
  smt::Result check_sat();
  smt::Result check_sat_assuming(const smt::TermVec & assumptions);

  smt::TermVec get_unsat_core();

  smt::Term substitute(const smt::Term term,
                       const smt::UnorderedTermMap & substitution_map) const;

  smt::Sort make_sort(const smt::SortKind sk) const;
  smt::Sort make_sort(const std::string name, uint64_t arity) const;
  smt::Sort make_sort(const smt::SortKind sk, uint64_t size) const;
  smt::Sort make_sort(const smt::SortKind sk, const smt::Sort & sort1) const;
  smt::Sort make_sort(const smt::SortKind sk,
                      const smt::Sort & sort1,
                      const smt::Sort & sort2) const;
  smt::Sort make_sort(const smt::SortKind sk,
                      const smt::Sort & sort1,
                      const smt::Sort & sort2,
                      const smt::Sort & sort3) const;
  smt::Sort make_sort(const smt::SortKind sk, const smt::SortVec & sorts) const;

  smt::Term make_symbol(const std::string name, const smt::Sort & sort);
  smt::Term make_term(const smt::Op op, const smt::TermVec & terms) const;
  smt::Term make_term(const smt::Op op, const smt::Term & t) const;
  smt::Term make_term(const smt::Op op,
                      const smt::Term & t0,
                      const smt::Term & t1) const;
  smt::Term make_term(const smt::Op op,
                      const smt::Term & t0,
                      const smt::Term & t1,
                      const smt::Term & t2) const;
  smt::Term make_term(const std::string val,
                      const smt::Sort & sort,
                      uint64_t base = 10);

  smt::Term make_term(bool b) const;
  smt::Term make_term(int64_t i, const smt::Sort & sort) const;
  smt::Term make_term(const smt::Term & val, const smt::Sort & sort) const;
  smt::Term make_term(const std::string val,
                      const smt::Sort & sort,
                      uint64_t base = 10) const;
  void run(std::string filename);
  void run_on_stdin();

 private:
  bool refine(smt::TermVec & outlemmas);
  bool refine_bvand(const smt::TermVec & fterms, smt::TermVec & outlemmas);

  void refine_final_shift(const smt::TermVec & fterms,
                          smt::TermVec & outlemmas);

  bool refine_bvlshift(const smt::TermVec & fterms, smt::TermVec & outlemmas);
  bool refine_bvrshift(const smt::TermVec & fterms, smt::TermVec & outlemmas);
  bool refine_final_bw(smt::Op op, const smt::TermVec & fterms,
                       smt::TermVec & outlemmas);

  bool try_sat_check(smt::TermVec &outlemmas);

  // print result and values based on options
  void print_result(smt::Result res) const;

  // BV2Int Translator
  BV2Int * bv2int_;

  // Preprocessor that will eliminate some bv operators. Note: keep in mind
  // while writing the preprocessor that we want to use it also in the
  // incremental setting (push/pop)
  Preprocessor * prepro_;
  

  // Postprocessor that will eliminate some integer operators. Note: keep in mind
  // while writing the postprocessor that we want to use it also in the
  // incremental setting (push/pop)
  Postprocessor * postpro_;

  // axioms for refinement
  Axioms axioms_;

  // smt-switch solver
  smt::SmtSolver & solver_;
  smt::SmtSolver s_checker_;
  // term transfer to s_checker
  smt::TermTranslator tr_s_checker_;

  // assertion stack
  smt::TermVec orig_assertions_;
  smt::TermVec assertions_;
  smt::TermVec extra_assertions_;
  size_t last_asserted_size_;

  // stack 
  typedef std::tuple<size_t, size_t, size_t> stack_entry_t;
  std::vector<stack_entry_t> stack_;

  bool lazy_;
};

}  // namespace lbv2i
