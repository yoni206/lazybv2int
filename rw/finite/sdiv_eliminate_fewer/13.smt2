
(set-logic QF_BV)
(declare-fun x () (_ BitVec 13))
(declare-fun y () (_ BitVec 13))
(define-fun mins () (_ BitVec 13) (_ bv4096 13))

(define-fun negative ((a (_ BitVec 13))) Bool (bvuge a (_ bv4096 13)))
(define-fun abs ((a (_ BitVec 13))) (_ BitVec 13) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 13)) (b (_ BitVec 13))) (_ BitVec 13) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 13) (bvsdiv x y))
(define-fun right () (_ BitVec 13) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
