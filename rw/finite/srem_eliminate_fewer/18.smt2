
(set-logic QF_BV)
(declare-fun x () (_ BitVec 18))
(declare-fun y () (_ BitVec 18))
(define-fun mins () (_ BitVec 18) (_ bv131072 18))

(define-fun negative ((a (_ BitVec 18))) Bool (bvuge a (_ bv131072 18)))
(define-fun abs ((a (_ BitVec 18))) (_ BitVec 18) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 18)) (b (_ BitVec 18))) (_ BitVec 18) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 18) (bvsrem x y))
(define-fun right () (_ BitVec 18) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
