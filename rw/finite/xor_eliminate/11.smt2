
(set-logic QF_BV)
(declare-fun x () (_ BitVec 11))
(declare-fun y () (_ BitVec 11))
(define-fun left () (_ BitVec 11) (bvxor x y))
(define-fun right () (_ BitVec 11) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
