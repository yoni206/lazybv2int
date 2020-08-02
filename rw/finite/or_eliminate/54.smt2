
(set-logic QF_BV)
(declare-fun x () (_ BitVec 54))
(declare-fun y () (_ BitVec 54))
(define-fun left () (_ BitVec 54) (bvor x y))
(define-fun right () (_ BitVec 54) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
