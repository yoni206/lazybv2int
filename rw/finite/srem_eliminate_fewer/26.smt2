
(set-logic QF_BV)
(declare-fun x () (_ BitVec 26))
(declare-fun y () (_ BitVec 26))
(define-fun mins () (_ BitVec 26) (_ bv33554432 26))

(define-fun negative ((a (_ BitVec 26))) Bool (bvuge a (_ bv33554432 26)))
(define-fun abs ((a (_ BitVec 26))) (_ BitVec 26) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 26)) (b (_ BitVec 26))) (_ BitVec 26) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 26) (bvsrem x y))
(define-fun right () (_ BitVec 26) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
