
(set-logic QF_BV)
(declare-fun x () (_ BitVec 62))
(declare-fun y () (_ BitVec 62))
(define-fun mins () (_ BitVec 62) (_ bv2305843009213693952 62))

(define-fun negative ((a (_ BitVec 62))) Bool (bvuge a (_ bv2305843009213693952 62)))
(define-fun abs ((a (_ BitVec 62))) (_ BitVec 62) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 62)) (b (_ BitVec 62))) (_ BitVec 62) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 62) (bvsrem x y))
(define-fun right () (_ BitVec 62) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
