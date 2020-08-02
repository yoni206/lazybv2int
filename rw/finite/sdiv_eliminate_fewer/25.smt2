
(set-logic QF_BV)
(declare-fun x () (_ BitVec 25))
(declare-fun y () (_ BitVec 25))
(define-fun mins () (_ BitVec 25) (_ bv16777216 25))

(define-fun negative ((a (_ BitVec 25))) Bool (bvuge a (_ bv16777216 25)))
(define-fun abs ((a (_ BitVec 25))) (_ BitVec 25) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 25)) (b (_ BitVec 25))) (_ BitVec 25) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 25) (bvsdiv x y))
(define-fun right () (_ BitVec 25) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
