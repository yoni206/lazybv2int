
(set-logic QF_BV)
(declare-fun x () (_ BitVec 2))
(declare-fun y () (_ BitVec 2))
(define-fun mins () (_ BitVec 2) (_ bv2 2))

(define-fun negative ((a (_ BitVec 2))) Bool (bvuge a (_ bv2 2)))
(define-fun abs ((a (_ BitVec 2))) (_ BitVec 2) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 2)) (b (_ BitVec 2))) (_ BitVec 2) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 2) (bvsrem x y))
(define-fun right () (_ BitVec 2) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
