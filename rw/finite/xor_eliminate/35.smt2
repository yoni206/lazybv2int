
(set-logic QF_BV)
(declare-fun x () (_ BitVec 35))
(declare-fun y () (_ BitVec 35))
(define-fun left () (_ BitVec 35) (bvxor x y))
(define-fun right () (_ BitVec 35) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
