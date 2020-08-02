
(set-logic QF_BV)
(declare-fun x () (_ BitVec 44))
(declare-fun y () (_ BitVec 44))
(define-fun mins () (_ BitVec 44) (_ bv8796093022208 44))

(define-fun negative ((a (_ BitVec 44))) Bool (bvuge a (_ bv8796093022208 44)))
(define-fun abs ((a (_ BitVec 44))) (_ BitVec 44) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 44)) (b (_ BitVec 44))) (_ BitVec 44) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 44) (bvsrem x y))
(define-fun right () (_ BitVec 44) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
