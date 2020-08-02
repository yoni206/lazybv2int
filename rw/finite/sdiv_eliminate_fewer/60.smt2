
(set-logic QF_BV)
(declare-fun x () (_ BitVec 60))
(declare-fun y () (_ BitVec 60))
(define-fun mins () (_ BitVec 60) (_ bv576460752303423488 60))

(define-fun negative ((a (_ BitVec 60))) Bool (bvuge a (_ bv576460752303423488 60)))
(define-fun abs ((a (_ BitVec 60))) (_ BitVec 60) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 60)) (b (_ BitVec 60))) (_ BitVec 60) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 60) (bvsdiv x y))
(define-fun right () (_ BitVec 60) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
