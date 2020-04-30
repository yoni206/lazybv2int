#pragma once

#include "smt-switch/identity_walker.h"
#include "smt-switch/smt.h"
#include "utils.h"

namespace lbv2i {


class BV2Int : smt::IdentityWalker
{
 public:
  BV2Int(smt::SmtSolver & solver, bool clear_cache, bool lazy_bw = false);
  ~BV2Int();

  typedef smt::IdentityWalker super;
  // it will also use the walker infrastructure

  smt::WalkerStepResult visit_term(smt::Term & term);
  smt::Term convert(smt::Term & t);

  void reset();
  void push();
  void pop();
  bool internal(smt::Term uf);

  const smt::Term & fbv_and() const { return utils_.fbvand_; }
  const smt::Term & fbv_lshift() const { return utils_.fbvshl_; }
  const smt::Term & fbv_rshift() const { return utils_.fbvlshr_; }

  const smt::TermVec & fbv_terms() const { return f_bv_terms_; }

  const smt::TermVec & get_extra_assertions() const {
    return extra_assertions_;
  };

  const smt::UnorderedTermSet & get_int_vars() const { return int_vars_; }


  uint64_t granularity() {return granularity_;}
  utils& get_utils() {return utils_;}

  const smt::UnorderedTermMap & get_cache() const { return cache_; }

private:
  smt::Term pow2(uint64_t k);
  smt::Term make_bvnot_term(const smt::Term & x, uint64_t k);
  smt::Term int_max(uint64_t k);
  smt::Term handle_bw_op(const smt::Term & t,
                         uint64_t bv_width,
                         const smt::TermVec & cached_children);
  smt::Term handle_bw_op_lazy(const smt::Term & t,
                              uint64_t bv_width,
                              const smt::TermVec & cached_children);
  smt::Term handle_bw_op_eager(const smt::Term & t,
                               uint64_t bv_width,
                               const smt::TermVec & cached_children);
  smt::Term handle_shift_op(const smt::Term & t,
                               uint64_t bv_width,
                               const smt::TermVec & cached_children);
  bool is_shift_op(smt::Op op);
  smt::Term gen_euclid(smt::Term m, smt::Term n);
  smt::Term gen_mod(const smt::Term &a, const smt::Term &b);
  smt::Term gen_intdiv(const smt::Term &a, const smt::Term &b);

  bool is_bw_op(smt::Op op);

  smt::TermVec extra_assertions_;
  smt::UnorderedTermSet int_vars_;  ///< integer versions of bv vars
  // list of abstract (lazy_bv_op) terms
  smt::TermVec f_bv_terms_;

  typedef std::tuple<smt::UnorderedTermMap, size_t, size_t>
      stack_entry_t;
  std::vector<stack_entry_t> stack_;

  smt::Sort int_sort_;

  smt::Term int_zero_;
  smt::Term int_one_;


  // flag that determines if we handle
  // bitwise operators (and/or/shift/...)
  // lazily or eagerly.
  bool lazy_bw_;

  uint64_t granularity_;


  utils utils_;


  //set of terms of the form 
  //fintdiv_(m,n) or fintmod_(m,n)
  //For each such term, we should assert euclid's equation:
  // (=> (distinct n 0)
  //        (let ((q (div m n)) (r (mod m n)))
  //          (and (= m (+ (* n q) r))
  //               (<= 0 r (- (abs n) 1))))))
  smt::UnorderedTermSet euclid_terms_;
};
}  // namespace lbv2i
