
(set-logic QF_BV)
(declare-fun x () (_ BitVec 23))
(declare-fun y () (_ BitVec 23))
(define-fun mins () (_ BitVec 23) (_ bv4194304 23))

(define-fun negative ((a (_ BitVec 23))) Bool (bvuge a (_ bv4194304 23)))
(define-fun abs ((a (_ BitVec 23))) (_ BitVec 23) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 23)) (b (_ BitVec 23))) (_ BitVec 23) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 23) (bvsdiv x y))
(define-fun right () (_ BitVec 23) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
