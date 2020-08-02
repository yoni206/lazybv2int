
(set-logic QF_BV)
(declare-fun x () (_ BitVec 52))
(declare-fun y () (_ BitVec 52))
(define-fun mins () (_ BitVec 52) (_ bv2251799813685248 52))

(define-fun negative ((a (_ BitVec 52))) Bool (bvuge a (_ bv2251799813685248 52)))
(define-fun abs ((a (_ BitVec 52))) (_ BitVec 52) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 52)) (b (_ BitVec 52))) (_ BitVec 52) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 52) (bvsdiv x y))
(define-fun right () (_ BitVec 52) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
