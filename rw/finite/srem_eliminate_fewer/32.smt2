
(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(define-fun mins () (_ BitVec 32) (_ bv2147483648 32))

(define-fun negative ((a (_ BitVec 32))) Bool (bvuge a (_ bv2147483648 32)))
(define-fun abs ((a (_ BitVec 32))) (_ BitVec 32) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 32)) (b (_ BitVec 32))) (_ BitVec 32) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 32) (bvsrem x y))
(define-fun right () (_ BitVec 32) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
