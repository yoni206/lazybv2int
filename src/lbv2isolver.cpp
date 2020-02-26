#include "lbv2isolver.h"

using namespace smt;

namespace lbv2i {

LBV2ISolver::LBV2ISolver(SmtSolver & solver) :
  solver_(solver)
{}

LBV2ISolver::~LBV2ISolver() {}

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

bool LBV2ISolver::set_logic(string logic_name) {solver_->set_logic(logic_name); return true;}


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

Term LBV2ISolver::make_symbol(const std::string name, const Sort & sort) {
  return solver_->make_symbol(name, sort);
}

Sort LBV2ISolver::make_sort(const SortKind sk, uint64_t size) const{
  return solver_->make_sort(sk, size);
}

bool LBV2ISolver::set_opt(string op, string value) {
  solver_->set_opt(op, value);
  return true;
}

bool LBV2ISolver::push() { solver_->push(); return true; }

bool LBV2ISolver::pop() { solver_->pop(); return true; }

bool LBV2ISolver::reset()
{
  solver_->reset_assertions();
  return false;
}

bool LBV2ISolver::assert_formula(Term f)
{
  // preprocess the formula
  Term pre_f = prepro_.process(f);

  // translate
  Term t_f = bv2int_.convert(pre_f);
  solver_->assert_formula(t_f);

  return true;
}

bool LBV2ISolver::refine(smt::TermVec & outlemmas) { return false; }

}  // namespace lbv2i
