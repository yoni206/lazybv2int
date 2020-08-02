
(set-logic QF_BV)
(declare-fun x () (_ BitVec 42))
(declare-fun y () (_ BitVec 42))
(define-fun left () (_ BitVec 42) (bvxor x y))
(define-fun right () (_ BitVec 42) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
