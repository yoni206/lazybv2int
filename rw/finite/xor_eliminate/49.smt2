
(set-logic QF_BV)
(declare-fun x () (_ BitVec 49))
(declare-fun y () (_ BitVec 49))
(define-fun left () (_ BitVec 49) (bvxor x y))
(define-fun right () (_ BitVec 49) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
