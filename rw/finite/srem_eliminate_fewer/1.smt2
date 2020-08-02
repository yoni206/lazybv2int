
(set-logic QF_BV)
(declare-fun x () (_ BitVec 1))
(declare-fun y () (_ BitVec 1))
(define-fun mins () (_ BitVec 1) (_ bv1 1))

(define-fun negative ((a (_ BitVec 1))) Bool (bvuge a (_ bv1 1)))
(define-fun abs ((a (_ BitVec 1))) (_ BitVec 1) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 1)) (b (_ BitVec 1))) (_ BitVec 1) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 1) (bvsrem x y))
(define-fun right () (_ BitVec 1) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
