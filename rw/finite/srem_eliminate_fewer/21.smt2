
(set-logic QF_BV)
(declare-fun x () (_ BitVec 21))
(declare-fun y () (_ BitVec 21))
(define-fun mins () (_ BitVec 21) (_ bv1048576 21))

(define-fun negative ((a (_ BitVec 21))) Bool (bvuge a (_ bv1048576 21)))
(define-fun abs ((a (_ BitVec 21))) (_ BitVec 21) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 21)) (b (_ BitVec 21))) (_ BitVec 21) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 21) (bvsrem x y))
(define-fun right () (_ BitVec 21) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
