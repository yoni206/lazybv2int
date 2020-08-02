
(set-logic QF_BV)
(declare-fun x () (_ BitVec 39))
(declare-fun y () (_ BitVec 39))
(define-fun mins () (_ BitVec 39) (_ bv274877906944 39))

(define-fun negative ((a (_ BitVec 39))) Bool (bvuge a (_ bv274877906944 39)))
(define-fun abs ((a (_ BitVec 39))) (_ BitVec 39) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 39)) (b (_ BitVec 39))) (_ BitVec 39) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 39) (bvsdiv x y))
(define-fun right () (_ BitVec 39) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
