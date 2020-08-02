
(set-logic QF_BV)
(declare-fun x () (_ BitVec 52))
(declare-fun y () (_ BitVec 52))
(define-fun left () (_ BitVec 52) (bvxor x y))
(define-fun right () (_ BitVec 52) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
