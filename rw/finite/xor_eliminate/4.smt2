
(set-logic QF_BV)
(declare-fun x () (_ BitVec 4))
(declare-fun y () (_ BitVec 4))
(define-fun left () (_ BitVec 4) (bvxor x y))
(define-fun right () (_ BitVec 4) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
