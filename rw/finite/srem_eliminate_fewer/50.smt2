
(set-logic QF_BV)
(declare-fun x () (_ BitVec 50))
(declare-fun y () (_ BitVec 50))
(define-fun mins () (_ BitVec 50) (_ bv562949953421312 50))

(define-fun negative ((a (_ BitVec 50))) Bool (bvuge a (_ bv562949953421312 50)))
(define-fun abs ((a (_ BitVec 50))) (_ BitVec 50) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 50)) (b (_ BitVec 50))) (_ BitVec 50) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 50) (bvsrem x y))
(define-fun right () (_ BitVec 50) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
