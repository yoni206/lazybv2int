#include "preprocessor.h"

using namespace smt;

namespace lbv2i {

Binarizer::Binarizer(SmtSolver & solver) : super(solver, false) {}

Binarizer::~Binarizer() {}

Term Binarizer::process(Term t) { return visit(t); }

WalkerStepResult Binarizer::visit_term(Term & t)
{
  if (!preorder_) {
    PrimOp po = t->get_op().prim_op;
    Term res = t;

    TermVec children;
    switch (po) {
      case BVAnd:
      case BVOr:
      case BVXor:
      case BVAdd:
      case BVMul:
      case Concat:
        children.clear();
        for (auto tt : t) {
          children.push_back(tt);
        }
        res = solver_->make_term(po, children[0], children[1]);
        for (size_t i = 2; i < children.size(); i++) {
          res = solver_->make_term(po, res, children[i]);
        }
        break;
        ;
      default: break; ;
    }

    cache_[t] = res;
  }

  return Walker_Continue;
}

OpEliminator::OpEliminator(SmtSolver & solver) : super(solver, false) {}

OpEliminator::~OpEliminator() {}

Term OpEliminator::process(Term t) { return visit(t); }

WalkerStepResult OpEliminator::visit_term(Term & term)
{
  // TODO: Implement this
  throw std::exception();
}

Preprocessor::Preprocessor(SmtSolver & solver) : bin_(solver), opelim_(solver)
{
}

Preprocessor::~Preprocessor() {}

Term Preprocessor::process(Term t)
{
  Term res = bin_.process(t);
  // TODO: Call OpEliminator here
  return t;
}

}  // namespace lbv2i
