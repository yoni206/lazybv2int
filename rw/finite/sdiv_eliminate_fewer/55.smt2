
(set-logic QF_BV)
(declare-fun x () (_ BitVec 55))
(declare-fun y () (_ BitVec 55))
(define-fun mins () (_ BitVec 55) (_ bv18014398509481984 55))

(define-fun negative ((a (_ BitVec 55))) Bool (bvuge a (_ bv18014398509481984 55)))
(define-fun abs ((a (_ BitVec 55))) (_ BitVec 55) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 55)) (b (_ BitVec 55))) (_ BitVec 55) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 55) (bvsdiv x y))
(define-fun right () (_ BitVec 55) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
