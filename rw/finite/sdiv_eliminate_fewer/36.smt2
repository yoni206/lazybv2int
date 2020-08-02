
(set-logic QF_BV)
(declare-fun x () (_ BitVec 36))
(declare-fun y () (_ BitVec 36))
(define-fun mins () (_ BitVec 36) (_ bv34359738368 36))

(define-fun negative ((a (_ BitVec 36))) Bool (bvuge a (_ bv34359738368 36)))
(define-fun abs ((a (_ BitVec 36))) (_ BitVec 36) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 36)) (b (_ BitVec 36))) (_ BitVec 36) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 36) (bvsdiv x y))
(define-fun right () (_ BitVec 36) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
