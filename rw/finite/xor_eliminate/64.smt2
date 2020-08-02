
(set-logic QF_BV)
(declare-fun x () (_ BitVec 64))
(declare-fun y () (_ BitVec 64))
(define-fun left () (_ BitVec 64) (bvxor x y))
(define-fun right () (_ BitVec 64) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
