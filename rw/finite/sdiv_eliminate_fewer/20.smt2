
(set-logic QF_BV)
(declare-fun x () (_ BitVec 20))
(declare-fun y () (_ BitVec 20))
(define-fun mins () (_ BitVec 20) (_ bv524288 20))

(define-fun negative ((a (_ BitVec 20))) Bool (bvuge a (_ bv524288 20)))
(define-fun abs ((a (_ BitVec 20))) (_ BitVec 20) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 20)) (b (_ BitVec 20))) (_ BitVec 20) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 20) (bvsdiv x y))
(define-fun right () (_ BitVec 20) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
