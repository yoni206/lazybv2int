
(set-logic QF_BV)
(declare-fun x () (_ BitVec 49))
(declare-fun y () (_ BitVec 49))
(define-fun mins () (_ BitVec 49) (_ bv281474976710656 49))

(define-fun negative ((a (_ BitVec 49))) Bool (bvuge a (_ bv281474976710656 49)))
(define-fun abs ((a (_ BitVec 49))) (_ BitVec 49) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 49)) (b (_ BitVec 49))) (_ BitVec 49) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 49) (bvsdiv x y))
(define-fun right () (_ BitVec 49) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
