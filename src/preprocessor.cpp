#include <assert.h>
#include <math.h>

#include <functional>
#include <map>

#include "preprocessor.h"
#include "utils.h"
#include "opts.h"

using namespace smt;
using namespace std;

namespace lbv2i {

Term make_bvneg(SmtSolver& solver, const Term& x) {
          //From Hacker's delight, 2-2
          //addition combined with logical operations
          //item a
          //bvneg x = (bvnot x)+1
  size_t size = x->get_sort()->get_width();
  Term one = solver->make_term(1, solver->make_sort(BV, size));
  Term bvnot = solver->make_term(BVNot, x);
  Term result = solver->make_term(BVAdd, bvnot, one);
  return result;
}

//Returns a boolean term that says that 
//the signed integer value of the bitvector term x is negative
//In other words, that the msb is 1.
//Another way of saying this: x >= 1000000 (where >= is unsigned)
Term make_signed_neg(SmtSolver& solver, const Term& x) {
            size_t size = x->get_sort()->get_width();
            Term constant =
                solver->make_term(utils::pow2_str(size-1), solver->make_sort(BV, size));
            Term condition = solver->make_term(BVUge, x, constant);
            return condition;
}

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
  SubEliminate,
  NegEliminate,
  OrEliminate,
  XorEliminate,
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

        { SubEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVSub;
          } },
        
        { NegEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVNeg;
          } },
        
        { OrEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVOr;
          } },
        
        { XorEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            return t->get_op() == BVXor;
          } }

    });

const std::map<RewriteRule,
               std::function<Term(
                   const Term & t, const TermVec & children, SmtSolver & s)>>
    rr_apply({

        { UdivZero,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Sort sort = t->get_sort();
            Term res =
                s->make_term(std::string(sort->get_width(), '1'), sort, 2);
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
            Term x_uge_0 = make_signed_neg(s, x);
            Term condition = s->make_term(Not, x_uge_0);
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
            Term a_lt_0 = make_signed_neg(s, a);
            Term b_lt_0 = make_signed_neg(s, b);
            Term abs_a = s->make_term(Ite, a_lt_0, make_bvneg(s, a), a);
            Term abs_b = s->make_term(Ite, b_lt_0, make_bvneg(s, b), b);
            Term a_udiv_b = s->make_term(BVUdiv, abs_a, abs_b);
            Term neg_result = make_bvneg(s, a_udiv_b);
            Term condition = s->make_term(Xor, a_lt_0, b_lt_0);
            Term res = s->make_term(Ite, condition, neg_result, a_udiv_b);
            return res;
          } },

        { SremEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            size_t size = t->get_sort()->get_width();

            Term a_lt_0 = make_signed_neg(s, a);
            Term b_lt_0 = make_signed_neg(s, b);
            Term abs_a = s->make_term(Ite, a_lt_0, make_bvneg(s, a), a);
            Term abs_b = s->make_term(Ite, b_lt_0, make_bvneg(s, b), b);
            Term a_urem_b = s->make_term(BVUrem, abs_a, abs_b);
            Term neg_result = make_bvneg(s, a_urem_b);
            Term res = s->make_term(Ite, a_lt_0, neg_result, a_urem_b);
            return res;
          } },

        { SmodEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term a = children[0];
            Term b = children[1];
            size_t size = t->get_sort()->get_width();

            Term abs_a = s->make_term(Ite,
                                      s->make_term(Not, make_signed_neg(s, a)),
                                      a,
                                      make_bvneg(s, a));
            Term abs_b = s->make_term(Ite,
                                      s->make_term(Not, make_signed_neg(s, b)),
                                      b,
                                      make_bvneg(s, b));

            Term u = s->make_term(BVUrem, abs_a, abs_b);
            Term neg_u = make_bvneg(s, u);
            Term cond0 = s->make_term(Equal, u, s->make_term(0, t->get_sort()));
            Term cond1 = s->make_term(And,
                                      s->make_term(Not, make_signed_neg(s, a)),
                                      s->make_term(Not, make_signed_neg(s, b)));
            Term cond2 = s->make_term(And,
                                      make_signed_neg(s, a),
                                      s->make_term(Not, make_signed_neg(s, b)));
            Term cond3 = s->make_term(And,
                                      s->make_term(Not, make_signed_neg(s, a)),
                                      make_signed_neg(s, b));
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
                        s->make_term(Ite, cond3, s->make_term(BVAdd, u, b), neg_u))));
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
            Term neg_sign = make_signed_neg(s, bv);
            Term zeros = s->make_term(0, s->make_sort(BV, amount));
            string p2_str = utils::pow2_str(amount);
            string ones_str = utils::sub_value(p2_str, "1");
            //TODO optimize ones using gmp
            Term ones = s->make_term(ones_str, s->make_sort(BV, amount), 10);
            Term zero_extend = s->make_term(Concat, zeros, bv);
            Term one_extend = s->make_term(Concat, ones, bv);
            Term result = s->make_term(Ite, neg_sign, one_extend, zero_extend);
            return result;
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
        
        { SubEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term negb = make_bvneg(s, children[1]);
            return s->make_term(BVAdd, children[0], negb);
          } },

        { NegEliminate,
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term result = make_bvneg(s, children[0]);
            return result;
          } },

        { OrEliminate,
          //From Hacker's delight, 2-2
          //addition combined with logical operations
          //item h
          //x+y = (x|y)+(x&y) and so
          //x|y = (x+y)-(x&y)
          //to inline the elimination of bvsub, we do
          //x|y = (x+y) + make_bvneg(s, x&y)
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term sum = s->make_term(BVAdd, children);
            Term bvand = s->make_term(BVAnd, children);
            Term bvneg = make_bvneg(s, bvand);
            Term result = s->make_term(BVAdd, sum, bvneg);
            return result;
          } },

        { XorEliminate,
          //From Hacker's delight, 2-2
          //addition combined with logical operations
          //item g
          //x+y = (x xor y)+2*(x&y) and so
          //x xor y = (x+y)-2*(x&y)
          //to inline the elimination of bvsub, we do
          //x xor y = (x+y) + make_bvneg(s, 2*(x&y))
          //but, if the bit-width is 1, then we cannot do
          //2*(x&y). in such a case, this term is just 0.
          [](const Term & t, const TermVec & children, SmtSolver & s) {
            Term sum = s->make_term(BVAdd, children);
            Term bvand = s->make_term(BVAnd, children);
            size_t size = t->get_sort()->get_width();
            Term two_bvand;
            if (size == 1) {
              two_bvand = s->make_term(0, s->make_sort(BV, size));
            } else {
              Term two = s->make_term(2, s->make_sort(BV, size));
              two_bvand = s->make_term(BVMul, two, bvand);
            }
            Term bvneg = make_bvneg(s, two_bvand);
            Term result = s->make_term(BVAdd, sum, bvneg);
            return result;
          } }
    });


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
        // case BVAdd:
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

DisjointSet::DisjointSet()
{
}

DisjointSet::~DisjointSet()
{
}

void DisjointSet::add(Term &a, Term &b)
{
  if (leader_.find(a) != leader_.end()) {
    Term leadera = leader_.at(a);
    UnorderedTermSet & groupa = group_.at(leadera);

    if (leader_.find(b) != leader_.end()) {
      Term leaderb = leader_.at(b);

      if (leadera != leaderb) {
        UnorderedTermSet & groupb = group_.at(leaderb);

        if (leadera <= leaderb) {
          groupa.insert(groupb.begin(), groupb.end());

          for (const Term &t : groupb) {
            leader_[t] = leadera;
          }
          groupb.clear();
          group_.erase(leaderb);

        } else {
          groupb.insert(groupa.begin(), groupa.end());

          for (const Term &t : groupa) {
            leader_[t] = leaderb;
          }
          groupa.clear();
          group_.erase(leadera);
        }
      }

    } else {
      groupa.insert(b);
      leader_[b] = leadera;
    }

  } else if (leader_.find(b) != leader_.end()) {
    Term leaderb = leader_.at(b);
    group_[leaderb].insert(a);
    leader_[a] = leaderb;

  } else {
    leader_[a] = b; //(a->hash() <= b->hash()) ? a : b;
    leader_[b] = b; //(a->hash() <= b->hash()) ? a : b;

    // if (a->hash() <= b->hash()) {
    //   group_[a] = UnorderedTermSet({a, b});
    // } else {
    //   group_[b] = UnorderedTermSet({a, b});
    // }

    group_[a] = UnorderedTermSet({a, b});
  }
}

Term DisjointSet::find(Term &t)
{
  assert(leader_.find(t) != leader_.end());
  return leader_.at(t);
}


TopLevelPropagator::TopLevelPropagator(SmtSolver &s) :
  solver_(s)
{
}

TopLevelPropagator::~TopLevelPropagator()
{
}

Term TopLevelPropagator::process(Term &t, bool preserve_equiv)
{
  DisjointSet ds;
  TermVec conjuncts;
  utils::conjunctive_partition(t, conjuncts);

  UnorderedTermSet relevant;
  for (auto &c : conjuncts) {
    Op op = c->get_op();
    //cout << op << " : " << c << endl;
    if (op.prim_op == Equal && c->get_sort()->get_sort_kind() != BOOL) {
      // cvc4 represent IFF as EQUAL. the second condition is to exclude IFF
      // case
      //cout << c << endl;
      TermVec children;
      for (auto tt : c) {
        children.push_back(tt);
      }

      if ((children[0]->is_symbolic_const() ||
           children[0]->is_value()) &&
          (children[1]->is_symbolic_const() ||
           children[1]->is_value())) {
        Term a, b;
        if (children[0]->is_symbolic_const()) {
          a = children[0];
          b = children[1];
        } else if (children[1]->is_symbolic_const()) {
          a = children[1];
          b = children[0];
        } else {
          continue;
        }
        ds.add(a, b);
        relevant.insert(a);
      }
    }
  }

  Term res = t;
  if (relevant.size() > 0) {
    Term equiv = solver_->make_term(true);
    UnorderedTermMap sigma;
    for (auto k : relevant) {
      Term v = ds.find(k);
      //cout << k << " : " << v << endl;
      if (k != v) {
        sigma[k] = v;
        Term eq = solver_->make_term(Equal, k, v);
        equiv = solver_->make_term(And, equiv, eq);
      }
    }

    res = solver_->substitute(t, sigma);
    if (preserve_equiv) {
      res = solver_->make_term(And, res, equiv);
    }
  }

  return res;
}


Preprocessor::Preprocessor(SmtSolver & solver) :
  bin_(solver),
  opelim_(solver),
  tlprop_(solver)
{
}

Preprocessor::~Preprocessor() {}

Term Preprocessor::process(Term t)
{
  Term res = bin_.process(t); 
  res = opelim_.process(res);
  if (opts.toplevel_propagation) {
    res = tlprop_.process(res, false);
  }

  return res;
}

}  // namespace lbv2i
