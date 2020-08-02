
(set-logic QF_BV)
(declare-fun x () (_ BitVec 56))
(declare-fun y () (_ BitVec 56))
(define-fun left () (_ BitVec 56) (bvxor x y))
(define-fun right () (_ BitVec 56) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
