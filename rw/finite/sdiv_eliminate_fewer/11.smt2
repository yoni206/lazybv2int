
(set-logic QF_BV)
(declare-fun x () (_ BitVec 11))
(declare-fun y () (_ BitVec 11))
(define-fun mins () (_ BitVec 11) (_ bv1024 11))

(define-fun negative ((a (_ BitVec 11))) Bool (bvuge a (_ bv1024 11)))
(define-fun abs ((a (_ BitVec 11))) (_ BitVec 11) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 11)) (b (_ BitVec 11))) (_ BitVec 11) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 11) (bvsdiv x y))
(define-fun right () (_ BitVec 11) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
