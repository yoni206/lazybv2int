
(set-logic QF_BV)
(declare-fun x () (_ BitVec 36))
(declare-fun y () (_ BitVec 36))
(define-fun left () (_ BitVec 36) (bvor x y))
(define-fun right () (_ BitVec 36) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
