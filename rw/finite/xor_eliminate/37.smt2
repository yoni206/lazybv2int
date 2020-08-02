
(set-logic QF_BV)
(declare-fun x () (_ BitVec 37))
(declare-fun y () (_ BitVec 37))
(define-fun left () (_ BitVec 37) (bvxor x y))
(define-fun right () (_ BitVec 37) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
