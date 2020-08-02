
(set-logic QF_BV)
(declare-fun x () (_ BitVec 36))
(declare-fun y () (_ BitVec 36))
(define-fun left () (_ BitVec 36) (bvxor x y))
(define-fun right () (_ BitVec 36) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
