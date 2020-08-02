
(set-logic QF_BV)
(declare-fun x () (_ BitVec 38))
(declare-fun y () (_ BitVec 38))
(define-fun left () (_ BitVec 38) (bvor x y))
(define-fun right () (_ BitVec 38) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
