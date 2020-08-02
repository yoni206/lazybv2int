
(set-logic QF_BV)
(declare-fun x () (_ BitVec 15))
(declare-fun y () (_ BitVec 15))
(define-fun mins () (_ BitVec 15) (_ bv16384 15))

(define-fun negative ((a (_ BitVec 15))) Bool (bvuge a (_ bv16384 15)))
(define-fun abs ((a (_ BitVec 15))) (_ BitVec 15) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 15)) (b (_ BitVec 15))) (_ BitVec 15) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 15) (bvsdiv x y))
(define-fun right () (_ BitVec 15) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
