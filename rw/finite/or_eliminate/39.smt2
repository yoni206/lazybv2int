
(set-logic QF_BV)
(declare-fun x () (_ BitVec 39))
(declare-fun y () (_ BitVec 39))
(define-fun left () (_ BitVec 39) (bvor x y))
(define-fun right () (_ BitVec 39) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
