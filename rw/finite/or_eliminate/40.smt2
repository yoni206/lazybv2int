
(set-logic QF_BV)
(declare-fun x () (_ BitVec 40))
(declare-fun y () (_ BitVec 40))
(define-fun left () (_ BitVec 40) (bvor x y))
(define-fun right () (_ BitVec 40) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
