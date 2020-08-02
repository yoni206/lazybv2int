
(set-logic QF_BV)
(declare-fun x () (_ BitVec 55))
(declare-fun y () (_ BitVec 55))
(define-fun left () (_ BitVec 55) (bvxor x y))
(define-fun right () (_ BitVec 55) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
