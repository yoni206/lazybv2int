
(set-logic QF_BV)
(declare-fun x () (_ BitVec 35))
(declare-fun y () (_ BitVec 35))
(define-fun mins () (_ BitVec 35) (_ bv17179869184 35))

(define-fun negative ((a (_ BitVec 35))) Bool (bvuge a (_ bv17179869184 35)))
(define-fun abs ((a (_ BitVec 35))) (_ BitVec 35) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 35)) (b (_ BitVec 35))) (_ BitVec 35) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 35) (bvsdiv x y))
(define-fun right () (_ BitVec 35) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
