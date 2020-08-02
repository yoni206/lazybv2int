
(set-logic QF_BV)
(declare-fun x () (_ BitVec 17))
(declare-fun y () (_ BitVec 17))
(define-fun mins () (_ BitVec 17) (_ bv65536 17))

(define-fun negative ((a (_ BitVec 17))) Bool (bvuge a (_ bv65536 17)))
(define-fun abs ((a (_ BitVec 17))) (_ BitVec 17) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 17)) (b (_ BitVec 17))) (_ BitVec 17) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 17) (bvsdiv x y))
(define-fun right () (_ BitVec 17) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
