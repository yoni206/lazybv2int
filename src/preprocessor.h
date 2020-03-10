#pragma once

#include "smt-switch/smt.h"
#include "smt-switch/identity_walker.h"

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

/** \class BitwiseOpDefs
 *  Introduces definition symbols for each bitwise operator.
 *  i.e. (bvand x y) becomes bvand_x_y and an assertion
 *  (= bvand_x_y (bvand x y))
 */
class BitwiseOpDefs : public smt::IdentityWalker
{
 public:
  BitwiseOpDefs(smt::SmtSolver & solver);
  ~BitwiseOpDefs();

  typedef smt::IdentityWalker super;

  smt::Term process(smt::Term t);

  const smt::TermVec & get_definitions() const;

 protected:
  smt::WalkerStepResult visit_term(smt::Term & term) override;

 private:
  smt::TermVec definitions_;
};

class Preprocessor
{
 public:
  Preprocessor(smt::SmtSolver & solver);
  ~Preprocessor();

  smt::Term process(smt::Term t);

  const smt::TermVec & get_definitions() const;

 private:
  // binarizer
  Binarizer bin_;

  // operator eliminator
  OpEliminator opelim_;

  // bitwise operator symbol definitions
  BitwiseOpDefs bvopdefs_;
};

}  // namespace lbv2i
