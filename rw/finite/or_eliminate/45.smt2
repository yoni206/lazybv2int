
(set-logic QF_BV)
(declare-fun x () (_ BitVec 45))
(declare-fun y () (_ BitVec 45))
(define-fun left () (_ BitVec 45) (bvor x y))
(define-fun right () (_ BitVec 45) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
