
(set-logic QF_BV)
(declare-fun x () (_ BitVec 1))
(declare-fun y () (_ BitVec 1))
(define-fun left () (_ BitVec 1) (bvor x y))
(define-fun right () (_ BitVec 1) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
