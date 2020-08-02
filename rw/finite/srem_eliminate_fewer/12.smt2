
(set-logic QF_BV)
(declare-fun x () (_ BitVec 12))
(declare-fun y () (_ BitVec 12))
(define-fun mins () (_ BitVec 12) (_ bv2048 12))

(define-fun negative ((a (_ BitVec 12))) Bool (bvuge a (_ bv2048 12)))
(define-fun abs ((a (_ BitVec 12))) (_ BitVec 12) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 12)) (b (_ BitVec 12))) (_ BitVec 12) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 12) (bvsrem x y))
(define-fun right () (_ BitVec 12) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
