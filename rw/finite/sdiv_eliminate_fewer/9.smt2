
(set-logic QF_BV)
(declare-fun x () (_ BitVec 9))
(declare-fun y () (_ BitVec 9))
(define-fun mins () (_ BitVec 9) (_ bv256 9))

(define-fun negative ((a (_ BitVec 9))) Bool (bvuge a (_ bv256 9)))
(define-fun abs ((a (_ BitVec 9))) (_ BitVec 9) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 9)) (b (_ BitVec 9))) (_ BitVec 9) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 9) (bvsdiv x y))
(define-fun right () (_ BitVec 9) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
