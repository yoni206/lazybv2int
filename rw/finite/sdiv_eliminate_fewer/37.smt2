
(set-logic QF_BV)
(declare-fun x () (_ BitVec 37))
(declare-fun y () (_ BitVec 37))
(define-fun mins () (_ BitVec 37) (_ bv68719476736 37))

(define-fun negative ((a (_ BitVec 37))) Bool (bvuge a (_ bv68719476736 37)))
(define-fun abs ((a (_ BitVec 37))) (_ BitVec 37) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 37)) (b (_ BitVec 37))) (_ BitVec 37) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 37) (bvsdiv x y))
(define-fun right () (_ BitVec 37) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
