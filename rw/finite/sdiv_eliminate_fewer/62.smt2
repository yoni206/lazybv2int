
(set-logic QF_BV)
(declare-fun x () (_ BitVec 62))
(declare-fun y () (_ BitVec 62))
(define-fun mins () (_ BitVec 62) (_ bv2305843009213693952 62))

(define-fun negative ((a (_ BitVec 62))) Bool (bvuge a (_ bv2305843009213693952 62)))
(define-fun abs ((a (_ BitVec 62))) (_ BitVec 62) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 62)) (b (_ BitVec 62))) (_ BitVec 62) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 62) (bvsdiv x y))
(define-fun right () (_ BitVec 62) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
