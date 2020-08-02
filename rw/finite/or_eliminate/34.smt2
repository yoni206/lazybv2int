
(set-logic QF_BV)
(declare-fun x () (_ BitVec 34))
(declare-fun y () (_ BitVec 34))
(define-fun left () (_ BitVec 34) (bvor x y))
(define-fun right () (_ BitVec 34) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
