
(set-logic QF_BV)
(declare-fun x () (_ BitVec 5))
(declare-fun y () (_ BitVec 5))
(define-fun left () (_ BitVec 5) (bvxor x y))
(define-fun right () (_ BitVec 5) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
