
(set-logic QF_BV)
(declare-fun x () (_ BitVec 35))
(declare-fun y () (_ BitVec 35))
(define-fun mins () (_ BitVec 35) (_ bv17179869184 35))

(define-fun negative ((a (_ BitVec 35))) Bool (bvuge a (_ bv17179869184 35)))
(define-fun abs ((a (_ BitVec 35))) (_ BitVec 35) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 35)) (b (_ BitVec 35))) (_ BitVec 35) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 35) (bvsrem x y))
(define-fun right () (_ BitVec 35) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
