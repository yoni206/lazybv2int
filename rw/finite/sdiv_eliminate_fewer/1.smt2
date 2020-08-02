
(set-logic QF_BV)
(declare-fun x () (_ BitVec 1))
(declare-fun y () (_ BitVec 1))
(define-fun mins () (_ BitVec 1) (_ bv1 1))

(define-fun negative ((a (_ BitVec 1))) Bool (bvuge a (_ bv1 1)))
(define-fun abs ((a (_ BitVec 1))) (_ BitVec 1) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 1)) (b (_ BitVec 1))) (_ BitVec 1) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 1) (bvsdiv x y))
(define-fun right () (_ BitVec 1) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
