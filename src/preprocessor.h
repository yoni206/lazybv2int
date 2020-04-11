#pragma once

#include "smt-switch/identity_walker.h"
#include "smt-switch/smt.h"
#include "utils.h"

namespace lbv2i {

class Binarizer : public smt::IdentityWalker
{
  // probably this class will inherit from SMT-Switch-Walker
 public:
  Binarizer(smt::SmtSolver & solver);
  ~Binarizer();

  typedef smt::IdentityWalker super;
  // it will also use the walker infrastructure

  smt::Term process(smt::Term t);

 protected:
  smt::WalkerStepResult visit_term(smt::Term & term) override;

 private:
};

class OpEliminator : public smt::IdentityWalker
{
  // probably this class will inherit from SMT-Switch-Walker
 public:
  OpEliminator(smt::SmtSolver & solver);
  ~OpEliminator();

  typedef smt::IdentityWalker super;
  // it will also use the walker infrastructure

  smt::Term process(smt::Term t);

 protected:
  smt::WalkerStepResult visit_term(smt::Term & term) override;

 private:
};

class DisjointSet
{
public:
  DisjointSet();
  ~DisjointSet();

  void add(smt::Term &a, smt::Term &b);
  smt::Term find(smt::Term &t);

private:
  // member to group's leader
  smt::UnorderedTermMap leader_;
  // group leader to group
  std::unordered_map<smt::Term, smt::UnorderedTermSet> group_;

};

class Preprocessor
{
 public:
  Preprocessor(smt::SmtSolver & solver);
  ~Preprocessor();

  smt::Term process(smt::Term t);

 private:
  // binarizer
  Binarizer bin_;

  // operator eliminator
  OpEliminator opelim_;
};

}  // namespace lbv2i
