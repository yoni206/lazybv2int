
(set-logic QF_BV)
(declare-fun x () (_ BitVec 4))
(declare-fun y () (_ BitVec 4))
(define-fun mins () (_ BitVec 4) (_ bv8 4))

(define-fun negative ((a (_ BitVec 4))) Bool (bvuge a (_ bv8 4)))
(define-fun abs ((a (_ BitVec 4))) (_ BitVec 4) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 4)) (b (_ BitVec 4))) (_ BitVec 4) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 4) (bvsrem x y))
(define-fun right () (_ BitVec 4) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
