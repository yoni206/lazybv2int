
(set-logic QF_BV)
(declare-fun x () (_ BitVec 12))
(declare-fun y () (_ BitVec 12))
(define-fun left () (_ BitVec 12) (bvxor x y))
(define-fun right () (_ BitVec 12) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
