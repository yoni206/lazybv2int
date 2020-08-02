
(set-logic QF_BV)
(declare-fun x () (_ BitVec 48))
(declare-fun y () (_ BitVec 48))
(define-fun left () (_ BitVec 48) (bvor x y))
(define-fun right () (_ BitVec 48) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
