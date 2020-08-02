
(set-logic QF_BV)
(declare-fun x () (_ BitVec 47))
(declare-fun y () (_ BitVec 47))
(define-fun left () (_ BitVec 47) (bvor x y))
(define-fun right () (_ BitVec 47) (bvsub (bvadd x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
