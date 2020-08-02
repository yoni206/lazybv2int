
(set-logic QF_BV)
(declare-fun x () (_ BitVec 30))
(declare-fun y () (_ BitVec 30))
(define-fun left () (_ BitVec 30) (bvxor x y))
(define-fun right () (_ BitVec 30) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
