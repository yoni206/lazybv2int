
(set-logic QF_BV)
(declare-fun x () (_ BitVec 50))
(declare-fun y () (_ BitVec 50))
(define-fun left () (_ BitVec 50) (bvor x y))
(define-fun right () (_ BitVec 50) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
