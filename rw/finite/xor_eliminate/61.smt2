
(set-logic QF_BV)
(declare-fun x () (_ BitVec 61))
(declare-fun y () (_ BitVec 61))
(define-fun left () (_ BitVec 61) (bvxor x y))
(define-fun right () (_ BitVec 61) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
