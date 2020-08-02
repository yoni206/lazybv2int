
(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(define-fun mins () (_ BitVec 32) (_ bv2147483648 32))

(define-fun negative ((a (_ BitVec 32))) Bool (bvuge a (_ bv2147483648 32)))
(define-fun abs ((a (_ BitVec 32))) (_ BitVec 32) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 32)) (b (_ BitVec 32))) (_ BitVec 32) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 32) (bvsdiv x y))
(define-fun right () (_ BitVec 32) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
