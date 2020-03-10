#include "lbv2isolver.h"
#include "smtlibmsatparser.h"
#include <assert.h>

using namespace smt;

namespace lbv2i {

LBV2ISolver::LBV2ISolver(SmtSolver & solver) :
  solver_(solver),
  bv2int_(new BV2Int(solver, true)),
  axioms_(solver, bv2int_->fbv_and(), bv2int_->fbv_or(), bv2int_->fbv_xor()),
  prepro_(new Preprocessor(solver))
{}

LBV2ISolver::~LBV2ISolver() {
  delete bv2int_;
  delete prepro_;
}

Result LBV2ISolver::check_sat() {
  return solve();
}

Result LBV2ISolver::check_sat_assuming(const TermVec & assumptions)
{
  push();
  for (auto a : assumptions)
  {
    assert_formula(a);
  }
  Result r = check_sat();
  pop();
  return r;
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
  return solver_->make_term(val, sort);
}

Term LBV2ISolver::make_term(const std::string val, const Sort & sort, uint64_t base) const
{
  return solver_->make_term(val, sort, base);
}

Term LBV2ISolver::make_term(const Op op, const TermVec & terms)const
{
  return solver_->make_term(op, terms);
}

Term LBV2ISolver::make_term(const Op op, const Term & t) const
{
  return solver_->make_term(op, t);
}

Term LBV2ISolver::make_term(const Op op, const Term & t0, const Term & t1) const
{
  return solver_->make_term(op, t0, t1);
}

Term LBV2ISolver::make_term(const Op op,
                            const Term & t0,
                            const Term & t1,
                            const Term & t2) const
{
  return solver_->make_term(op, t0, t1, t2);
}

Term LBV2ISolver::make_term(const string val, const Sort & sort, uint64_t base)
{
  return solver_->make_term(val, sort, base);
}

Term LBV2ISolver::make_symbol(const std::string name, const Sort & sort)
{
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

Term LBV2ISolver::get_value(Term& t) const {
  //Need to do this by translating back to bv...
  assert(false);
}

void LBV2ISolver::push(uint64_t num)
{
  for (size_t i = 0; i < num; i++)
  {
    bv2int_->push();
  }
  solver_->push(num);
}

void LBV2ISolver::pop(uint64_t num) {
  for (size_t i = 0; i < num; i++)
  {
    bv2int_->pop();
  }
  solver_->pop(num);
}

void LBV2ISolver::reset()
{
  solver_->reset();
}

void LBV2ISolver::assert_formula(const Term& f) const
{
  // preprocess the formula
  Term pre_f = prepro_->process(f);

  // translate
  Term t_f = bv2int_->convert(pre_f);
  cout << "panda pre" << pre_f << endl;
  cout << "panda post" << t_f << endl;
  solver_->assert_formula(t_f);
}

bool LBV2ISolver::refine(TermVec & outlemmas)
{
  const TermVec &fbv_terms = bv2int_->fbv_terms();
  const Term &fbv_and = bv2int_->fbv_and();
  const Term &fbv_or = bv2int_->fbv_or();
  const Term &fbv_xor = bv2int_->fbv_xor();

  TermVec fbvand_terms, fbvor_terms, fbvxor_terms;
  for (Term f : fbv_terms) {
    // TODO: check for spurious terms
    Term fsymbol = *(f->begin());
    if (fsymbol == fbv_and) {
      fbvand_terms.push_back(f);
    } else if (fsymbol == fbv_or) {
      fbvor_terms.push_back(f);
    } else if (fsymbol == fbv_xor) {
      fbvxor_terms.push_back(f);
    } else {
      assert(false);
    }
  }

  return false;
}

bool LBV2ISolver::refine_bvand(TermVec &outlemmas)
{
  return false;
}

bool LBV2ISolver::refine_bvor(TermVec &outlemmas)
{
  return false;
}

bool LBV2ISolver::refine_bvxor(TermVec &outlemmas)
{
  return false;
}

void LBV2ISolver::run(string filename)
{
  TermTranslator tr(solver_);
  FILE * f = fopen(filename.c_str(), "r");
  Term assert_term = parse_smt2(f, tr);
  assert_formula(assert_term);
  check_sat();
}

}  // namespace lbv2i
