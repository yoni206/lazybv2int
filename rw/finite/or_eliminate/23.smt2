
(set-logic QF_BV)
(declare-fun x () (_ BitVec 23))
(declare-fun y () (_ BitVec 23))
(define-fun left () (_ BitVec 23) (bvor x y))
(define-fun right () (_ BitVec 23) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
