
(set-logic QF_BV)
(declare-fun x () (_ BitVec 8))
(declare-fun y () (_ BitVec 8))
(define-fun mins () (_ BitVec 8) (_ bv128 8))

(define-fun negative ((a (_ BitVec 8))) Bool (bvuge a (_ bv128 8)))
(define-fun abs ((a (_ BitVec 8))) (_ BitVec 8) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 8)) (b (_ BitVec 8))) (_ BitVec 8) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 8) (bvsdiv x y))
(define-fun right () (_ BitVec 8) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
