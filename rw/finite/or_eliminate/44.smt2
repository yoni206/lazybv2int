
(set-logic QF_BV)
(declare-fun x () (_ BitVec 44))
(declare-fun y () (_ BitVec 44))
(define-fun left () (_ BitVec 44) (bvor x y))
(define-fun right () (_ BitVec 44) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
