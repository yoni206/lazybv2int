
(set-logic QF_BV)
(declare-fun x () (_ BitVec 64))
(declare-fun y () (_ BitVec 64))
(define-fun left () (_ BitVec 64) (bvor x y))
(define-fun right () (_ BitVec 64) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
