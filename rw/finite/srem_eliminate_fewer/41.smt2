
(set-logic QF_BV)
(declare-fun x () (_ BitVec 41))
(declare-fun y () (_ BitVec 41))
(define-fun mins () (_ BitVec 41) (_ bv1099511627776 41))

(define-fun negative ((a (_ BitVec 41))) Bool (bvuge a (_ bv1099511627776 41)))
(define-fun abs ((a (_ BitVec 41))) (_ BitVec 41) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 41)) (b (_ BitVec 41))) (_ BitVec 41) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 41) (bvsrem x y))
(define-fun right () (_ BitVec 41) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
