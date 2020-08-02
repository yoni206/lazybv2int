
(set-logic QF_BV)
(declare-fun x () (_ BitVec 28))
(declare-fun y () (_ BitVec 28))
(define-fun left () (_ BitVec 28) (bvor x y))
(define-fun right () (_ BitVec 28) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
