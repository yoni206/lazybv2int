
(set-logic QF_BV)
(declare-fun x () (_ BitVec 24))
(declare-fun y () (_ BitVec 24))
(define-fun left () (_ BitVec 24) (bvxor x y))
(define-fun right () (_ BitVec 24) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
