
(set-logic QF_BV)
(declare-fun x () (_ BitVec 22))
(declare-fun y () (_ BitVec 22))
(define-fun left () (_ BitVec 22) (bvor x y))
(define-fun right () (_ BitVec 22) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
