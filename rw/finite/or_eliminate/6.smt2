
(set-logic QF_BV)
(declare-fun x () (_ BitVec 6))
(declare-fun y () (_ BitVec 6))
(define-fun left () (_ BitVec 6) (bvor x y))
(define-fun right () (_ BitVec 6) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
