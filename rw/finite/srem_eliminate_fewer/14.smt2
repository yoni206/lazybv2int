
(set-logic QF_BV)
(declare-fun x () (_ BitVec 14))
(declare-fun y () (_ BitVec 14))
(define-fun mins () (_ BitVec 14) (_ bv8192 14))

(define-fun negative ((a (_ BitVec 14))) Bool (bvuge a (_ bv8192 14)))
(define-fun abs ((a (_ BitVec 14))) (_ BitVec 14) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 14)) (b (_ BitVec 14))) (_ BitVec 14) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 14) (bvsrem x y))
(define-fun right () (_ BitVec 14) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
