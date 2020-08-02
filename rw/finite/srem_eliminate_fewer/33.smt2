
(set-logic QF_BV)
(declare-fun x () (_ BitVec 33))
(declare-fun y () (_ BitVec 33))
(define-fun mins () (_ BitVec 33) (_ bv4294967296 33))

(define-fun negative ((a (_ BitVec 33))) Bool (bvuge a (_ bv4294967296 33)))
(define-fun abs ((a (_ BitVec 33))) (_ BitVec 33) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 33)) (b (_ BitVec 33))) (_ BitVec 33) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 33) (bvsrem x y))
(define-fun right () (_ BitVec 33) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
