
(set-logic QF_BV)
(declare-fun x () (_ BitVec 64))
(declare-fun y () (_ BitVec 64))
(define-fun mins () (_ BitVec 64) (_ bv9223372036854775808 64))

(define-fun negative ((a (_ BitVec 64))) Bool (bvuge a (_ bv9223372036854775808 64)))
(define-fun abs ((a (_ BitVec 64))) (_ BitVec 64) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 64)) (b (_ BitVec 64))) (_ BitVec 64) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 64) (bvsdiv x y))
(define-fun right () (_ BitVec 64) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
