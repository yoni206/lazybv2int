
(set-logic QF_BV)
(declare-fun x () (_ BitVec 6))
(declare-fun y () (_ BitVec 6))
(define-fun mins () (_ BitVec 6) (_ bv32 6))

(define-fun negative ((a (_ BitVec 6))) Bool (bvuge a (_ bv32 6)))
(define-fun abs ((a (_ BitVec 6))) (_ BitVec 6) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 6)) (b (_ BitVec 6))) (_ BitVec 6) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 6) (bvsdiv x y))
(define-fun right () (_ BitVec 6) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
