
(set-logic QF_BV)
(declare-fun x () (_ BitVec 5))
(declare-fun y () (_ BitVec 5))
(define-fun mins () (_ BitVec 5) (_ bv16 5))

(define-fun negative ((a (_ BitVec 5))) Bool (bvuge a (_ bv16 5)))
(define-fun abs ((a (_ BitVec 5))) (_ BitVec 5) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 5)) (b (_ BitVec 5))) (_ BitVec 5) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 5) (bvsdiv x y))
(define-fun right () (_ BitVec 5) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
