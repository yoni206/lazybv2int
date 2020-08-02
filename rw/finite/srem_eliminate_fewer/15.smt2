
(set-logic QF_BV)
(declare-fun x () (_ BitVec 15))
(declare-fun y () (_ BitVec 15))
(define-fun mins () (_ BitVec 15) (_ bv16384 15))

(define-fun negative ((a (_ BitVec 15))) Bool (bvuge a (_ bv16384 15)))
(define-fun abs ((a (_ BitVec 15))) (_ BitVec 15) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 15)) (b (_ BitVec 15))) (_ BitVec 15) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 15) (bvsrem x y))
(define-fun right () (_ BitVec 15) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
