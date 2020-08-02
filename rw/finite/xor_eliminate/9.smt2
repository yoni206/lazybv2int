
(set-logic QF_BV)
(declare-fun x () (_ BitVec 9))
(declare-fun y () (_ BitVec 9))
(define-fun left () (_ BitVec 9) (bvxor x y))
(define-fun right () (_ BitVec 9) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
