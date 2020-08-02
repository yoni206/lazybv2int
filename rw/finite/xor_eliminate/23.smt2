
(set-logic QF_BV)
(declare-fun x () (_ BitVec 23))
(declare-fun y () (_ BitVec 23))
(define-fun left () (_ BitVec 23) (bvxor x y))
(define-fun right () (_ BitVec 23) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
