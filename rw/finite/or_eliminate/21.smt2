
(set-logic QF_BV)
(declare-fun x () (_ BitVec 21))
(declare-fun y () (_ BitVec 21))
(define-fun left () (_ BitVec 21) (bvor x y))
(define-fun right () (_ BitVec 21) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
