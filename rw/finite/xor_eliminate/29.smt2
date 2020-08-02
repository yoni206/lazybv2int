
(set-logic QF_BV)
(declare-fun x () (_ BitVec 29))
(declare-fun y () (_ BitVec 29))
(define-fun left () (_ BitVec 29) (bvxor x y))
(define-fun right () (_ BitVec 29) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
