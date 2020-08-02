
(set-logic QF_BV)
(declare-fun x () (_ BitVec 41))
(declare-fun y () (_ BitVec 41))
(define-fun mins () (_ BitVec 41) (_ bv1099511627776 41))

(define-fun negative ((a (_ BitVec 41))) Bool (bvuge a (_ bv1099511627776 41)))
(define-fun abs ((a (_ BitVec 41))) (_ BitVec 41) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 41)) (b (_ BitVec 41))) (_ BitVec 41) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 41) (bvsdiv x y))
(define-fun right () (_ BitVec 41) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
