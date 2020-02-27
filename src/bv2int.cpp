#include "bv2int.h"

using namespace smt;

namespace lbv2i {

BV2Int::BV2Int(SmtSolver & solver, bool clear_cache) :
  super(solver, clear_cache)
{}

BV2Int::~BV2Int() {}


WalkerStepResult BV2Int::visit_term(Term& term) {
  if (!preorder_) {
    Op op = term->get_op();
    if (!op.is_null()) {
      //term has children
      TermVec cached_children;
      for (auto t : term) {
        cached_children.push_back(cache_.at(t));
      }
      switch (op) {
        case BVAdd:
          {
            cache_[term] = solver_->make_term()
            break;
          }
    
      }
    }
  }
}

Term BV2Int::convert(Term t)
{
  Term res;
  return t;
}

}  // namespace lbv2i
