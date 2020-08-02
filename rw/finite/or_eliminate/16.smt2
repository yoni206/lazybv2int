
(set-logic QF_BV)
(declare-fun x () (_ BitVec 16))
(declare-fun y () (_ BitVec 16))
(define-fun left () (_ BitVec 16) (bvor x y))
(define-fun right () (_ BitVec 16) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
