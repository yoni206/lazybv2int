
(set-logic QF_BV)
(declare-fun x () (_ BitVec 14))
(declare-fun y () (_ BitVec 14))
(define-fun left () (_ BitVec 14) (bvor x y))
(define-fun right () (_ BitVec 14) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
