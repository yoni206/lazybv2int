
(set-logic QF_BV)
(declare-fun x () (_ BitVec 3))
(declare-fun y () (_ BitVec 3))
(define-fun left () (_ BitVec 3) (bvor x y))
(define-fun right () (_ BitVec 3) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
