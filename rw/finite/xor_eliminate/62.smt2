
(set-logic QF_BV)
(declare-fun x () (_ BitVec 62))
(declare-fun y () (_ BitVec 62))
(define-fun left () (_ BitVec 62) (bvxor x y))
(define-fun right () (_ BitVec 62) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
