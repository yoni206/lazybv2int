
(set-logic QF_BV)
(declare-fun x () (_ BitVec 41))
(declare-fun y () (_ BitVec 41))
(define-fun left () (_ BitVec 41) (bvxor x y))
(define-fun right () (_ BitVec 41) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
