
(set-logic QF_BV)
(declare-fun x () (_ BitVec 29))
(declare-fun y () (_ BitVec 29))
(define-fun mins () (_ BitVec 29) (_ bv268435456 29))

(define-fun negative ((a (_ BitVec 29))) Bool (bvuge a (_ bv268435456 29)))
(define-fun abs ((a (_ BitVec 29))) (_ BitVec 29) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 29)) (b (_ BitVec 29))) (_ BitVec 29) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 29) (bvsrem x y))
(define-fun right () (_ BitVec 29) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
