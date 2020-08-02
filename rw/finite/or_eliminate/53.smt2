
(set-logic QF_BV)
(declare-fun x () (_ BitVec 53))
(declare-fun y () (_ BitVec 53))
(define-fun left () (_ BitVec 53) (bvor x y))
(define-fun right () (_ BitVec 53) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
