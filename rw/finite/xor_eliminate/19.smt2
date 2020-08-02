
(set-logic QF_BV)
(declare-fun x () (_ BitVec 19))
(declare-fun y () (_ BitVec 19))
(define-fun left () (_ BitVec 19) (bvxor x y))
(define-fun right () (_ BitVec 19) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
