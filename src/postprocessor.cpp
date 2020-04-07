#include <assert.h>
#include <math.h>

#include <functional>
#include <map>

#include "postprocessor.h"
#include "utils.h"

using namespace smt;
using namespace std;

namespace lbv2i {

// Using simplification and op elimination rewrite rules from CVC4:
// https://github.com/CVC4/CVC4/tree/master/src/theory/bv

bool Moderizer::is_fintmod(Term t) {
  return (t->get_op() == Apply && get_children(t)[0] == utils_->fintmod_);
}

TermVec Moderizer::get_children(Term t) {
  TermVec result(t->begin(), t->end());
  return result;
}




Moderizer::Moderizer(SmtSolver & solver, utils* u) : super(solver, false) {
  utils_ = u;
    rr_applies_[ModFactorOut] = [](const Term & t, const TermVec & children, SmtSolver & s, Moderizer& moderizer) {
  // ((a+b) mod c) mod c <---------- ((a mod c) + (b mod c)) mod c
  /**
   * We need to make sure that: 
   * (1) t has the form: fintmod((fintmod(a, c1) + fintmod(b,c2)), c3)
   * (2) c1=c2=c3
   *
   * first_check: t is an application of fintmod
   * t_first: first argument to the application
   * c3: second argument to the application
   * second_check: t_first is a sum
   * sum_arg1: first argument to the sum
   * sum_arg2: second argument to the sum
   * third_check: sum_arg1 is an application of fintmod
   * c1: the second argument of the application
   * fourth_check: sum_arg2 is an application of fintmod
   * c2: the second argument of the application
   * fifth_check: c1=c2=c3
   */
            bool first_check = moderizer.is_fintmod(t);
            if (!first_check) {
              return false;
            } 
            Term t_first = children[1];
            Term c3 = children[2];
            bool second_check = (t_first->get_op() == Plus);
            if (!second_check) {
              return false;
            }
            Term sum_arg1 = moderizer.get_children(t_first)[0];
            Term sum_arg2 = moderizer.get_children(t_first)[1];
            bool third_check = moderizer.is_fintmod(sum_arg1);
            bool fourth_check = moderizer.is_fintmod(sum_arg2);
            if (!third_check || !fourth_check) {
              return false;
            }
            Term c1 = moderizer.get_children(sum_arg1)[2];
            Term c2 = moderizer.get_children(sum_arg2)[2];
            if (c1 != c2 || c2 != c3 || c1 != c3) {
              return false;
            }
            cout << "panda" << endl;
            return true;
          };



    rr_apply_[ModFactorOut] = 
          [](const Term & t, const TermVec & children, SmtSolver & s, Moderizer& moderizer) {
  // ((a+b) mod c) mod c <---------- ((a mod c) + (b mod c)) mod c

            Term t_first = children[1];
            Term c3 = children[2];
            Term sum_arg1 = moderizer.get_children(t_first)[0];
            Term sum_arg2 = moderizer.get_children(t_first)[1];
            Term a = moderizer.get_children(sum_arg1)[1];
            Term b = moderizer.get_children(sum_arg2)[1];
            Term c1 = moderizer.get_children(sum_arg1)[2];
            Term c2 = moderizer.get_children(sum_arg2)[2];
            assert(c1 == c2 && c2 == c3);
            Term c = c1;
            Term a_plus_b = s->make_term(Plus, a, b);
            Term a_plus_b_mod_c = s->make_term(Apply, moderizer.utils_->fintmod_, a_plus_b, c);
            Term res = s->make_term(Apply, a_plus_b_mod_c, c);
            return res;
          };
}

Moderizer::~Moderizer() {}

Term Moderizer::process(Term t) { return visit(t); }

WalkerStepResult Moderizer::visit_term(Term & term)
{
  if (!preorder_) {
    Op op = term->get_op();
    if (op.is_null()) {
      cache_[term] = term;
      return Walker_Continue;
    }

    TermVec children;
    for (auto tt : term) {
      children.push_back(cache_.at(tt));
    }
    // rebuild it from cached children before rewriting
    Term res = solver_->make_term(term->get_op(), children);

    // now we need to update the op and children (in case the solver
    // rewrote the term internally)
    op = res->get_op();
    children.clear();
    for (auto tt : res)
    {
      children.push_back(tt);
    }

    bool fixpoint;
    do {
      fixpoint = true;

      // iterate over all the rewrite rules and apply applicable ones
      for (int rr_int = 0; rr_int < NUM_REWRITE_RULES; rr_int++) {
        RewriteRule rr = static_cast<RewriteRule>(rr_int);
        if (rr_applies_.at(rr)(res, children, solver_, *this)) {
          fixpoint = false;
          res = rr_apply_.at(rr)(res, children, solver_, *this);
          // update children after rewriting
          children.clear();
          for (auto tt : res) {
            children.push_back(tt);
          }
        }
      }
    } while (!fixpoint);

    cache_[term] = res;
  }
  return Walker_Continue;
}

Postprocessor::Postprocessor(SmtSolver & solver, utils* u) : utils_(u), mod_(solver, u)  {
}

Postprocessor::~Postprocessor() {}

Term Postprocessor::process(Term t)
{
  Term res = mod_.process(t);
  return res;
}

}  // namespace lbv2i
