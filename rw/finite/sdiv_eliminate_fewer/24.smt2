
(set-logic QF_BV)
(declare-fun x () (_ BitVec 24))
(declare-fun y () (_ BitVec 24))
(define-fun mins () (_ BitVec 24) (_ bv8388608 24))

(define-fun negative ((a (_ BitVec 24))) Bool (bvuge a (_ bv8388608 24)))
(define-fun abs ((a (_ BitVec 24))) (_ BitVec 24) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 24)) (b (_ BitVec 24))) (_ BitVec 24) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 24) (bvsdiv x y))
(define-fun right () (_ BitVec 24) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
