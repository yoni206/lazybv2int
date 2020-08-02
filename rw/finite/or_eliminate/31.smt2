
(set-logic QF_BV)
(declare-fun x () (_ BitVec 31))
(declare-fun y () (_ BitVec 31))
(define-fun left () (_ BitVec 31) (bvor x y))
(define-fun right () (_ BitVec 31) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
