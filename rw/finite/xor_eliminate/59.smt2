
(set-logic QF_BV)
(declare-fun x () (_ BitVec 59))
(declare-fun y () (_ BitVec 59))
(define-fun left () (_ BitVec 59) (bvxor x y))
(define-fun right () (_ BitVec 59) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
