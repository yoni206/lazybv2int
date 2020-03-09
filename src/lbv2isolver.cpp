#include "lbv2isolver.h"
#include <assert.h>

using namespace smt;

namespace lbv2i {

LBV2ISolver::LBV2ISolver(SmtSolver & solver) :
  solver_(solver),
  bv2int_(solver, true),
  axioms_(solver),
  prepro_(solver)
{}

LBV2ISolver::~LBV2ISolver() {}

Result LBV2ISolver::check_sat() {
  return solve();
}

Result LBV2ISolver::solve()
{
  TermVec lemmas;

  while (true) {
    Result r = solver_->check_sat();

    if (r.is_unsat()) {
      return r;
    }

    lemmas.clear();
    if (!refine(lemmas)) {
      return r;
    }

    for (auto l : lemmas) {
      solver_->assert_formula(l);
    }
  }
}

void LBV2ISolver::set_logic(const string logic_name) const {solver_->set_logic(logic_name); }

void LBV2ISolver::reset_assertions() {
  solver_->reset_assertions();
}

Term LBV2ISolver::make_term(bool b) const {
  return solver_->make_term(b);
}

Term LBV2ISolver::make_term(int64_t i, const Sort & sort) const {
  return solver_->make_term(i, sort);
}

Term LBV2ISolver::make_term(const Term & val, const Sort & sort) const {
  solver_->make_term(val, sort);
}

Term LBV2ISolver::make_term(const Op op, const TermVec & terms)const 
{
   return solver_->make_term(op, terms);
}

Term LBV2ISolver::make_term(const Op op, const Term & t) const{
   return solver_->make_term(op, t);
}

Term LBV2ISolver::make_term(const Op op, const Term & t0, const Term& t1) const {
   return solver_->make_term(op, t0, t1);
}

Term LBV2ISolver::make_term(const Op op, const Term & t0, const Term& t1, const Term& t2) const {
   return solver_->make_term(op, t0, t1, t2);
}

Term LBV2ISolver::make_term(const string val, const Sort & sort,
                            uint64_t base)
{
  return solver_->make_term(val, sort, base);
}

Term LBV2ISolver::make_symbol(const std::string name, const Sort & sort) {
  return solver_->make_symbol(name, sort);
}

Sort LBV2ISolver::make_sort(const std::string name, uint64_t arity) const {
  return solver_->make_sort(name, arity);
}

Sort LBV2ISolver::make_sort(const SortKind sk) const {
  return solver_->make_sort(sk);
}

Sort LBV2ISolver::make_sort(const SortKind sk, uint64_t size) const { 
  return solver_->make_sort(sk, size);
}

Sort LBV2ISolver::make_sort(const SortKind sk, const Sort & sort1) const {
  return solver_->make_sort(sk, sort1);
}


Sort LBV2ISolver::make_sort(const SortKind sk,
                         const Sort & sort1,
                         const Sort & sort2) const {
  return solver_->make_sort(sk, sort1, sort2);
}

Sort LBV2ISolver::make_sort(const SortKind sk,
                         const Sort & sort1,
                         const Sort & sort2,
                         const Sort & sort3) const {
  return solver_->make_sort(sk, sort1, sort2, sort3);
}


Sort LBV2ISolver::make_sort(const SortKind sk, const SortVec & sorts) const {
  return solver_->make_sort(sk, sorts);
}


void LBV2ISolver::set_opt(string op, string value) {
  solver_->set_opt(op, value);
}

Term LBV2ISolver::get_value(Term& t) {
  //Need to do this by translating back to bv...
  assert(false);
}

void LBV2ISolver::push()
{
  bv2int_.push();
  solver_->push();
}

void LBV2ISolver::pop() {
  bv2int_.push();
  solver_->pop();
}

void LBV2ISolver::reset()
{
  solver_->reset_assertions();
  false;
}

void LBV2ISolver::assert_formula(const Term& f) const
{
  // preprocess the formula
  Term pre_f = prepro_.process(f);

  // translate
  Term t_f = bv2int_.convert(pre_f);
  cout << "panda pre" << pre_f << endl;
  cout << "panda post" << t_f << endl;
  solver_->assert_formula(t_f);
}

bool LBV2ISolver::refine(smt::TermVec & outlemmas) { return false; }

}  // namespace lbv2i
