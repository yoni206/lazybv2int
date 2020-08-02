
(set-logic QF_BV)
(declare-fun x () (_ BitVec 13))
(declare-fun y () (_ BitVec 13))
(define-fun left () (_ BitVec 13) (bvxor x y))
(define-fun right () (_ BitVec 13) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
