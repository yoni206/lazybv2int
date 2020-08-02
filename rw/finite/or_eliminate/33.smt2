
(set-logic QF_BV)
(declare-fun x () (_ BitVec 33))
(declare-fun y () (_ BitVec 33))
(define-fun left () (_ BitVec 33) (bvor x y))
(define-fun right () (_ BitVec 33) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
