
(set-logic QF_BV)
(declare-fun x () (_ BitVec 52))
(declare-fun y () (_ BitVec 52))
(define-fun mins () (_ BitVec 52) (_ bv2251799813685248 52))

(define-fun negative ((a (_ BitVec 52))) Bool (bvuge a (_ bv2251799813685248 52)))
(define-fun abs ((a (_ BitVec 52))) (_ BitVec 52) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 52)) (b (_ BitVec 52))) (_ BitVec 52) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 52) (bvsrem x y))
(define-fun right () (_ BitVec 52) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
