#include <functional>
#include <map>

#include "preprocessor.h"

using namespace smt;

namespace lbv2i {

enum RewriteRule
{
 UdivZero,
 SdivEliminate,
 SremEliminate,
 SmodEliminate,
 RepeatEliminate,
 ZeroExtendEliminate,
 SignExtendEliminate,
 RotateRightEliminate,
 RotateLeftEliminate,
 CompEliminate,
 SleEliminate,
 SltEliminate,
 SgtEliminate,
 SgeEliminate,
 ShlByConst,
 LshrByConst
};

// TODO: implement all of these
const std::map<RewriteRule, std::function<bool(const Term & t)>> rr_applies({
 { UdivZero, [](const Term & t) { return false; } },
 { SdivEliminate, [](const Term & t) { return false; } },
 { SremEliminate, [](const Term & t) { return false; } },
 { SmodEliminate, [](const Term & t) { return false; } },
 { RepeatEliminate, [](const Term & t) { return false; } },
 { ZeroExtendEliminate, [](const Term & t) { return false; } },
 { SignExtendEliminate, [](const Term & t) { return false; } },
 { RotateRightEliminate, [](const Term & t) { return false; } },
 { RotateLeftEliminate, [](const Term & t) { return false; } },
 { CompEliminate, [](const Term & t) { return false; } },
 { SleEliminate, [](const Term & t) { return false; } },
 { SltEliminate, [](const Term & t) { return false; } },
 { SgtEliminate, [](const Term & t) { return false; } },
 { SgeEliminate, [](const Term & t) { return false; } },
 { ShlByConst, [](const Term & t) { return false; } },
 { LshrByConst, [](const Term & t) { return false; } }
    });

// TODO: implement all of these
const std::map<RewriteRule, std::function<Term(const Term & t)>> rr_apply({
 { UdivZero, [](const Term & t) { Term res; return res; } },
 { SdivEliminate, [](const Term & t) { Term res; return res; } },
 { SremEliminate, [](const Term & t) { Term res; return res; } },
 { SmodEliminate, [](const Term & t) { Term res; return res; } },
 { RepeatEliminate, [](const Term & t) { Term res; return res; } },
 { ZeroExtendEliminate, [](const Term & t) { Term res; return res; } },
 { SignExtendEliminate, [](const Term & t) { Term res; return res; } },
 { RotateRightEliminate, [](const Term & t) { Term res; return res; } },
 { RotateLeftEliminate, [](const Term & t) { Term res; return res; } },
 { CompEliminate, [](const Term & t) { Term res; return res; } },
 { SleEliminate, [](const Term & t) { Term res; return res; } },
 { SltEliminate, [](const Term & t) { Term res; return res; } },
 { SgtEliminate, [](const Term & t) { Term res; return res; } },
 { SgeEliminate, [](const Term & t) { Term res; return res; } },
 { ShlByConst, [](const Term & t) { Term res; return res; } },
 { LshrByConst, [](const Term & t) { Term res; return res; } }
    });

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
