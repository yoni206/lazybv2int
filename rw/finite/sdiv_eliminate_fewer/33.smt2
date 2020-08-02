
(set-logic QF_BV)
(declare-fun x () (_ BitVec 33))
(declare-fun y () (_ BitVec 33))
(define-fun mins () (_ BitVec 33) (_ bv4294967296 33))

(define-fun negative ((a (_ BitVec 33))) Bool (bvuge a (_ bv4294967296 33)))
(define-fun abs ((a (_ BitVec 33))) (_ BitVec 33) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 33)) (b (_ BitVec 33))) (_ BitVec 33) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 33) (bvsdiv x y))
(define-fun right () (_ BitVec 33) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
