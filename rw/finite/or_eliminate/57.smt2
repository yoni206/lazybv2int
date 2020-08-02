
(set-logic QF_BV)
(declare-fun x () (_ BitVec 57))
(declare-fun y () (_ BitVec 57))
(define-fun left () (_ BitVec 57) (bvor x y))
(define-fun right () (_ BitVec 57) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
