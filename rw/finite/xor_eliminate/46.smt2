
(set-logic QF_BV)
(declare-fun x () (_ BitVec 46))
(declare-fun y () (_ BitVec 46))
(define-fun left () (_ BitVec 46) (bvxor x y))
(define-fun right () (_ BitVec 46) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
