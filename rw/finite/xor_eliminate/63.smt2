
(set-logic QF_BV)
(declare-fun x () (_ BitVec 63))
(declare-fun y () (_ BitVec 63))
(define-fun left () (_ BitVec 63) (bvxor x y))
(define-fun right () (_ BitVec 63) (bvsub (bvor x y) (bvand x y)))
(assert (distinct left right))
(check-sat)
