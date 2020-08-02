
(set-logic QF_BV)
(declare-fun x () (_ BitVec 58))
(declare-fun y () (_ BitVec 58))
(define-fun left () (_ BitVec 58) (bvxor x y))
(define-fun right () (_ BitVec 58) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
