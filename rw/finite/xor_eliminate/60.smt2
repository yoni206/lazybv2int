
(set-logic QF_BV)
(declare-fun x () (_ BitVec 60))
(declare-fun y () (_ BitVec 60))
(define-fun left () (_ BitVec 60) (bvxor x y))
(define-fun right () (_ BitVec 60) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
