
(set-logic QF_BV)
(declare-fun x () (_ BitVec 14))
(declare-fun y () (_ BitVec 14))
(define-fun mins () (_ BitVec 14) (_ bv8192 14))

(define-fun negative ((a (_ BitVec 14))) Bool (bvuge a (_ bv8192 14)))
(define-fun abs ((a (_ BitVec 14))) (_ BitVec 14) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 14)) (b (_ BitVec 14))) (_ BitVec 14) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 14) (bvsdiv x y))
(define-fun right () (_ BitVec 14) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
