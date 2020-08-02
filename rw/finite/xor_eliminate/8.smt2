
(set-logic QF_BV)
(declare-fun x () (_ BitVec 8))
(declare-fun y () (_ BitVec 8))
(define-fun left () (_ BitVec 8) (bvxor x y))
(define-fun right () (_ BitVec 8) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
