
(set-logic QF_BV)
(declare-fun x () (_ BitVec 26))
(declare-fun y () (_ BitVec 26))
(define-fun left () (_ BitVec 26) (bvxor x y))
(define-fun right () (_ BitVec 26) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
