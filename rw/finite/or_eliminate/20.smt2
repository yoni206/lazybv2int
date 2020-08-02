
(set-logic QF_BV)
(declare-fun x () (_ BitVec 20))
(declare-fun y () (_ BitVec 20))
(define-fun left () (_ BitVec 20) (bvor x y))
(define-fun right () (_ BitVec 20) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
