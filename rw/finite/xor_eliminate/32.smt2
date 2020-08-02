
(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(define-fun left () (_ BitVec 32) (bvxor x y))
(define-fun right () (_ BitVec 32) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
