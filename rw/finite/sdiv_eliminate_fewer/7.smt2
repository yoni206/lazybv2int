
(set-logic QF_BV)
(declare-fun x () (_ BitVec 7))
(declare-fun y () (_ BitVec 7))
(define-fun mins () (_ BitVec 7) (_ bv64 7))

(define-fun negative ((a (_ BitVec 7))) Bool (bvuge a (_ bv64 7)))
(define-fun abs ((a (_ BitVec 7))) (_ BitVec 7) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 7)) (b (_ BitVec 7))) (_ BitVec 7) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 7) (bvsdiv x y))
(define-fun right () (_ BitVec 7) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
