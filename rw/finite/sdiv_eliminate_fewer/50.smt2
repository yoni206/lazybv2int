
(set-logic QF_BV)
(declare-fun x () (_ BitVec 50))
(declare-fun y () (_ BitVec 50))
(define-fun mins () (_ BitVec 50) (_ bv562949953421312 50))

(define-fun negative ((a (_ BitVec 50))) Bool (bvuge a (_ bv562949953421312 50)))
(define-fun abs ((a (_ BitVec 50))) (_ BitVec 50) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 50)) (b (_ BitVec 50))) (_ BitVec 50) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 50) (bvsdiv x y))
(define-fun right () (_ BitVec 50) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
