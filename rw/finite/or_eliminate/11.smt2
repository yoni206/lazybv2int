
(set-logic QF_BV)
(declare-fun x () (_ BitVec 11))
(declare-fun y () (_ BitVec 11))
(define-fun left () (_ BitVec 11) (bvor x y))
(define-fun right () (_ BitVec 11) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)