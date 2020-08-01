
import sys
import re
import os
from pathlib import Path
import filter_smtlib as fs

PATTERN = re.compile('\(_ bv(\d+) \d+\)')
MAX_BW=64

def do_replacements(content, bw):
    result = content
    result = result.replace("<bw>", str(bw))
    result = result.replace("<mins>", str(2**(bw - 1)))
    result = result.replace("<maxs>", str((2**bw) - 1))
    return result


def create_formulas():
  result = {}
  result["neg_eliminate"] = \
"""
(set-logic QF_BV)
(declare-fun x () (_ BitVec <bw>))
(define-fun left () (_ BitVec <bw>) (bvneg x))
(define-fun right () (_ BitVec <bw>) (bvadd (bvnot x) (_ bv1 <bw>) ))
(assert (distinct left right))
(check-sat)

"""
  result["or_eliminate"] = \
"""
(set-logic QF_BV)
(declare-fun x () (_ BitVec <bw>))
(declare-fun y () (_ BitVec <bw>))
(define-fun left () (_ BitVec <bw>) (bvor x y))
(define-fun right () (_ BitVec <bw>) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
"""
  result["xor_eliminate"] = \
"""
(set-logic QF_BV)
(declare-fun x () (_ BitVec <bw>))
(declare-fun y () (_ BitVec <bw>))
(define-fun left () (_ BitVec <bw>) (bvxor x y))
(define-fun right () (_ BitVec <bw>) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
"""

  result["sdiv_eliminate_fewer"] = \
"""
(set-logic QF_BV)
(declare-fun x () (_ BitVec <bw>))
(declare-fun y () (_ BitVec <bw>))
(define-fun mins () (_ BitVec <bw>) (_ bv<mins> <bw>))

(define-fun negative ((a (_ BitVec <bw>))) Bool (bvuge a (_ bv<mins> <bw>)))
(define-fun abs ((a (_ BitVec <bw>))) (_ BitVec <bw>) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec <bw>)) (b (_ BitVec <bw>))) (_ BitVec <bw>) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec <bw>) (bvsdiv x y))
(define-fun right () (_ BitVec <bw>) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
"""

  result["srem_eliminate_fewer"] = \
"""
(set-logic QF_BV)
(declare-fun x () (_ BitVec <bw>))
(declare-fun y () (_ BitVec <bw>))
(define-fun mins () (_ BitVec <bw>) (_ bv<mins> <bw>))

(define-fun negative ((a (_ BitVec <bw>))) Bool (bvuge a (_ bv<mins> <bw>)))
(define-fun abs ((a (_ BitVec <bw>))) (_ BitVec <bw>) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec <bw>)) (b (_ BitVec <bw>))) (_ BitVec <bw>) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec <bw>) (bvsdiv x y))
(define-fun right () (_ BitVec <bw>) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
"""

  result["smod_eliminate_fewer"] = \
"""
(set-logic QF_BV)
(declare-fun x () (_ BitVec <bw>))
(declare-fun y () (_ BitVec <bw>))
(define-fun mins () (_ BitVec <bw>) (_ bv<mins> <bw>))
(define-fun negative ((a (_ BitVec <bw>))) Bool (bvuge a (_ bv<mins> <bw>)))
(define-fun abs ((a (_ BitVec <bw>))) (_ BitVec <bw>) (ite (negative a) (bvneg a) a))
(define-fun u ((a (_ BitVec <bw>)) (b (_ BitVec <bw>))) (_ BitVec <bw>) (bvurem (abs a) (abs b)))
(define-fun neg_u ((a (_ BitVec <bw>)) (b (_ BitVec <bw>))) (_ BitVec <bw>) (bvneg (u a b)))
(define-fun cond_0 () Bool (= (u x y) (_ bv0 <bw>)))
(define-fun cond_1 () Bool (and (not (negative x)) (not (negative y))))
(define-fun cond_2 () Bool (and (negative x) (not (negative y))))
(define-fun cond_3 () Bool (and (not (negative x)) (negative y)))
(define-fun left () (_ BitVec <bw>) (bvsmod x y))
(define-fun right () (_ BitVec <bw>) (ite cond_0 (u x y) (ite cond_1 (u x y) (ite cond_2 (bvadd (neg_u x y) y) (ite cond_3 (bvadd (u x y) y) (neg_u x y))))))
(assert (distinct left right))
(check-sat)
"""


  return result

if len(sys.argv) < 2:
    print("arg1: dir to put all files in")
    sys.exit(1)
output_dir = sys.argv[1]
formulas = create_formulas()
for formula_name in formulas:
    dir_of_all_bws = output_dir + "/" + formula_name
    dir_of_all_bws_path = Path(dir_of_all_bws)
    dir_of_all_bws_path.mkdir(parents=True)
    for bw in range(1, MAX_BW+1):
        filename = str(bw) + ".smt2"
        new_path = dir_of_all_bws + "/" + filename
        content = formulas[formula_name]
        new_content = do_replacements(content, bw)
        with open(new_path, "w") as f:
            f.write(new_content)
