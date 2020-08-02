
(set-logic QF_BV)
(declare-fun x () (_ BitVec 25))
(declare-fun y () (_ BitVec 25))
(define-fun left () (_ BitVec 25) (bvor x y))
(define-fun right () (_ BitVec 25) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
