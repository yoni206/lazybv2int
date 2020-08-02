
(set-logic QF_BV)
(declare-fun x () (_ BitVec 18))
(declare-fun y () (_ BitVec 18))
(define-fun left () (_ BitVec 18) (bvor x y))
(define-fun right () (_ BitVec 18) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
