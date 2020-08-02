
(set-logic QF_BV)
(declare-fun x () (_ BitVec 17))
(declare-fun y () (_ BitVec 17))
(define-fun left () (_ BitVec 17) (bvxor x y))
(define-fun right () (_ BitVec 17) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
