
(set-logic QF_BV)
(declare-fun x () (_ BitVec 38))
(declare-fun y () (_ BitVec 38))
(define-fun mins () (_ BitVec 38) (_ bv137438953472 38))

(define-fun negative ((a (_ BitVec 38))) Bool (bvuge a (_ bv137438953472 38)))
(define-fun abs ((a (_ BitVec 38))) (_ BitVec 38) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 38)) (b (_ BitVec 38))) (_ BitVec 38) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 38) (bvsrem x y))
(define-fun right () (_ BitVec 38) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
