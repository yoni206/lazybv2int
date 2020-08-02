
(set-logic QF_BV)
(declare-fun x () (_ BitVec 26))
(declare-fun y () (_ BitVec 26))
(define-fun mins () (_ BitVec 26) (_ bv33554432 26))

(define-fun negative ((a (_ BitVec 26))) Bool (bvuge a (_ bv33554432 26)))
(define-fun abs ((a (_ BitVec 26))) (_ BitVec 26) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 26)) (b (_ BitVec 26))) (_ BitVec 26) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 26) (bvsdiv x y))
(define-fun right () (_ BitVec 26) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
