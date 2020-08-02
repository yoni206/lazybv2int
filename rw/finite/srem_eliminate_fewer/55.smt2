
(set-logic QF_BV)
(declare-fun x () (_ BitVec 55))
(declare-fun y () (_ BitVec 55))
(define-fun mins () (_ BitVec 55) (_ bv18014398509481984 55))

(define-fun negative ((a (_ BitVec 55))) Bool (bvuge a (_ bv18014398509481984 55)))
(define-fun abs ((a (_ BitVec 55))) (_ BitVec 55) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 55)) (b (_ BitVec 55))) (_ BitVec 55) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 55) (bvsrem x y))
(define-fun right () (_ BitVec 55) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
