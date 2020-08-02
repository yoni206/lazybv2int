
(set-logic QF_BV)
(declare-fun x () (_ BitVec 22))
(declare-fun y () (_ BitVec 22))
(define-fun left () (_ BitVec 22) (bvxor x y))
(define-fun right () (_ BitVec 22) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
