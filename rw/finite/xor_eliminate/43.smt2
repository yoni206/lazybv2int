
(set-logic QF_BV)
(declare-fun x () (_ BitVec 43))
(declare-fun y () (_ BitVec 43))
(define-fun left () (_ BitVec 43) (bvxor x y))
(define-fun right () (_ BitVec 43) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
