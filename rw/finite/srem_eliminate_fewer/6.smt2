
(set-logic QF_BV)
(declare-fun x () (_ BitVec 6))
(declare-fun y () (_ BitVec 6))
(define-fun mins () (_ BitVec 6) (_ bv32 6))

(define-fun negative ((a (_ BitVec 6))) Bool (bvuge a (_ bv32 6)))
(define-fun abs ((a (_ BitVec 6))) (_ BitVec 6) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 6)) (b (_ BitVec 6))) (_ BitVec 6) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 6) (bvsrem x y))
(define-fun right () (_ BitVec 6) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
