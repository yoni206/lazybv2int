#pragma once

#include <functional>
#include <map>

#include "identity_walker.h"
#include "smt-switch/smt.h"
#include "utils.h"

namespace lbv2i {
enum RewriteRule
{
  ModFactorOut= 0,
  // Not meant to be used except for iteration
  NUM_REWRITE_RULES
};

class Moderizer : public IdentityWalker
{
 public:
  Moderizer(smt::SmtSolver & solver, utils* u);
  ~Moderizer();

  typedef IdentityWalker super;

  smt::Term process(smt::Term t);
  bool is_fintmod(smt::Term t);
  smt::TermVec get_children(smt::Term t);

 protected:
  WalkerStepResult visit_term(smt::Term & term) override;

 private:
    utils* utils_;

std::map<
    RewriteRule,
    std::function<bool(const smt::Term & t, const smt::TermVec & c, smt::SmtSolver & s, Moderizer& moderizer)>> rr_applies_;
    std::map<RewriteRule, std::function<smt::Term(const smt::Term & t, const smt::TermVec & children, smt::SmtSolver & s, Moderizer& moderizer)>> rr_apply_;

};

class Postprocessor 
{
 public:
  Postprocessor(smt::SmtSolver & solver, utils* u);
  ~Postprocessor();

  smt::Term process(smt::Term t);

 private:
   Moderizer mod_;
   utils* utils_;

};

}  // namespace lbv2i
