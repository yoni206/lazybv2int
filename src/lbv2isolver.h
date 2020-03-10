#pragma once

#include <iostream>

#include "bv2int.h"
#include "preprocessor.h"
#include "axioms.h"

#include "smt-switch/smt.h"
#include "smt-switch/result.h"

namespace lbv2i {

  using namespace std;
  using namespace smt;

class LBV2ISolver : public AbsSmtSolver
{
 public:
  LBV2ISolver(SmtSolver & sovler);
  ~LBV2ISolver();

  Result solve();

  void push(uint64_t num=1);
  void pop(uint64_t num=1);
  void reset();
  void reset_assertions();
  void set_logic(const string logic_name) const;
  void set_opt(string op, string value);
  void assert_formula(const Term& f) const;
  Term get_value(Term& t) const;
  Result check_sat();
  Result check_sat_assuming(const TermVec & assumptions);

  Sort make_sort(const SortKind sk) const;
  Sort make_sort(const std::string name, uint64_t arity) const;
  Sort make_sort(const SortKind sk, uint64_t size) const;
  Sort make_sort(const SortKind sk, const Sort & sort1) const;
  Sort make_sort(const SortKind sk,
                         const Sort & sort1,
                         const Sort & sort2) const;
  Sort make_sort(const SortKind sk,
                         const Sort & sort1,
                         const Sort & sort2,
                         const Sort & sort3) const;
  Sort make_sort(const SortKind sk, const SortVec & sorts) const;

  Term make_symbol(const std::string name, const Sort & sort);
  Term make_term(const Op op, const TermVec & terms) const;
  Term make_term(const Op op, const Term & t) const;
  Term make_term(const Op op,
                         const Term & t0,
                         const Term & t1) const;
  Term make_term(const Op op,
                         const Term & t0,
                         const Term & t1,
                         const Term & t2) const;
  Term make_term(const std::string val,
                 const Sort & sort,
                 uint64_t base = 10);

  Term make_term(bool b) const;
  Term make_term(int64_t i, const Sort & sort) const;
  Term make_term(const Term & val, const Sort & sort) const;
  Term make_term(const std::string val, const Sort & sort, uint64_t base=10) const;
  void run(std::string filename);

 private:
  bool refine(smt::TermVec & outlemmas);
  bool refine_bvand(const smt::TermVec &fterms, smt::TermVec & outlemmas);
  bool refine_bvor(const smt::TermVec &fterms, smt::TermVec & outlemmas);
  bool refine_bvxor(const smt::TermVec &fterms, smt::TermVec & outlemmas);

  // BV2Int Translator
  BV2Int * bv2int_;

  // Preprocessor that will eliminate some bv operators. Note: keep in mind
  // while writing the preprocessor that we want to use it also in the
  // incremental setting (push/pop)
  Preprocessor * prepro_;

  // axioms for refinement
  Axioms axioms_;
  
  // smt-switch solver
  smt::SmtSolver & solver_;
};
}  // namespace lbv2i
