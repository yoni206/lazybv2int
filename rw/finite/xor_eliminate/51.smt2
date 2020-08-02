
(set-logic QF_BV)
(declare-fun x () (_ BitVec 51))
(declare-fun y () (_ BitVec 51))
(define-fun left () (_ BitVec 51) (bvxor x y))
(define-fun right () (_ BitVec 51) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
