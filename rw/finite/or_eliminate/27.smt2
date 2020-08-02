
(set-logic QF_BV)
(declare-fun x () (_ BitVec 27))
(declare-fun y () (_ BitVec 27))
(define-fun left () (_ BitVec 27) (bvor x y))
(define-fun right () (_ BitVec 27) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
