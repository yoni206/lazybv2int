
(set-logic QF_BV)
(declare-fun x () (_ BitVec 15))
(declare-fun y () (_ BitVec 15))
(define-fun left () (_ BitVec 15) (bvxor x y))
(define-fun right () (_ BitVec 15) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
