
(set-logic QF_BV)
(declare-fun x () (_ BitVec 3))
(declare-fun y () (_ BitVec 3))
(define-fun mins () (_ BitVec 3) (_ bv4 3))

(define-fun negative ((a (_ BitVec 3))) Bool (bvuge a (_ bv4 3)))
(define-fun abs ((a (_ BitVec 3))) (_ BitVec 3) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 3)) (b (_ BitVec 3))) (_ BitVec 3) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 3) (bvsdiv x y))
(define-fun right () (_ BitVec 3) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
