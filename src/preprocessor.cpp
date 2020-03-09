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
const std::map<RewriteRule, std::function<bool(const Term & t, const TermVec & c, SmtSolver & s)>> rr_applies({

 { UdivZero, [](const Term & t, const TermVec& children, SmtSolver & s)
             {
               return t->get_op() == BVUdiv &&
                 children[1] == s->make_term(0, s->make_sort(BV, 1));
             } },

 { SdivEliminate, [](const Term & t, const TermVec & children, SmtSolver & s)
                  {
                    return t->get_op() == BVSdiv;
                  } },

 { SremEliminate, [](const Term & t, const TermVec & children, SmtSolver & s)
                  {
                    return t->get_op() == BVSrem;
                  } },

 { SmodEliminate, [](const Term & t, const TermVec & children, SmtSolver & s)
                  {
                    return t->get_op() == BVSmod;
                  } },

 { RepeatEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { ZeroExtendEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { SignExtendEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { RotateRightEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { RotateLeftEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { CompEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { SleEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { SltEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { SgtEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { SgeEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { ShlByConst, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } },
 { LshrByConst, [](const Term & t, const TermVec & children, SmtSolver & s) { return false; } }
    });

// TODO: implement all of these
const std::map<RewriteRule, std::function<Term(const Term & t, const TermVec & children, SmtSolver & s)>> rr_apply({

 { UdivZero, [](const Term & t, const TermVec & children, SmtSolver & s)
             {
               Term res = s->make_term(std::string('1', t->get_sort()->get_width()),
                                       t->get_sort(), 2);
               return res;
             } },

 { SdivEliminate, [](const Term & t, const TermVec & children, SmtSolver & s)
                  {
                    size_t size = t->get_sort()->get_width();
                    Term a = children[0];
                    Term b = children[1];
                    Term one = s->make_term(1, s->make_sort(BV, 1));
                    Op ext_msb(Extract, size-1, size-1);
                    Term a_lt_0 = s->make_term(Equal,
                                               s->make_term(ext_msb, a),
                                               one);
                    Term b_lt_0 = s->make_term(Equal,
                                               s->make_term(ext_msb, b),
                                               one);
                    Term abs_a = s->make_term(Ite,
                                              a_lt_0,
                                              s->make_term(BVNeg, a),
                                              a);
                    Term abs_b = s->make_term(Ite,
                                              b_lt_0,
                                              s->make_term(BVNeg, b),
                                              b);
                    Term a_udiv_b = s->make_term(BVUdiv, abs_a, abs_b);
                    Term neg_result = s->make_term(BVNeg, a_udiv_b);
                    Term condition = s->make_term(Xor, a_lt_0, b_lt_0);
                    Term res = s->make_term(Ite, condition, neg_result, a_udiv_b);
                    return res;
                  } },

 { SremEliminate, [](const Term & t, const TermVec & children, SmtSolver & s)
                  {
                    Term a = children[0];
                    Term b = children[1];
                    size_t size = t->get_sort()->get_width();

                    Term one = s->make_term(1, s->make_sort(BV, 1));
                    Op ext_msb(Extract, size-1, size-1);
                    Term a_lt_0 = s->make_term(Equal,
                                               s->make_term(ext_msb, a),
                                               one);
                    Term b_lt_0 = s->make_term(Equal,
                                               s->make_term(ext_msb, b),
                                               one);
                    Term abs_a = s->make_term(Ite,
                                              a_lt_0,
                                              s->make_term(BVNeg, a),
                                              a);
                    Term abs_b = s->make_term(Ite,
                                              b_lt_0,
                                              s->make_term(BVNeg, b),
                                              b);
                    Term a_urem_b = s->make_term(BVUrem, abs_a, abs_b);
                    Term neg_result = s->make_term(BVNeg, a_urem_b);
                    Term res = s->make_term(Ite, a_lt_0, neg_result, a_urem_b);
                    return res;
                  } },

 { SmodEliminate, [](const Term & t, const TermVec & children, SmtSolver & s)
                  {
                    Term a = children[0];
                    Term b = children[1];
                    size_t size = t->get_sort()->get_width();

                    Op ext_msb(Extract, size-1, size-1);
                    Term msb_a = s->make_term(ext_msb, a);
                    Term msb_b = s->make_term(ext_msb, b);

                    Sort bvsort1 = s->make_sort(BV, 1);
                    Term bit1 = s->make_term(1, bvsort1);
                    Term bit0 = s->make_term(0, bvsort1);

                    Term abs_a = s->make_term(Ite,
                                              s->make_term(Equal, msb_a, bit0),
                                              a,
                                              s->make_term(BVNeg, a));
                    Term abs_b = s->make_term(Ite,
                                              s->make_term(Equal, msb_b, bit0),
                                              b,
                                              s->make_term(BVNeg, b));

                    Term u = s->make_term(BVUrem, abs_a, abs_b);
                    Term neg_u = s->make_term(BVNeg, u);
                    Term cond0 = s->make_term(Equal, u, s->make_term(0, t->get_sort()));
                    Term cond1 = s->make_term(And,
                                              s->make_term(Equal, msb_a, bit0),
                                              s->make_term(Equal, msb_b, bit0));
                    Term cond2 = s->make_term(And,
                                              s->make_term(Equal, msb_a, bit1),
                                              s->make_term(Equal, msb_b, bit0));
                    Term cond3 = s->make_term(And,
                                              s->make_term(Equal, msb_a, bit0),
                                              s->make_term(Equal, msb_b, bit1));
                    Term res = s->make_term(
                            Ite,
                            cond0,
                            u,
                            s->make_term(Ite,
                                          cond1,
                                          u,
                                          s->make_term(Ite,
                                                      cond2,
                                                      s->make_term(BVAdd,
                                                                    neg_u,
                                                                    b),
                                                      s->make_term(Ite,
                                                                    s->make_term(BVAdd,
                                                                                u,
                                                                                b),
                                                                    neg_u))));
                    return res;
                  } },
 { RepeatEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { ZeroExtendEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { SignExtendEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { RotateRightEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { RotateLeftEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { CompEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { SleEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { SltEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { SgtEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { SgeEliminate, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { ShlByConst, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } },
 { LshrByConst, [](const Term & t, const TermVec & children, SmtSolver & s) { Term res; return res; } }
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
