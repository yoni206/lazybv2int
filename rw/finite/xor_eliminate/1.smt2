
(set-logic QF_BV)
(declare-fun x () (_ BitVec 1))
(declare-fun y () (_ BitVec 1))
(define-fun left () (_ BitVec 1) (bvxor x y))
(define-fun right () (_ BitVec 1) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
