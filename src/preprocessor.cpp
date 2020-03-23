#include "preprocessor.h"

#include <assert.h>
#include <math.h>

#include <functional>
#include <map>

#include "preprocessor.h"
#include "utils.h"

using namespace smt;
using namespace std;

namespace lbv2i {

// Using simplification and op elimination rewrite rules from CVC4:
// https://github.com/CVC4/CVC4/tree/master/src/theory/bv
enum RewriteRule
{
  UdivZero = 0,
  AshrEliminate,
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
  NandEliminate,
  NorEliminate,
  XnorEliminate,
  ShlByConst,
  LshrByConst,
  // Not meant to be used except for iteration
  NUM_REWRITE_RULES
};

const std::map<
    RewriteRule,
    std::function<bool(const Term & t, const TermVec & c, SmtSolver & s)>>
    rr_applies({

        { UdivZero,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVUdiv
                   && children[1] == s->make_term(0, s->make_sort(BV, 1));
          } },

        { AshrEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVAshr;
          } },

        { SdivEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSdiv;
          } },

        { SremEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSrem;
          } },

        { SmodEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSmod;
          } },

        { RepeatEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op().prim_op == Repeat;
          } },

        { ZeroExtendEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op().prim_op == Zero_Extend;
          } },

        { SignExtendEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op().prim_op == Sign_Extend;
          } },

        { RotateRightEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op().prim_op == Rotate_Right;
          } },

        { RotateLeftEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op().prim_op == Rotate_Left;
          } },

        { CompEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVComp;
          } },
        { SleEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSle;
          } },

        { SltEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSlt;
          } },

        { SgtEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSgt;
          } },

        { SgeEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSge;
          } },

        { NandEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVNand;
          } },

        { NorEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVNor;
          } },

        { XnorEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVXnor;
          } },

        { ShlByConst,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVShl && (children[1]->is_value());
          } },

        { LshrByConst,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVLshr && (children[1]->is_value());
          } } });

const std::map<RewriteRule,
               std::function<Term(
                   const Term & t, const TermVec & children, SmtSolver & s)>>
    rr_apply({

        { UdivZero,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term res = s->make_term(
                std::string('1', t->get_sort()->get_width()), t->get_sort(), 2);
            return res;
          } },

        { AshrEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            /*
             * Equivalently:
             *  (bvashr x y) abbreviates
             *      (ite (bvult x 100000...)
             *           (bvlshr x y)
             *           (bvnot (bvlshr (bvnot x) y)))
             */
            size_t size = t->get_sort()->get_width();
            Term x = children[0];
            Term y = children[1];
            Term constant =
                s->make_term(utils::pow2_str(size-1), s->make_sort(BV, size));
            Term condition = s->make_term(BVUlt, x, constant);
            Term first = s->make_term(BVLshr, x, y);
            Term not_x = s->make_term(BVNot, x);
            Term sh = s->make_term(BVLshr, not_x, y);
            Term second = s->make_term(BVNot, sh);
            Term res = s->make_term(Ite, condition, first, second);
            return res;
          } },

        { SdivEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            size_t size = t->get_sort()->get_width();
            Term a = children[0];
            Term b = children[1];
            Term one = s->make_term(1, s->make_sort(BV, 1));
            Op ext_msb(Extract, size - 1, size - 1);
            Term a_lt_0 = s->make_term(Equal, s->make_term(ext_msb, a), one);
            Term b_lt_0 = s->make_term(Equal, s->make_term(ext_msb, b), one);
            Term abs_a = s->make_term(Ite, a_lt_0, s->make_term(BVNeg, a), a);
            Term abs_b = s->make_term(Ite, b_lt_0, s->make_term(BVNeg, b), b);
            Term a_udiv_b = s->make_term(BVUdiv, abs_a, abs_b);
            Term neg_result = s->make_term(BVNeg, a_udiv_b);
            Term condition = s->make_term(Xor, a_lt_0, b_lt_0);
            Term res = s->make_term(Ite, condition, neg_result, a_udiv_b);
            return res;
          } },

        { SremEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            size_t size = t->get_sort()->get_width();

            Term one = s->make_term(1, s->make_sort(BV, 1));
            Op ext_msb(Extract, size - 1, size - 1);
            Term a_lt_0 = s->make_term(Equal, s->make_term(ext_msb, a), one);
            Term b_lt_0 = s->make_term(Equal, s->make_term(ext_msb, b), one);
            Term abs_a = s->make_term(Ite, a_lt_0, s->make_term(BVNeg, a), a);
            Term abs_b = s->make_term(Ite, b_lt_0, s->make_term(BVNeg, b), b);
            Term a_urem_b = s->make_term(BVUrem, abs_a, abs_b);
            Term neg_result = s->make_term(BVNeg, a_urem_b);
            Term res = s->make_term(Ite, a_lt_0, neg_result, a_urem_b);
            return res;
          } },

        { SmodEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            size_t size = t->get_sort()->get_width();

            Op ext_msb(Extract, size - 1, size - 1);
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
                s->make_term(
                    Ite,
                    cond1,
                    u,
                    s->make_term(
                        Ite,
                        cond2,
                        s->make_term(BVAdd, neg_u, b),
                        s->make_term(Ite, s->make_term(BVAdd, u, b), neg_u))));
            return res;
          } },

        { RepeatEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term res = t;
            size_t amount = t->get_op().idx0;

            if (amount == 1) {
              return res;
            }

            for (size_t i = 1; i < amount; ++i) {
              res = s->make_term(Concat, res, t);
            }

            return res;
          } },

        { ZeroExtendEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term bv = children[0];
            size_t amount = t->get_op().idx0;
            if (amount == 0) {
              return bv;
            }

            Term zeros = s->make_term(0, s->make_sort(BV, amount));
            return s->make_term(Concat, zeros, bv);
          } },

        { SignExtendEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term bv = children[0];
            size_t amount = t->get_op().idx0;
            if (amount == 0) {
              return bv;
            }

            size_t size = bv->get_sort()->get_width();
            Term sign_bit = s->make_term(Op(Extract, size - 1, size - 1), bv);
            Term extension = sign_bit;
            for (size_t i = 1; i < amount; ++i) {
              extension = s->make_term(Concat, extension, sign_bit);
            }
            return s->make_term(Concat, extension, bv);
          } },

        { RotateRightEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            size_t amount = t->get_op().idx0;
            if (amount == 0) {
              return a;
            }

            Term left = s->make_term(Op(Extract, amount - 1, 0), a);
            Term right = s->make_term(
                Op(Extract, t->get_sort()->get_width() - 1, amount), a);
            return s->make_term(Concat, left, right);
          } },

        { RotateLeftEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            size_t amount = t->get_op().idx0;
            size_t size = t->get_sort()->get_width();
            amount = amount % size;

            if (amount == 0) {
              return a;
            }

            Term left = s->make_term(Op(Extract, size - 1 - amount, 0), a);
            Term right = s->make_term(Op(Extract, size - 1, size - amount), a);
            return s->make_term(Concat, left, right);
          } },

        { CompEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term comp = s->make_term(Equal, children[0], children[1]);
            Sort bvsort1 = s->make_sort(BV, 1);
            Term one = s->make_term(1, bvsort1);
            Term zero = s->make_term(0, bvsort1);
            return s->make_term(Ite, comp, one, zero);
          } },

        { SleEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            Term b_slt_a = s->make_term(BVSlt, b, a);
            return s->make_term(Not, b_slt_a);
          } },

        { SltEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            size_t size = a->get_sort()->get_width();
            std::string val("1");
            val += std::string(size - 1, '0');
            Term pow_two = s->make_term(val, a->get_sort(), 2);
            a = s->make_term(BVAdd, a, pow_two);
            b = s->make_term(BVAdd, b, pow_two);
            return s->make_term(BVUlt, a, b);
          } },

        { SgtEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            return s->make_term(BVSlt, b, a);
          } },

        { SgeEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            return s->make_term(BVSle, b, a);
          } },

        { NandEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            Term and_term = s->make_term(BVAnd, a, b);
            return s->make_term(BVNot, and_term);
          } },

        { NorEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            Term or_term = s->make_term(BVAnd, a, b);
            return s->make_term(BVNot, or_term);
          } },

        { XnorEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            return s->make_term(Equal, b, a);
          } },

        { ShlByConst,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            // this will throw an exception if the value is not representable
            uint64_t amount = children[1]->to_int();
            Term a = children[0];
            if (amount == 0) {
              return a;
            }
            uint64_t size = a->get_sort()->get_width();

            if (amount >= size) {
              // if shifting more than width, return 0
              return s->make_term(0, a->get_sort());
            }

            Term left = s->make_term(Op(Extract, size - 1 - amount, 0), a);
            Term right = s->make_term(0, s->make_sort(BV, amount));
            return s->make_term(Concat, left, right);
          } },

        { LshrByConst,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            // will throw an exception if amount is not representable as
            // uint64_t
            uint64_t amount = children[1]->to_int();
            Term a = children[0];
            if (amount == 0) {
              return a;
            }
            uint64_t size = a->get_sort()->get_width();

            if (amount >= size) {
              // if shifting more than width, return 0
              return s->make_term(0, a->get_sort());
            }

            Term right = s->make_term(Op(Extract, size - 1, amount), a);
            Term left = s->make_term(0, s->make_sort(BV, amount));
            return s->make_term(Concat, left, right);
          } } });

Binarizer::Binarizer(SmtSolver & solver) : super(solver, false) {}

Binarizer::~Binarizer() {}

Term Binarizer::process(Term t)
{
  Term res = visit(t);
  return res;
}

WalkerStepResult Binarizer::visit_term(Term & t)
{
  if (!preorder_) {
    Op o = t->get_op();
    PrimOp po = o.prim_op;
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
        if (rr_applies.at(rr)(res, children, solver_)) {
          fixpoint = false;
          res = rr_apply.at(rr)(res, children, solver_);
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

Preprocessor::Preprocessor(SmtSolver & solver) : bin_(solver), opelim_(solver)
{
}

Preprocessor::~Preprocessor() {}

Term Preprocessor::process(Term t)
{
  Term res = bin_.process(t);
  res = opelim_.process(res);
  return res;
}

}  // namespace lbv2i
