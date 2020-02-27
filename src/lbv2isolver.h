#pragma once

#include <iostream>
#include "bv2int.h"
#include "preprocessor.h"
#include "smt-switch/smt.h"
#include "smt-switch/result.h"

namespace lbv2i {

  using namespace std;
  using namespace smt;

class LBV2ISolver
{
 public:
  LBV2ISolver(SmtSolver & sovler);
  ~LBV2ISolver();

  Result solve();

  bool push();
  bool pop();
  bool reset();
  bool set_logic(string logic_name);
  bool set_opt(string op, string value);
  bool assert_formula(Term f);
  Result check_sat();

  Sort make_sort(const SortKind sk, uint64_t size) const;
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
 private:
  bool refine(TermVec & outlemmas);

  // BV2Int Translator
  BV2Int bv2int_;

  // Preprocessor that will eliminate some bv operators. Note: keep in mind
  // while writing the preprocessor that we want to use it also in the
  // incremental setting (push/pop)
  Preprocessor prepro_;

  // smt-switch solver
  smt::SmtSolver & solver_;
};
}  // namespace lbv2i
