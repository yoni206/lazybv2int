
(set-logic QF_BV)
(declare-fun x () (_ BitVec 34))
(declare-fun y () (_ BitVec 34))
(define-fun mins () (_ BitVec 34) (_ bv8589934592 34))

(define-fun negative ((a (_ BitVec 34))) Bool (bvuge a (_ bv8589934592 34)))
(define-fun abs ((a (_ BitVec 34))) (_ BitVec 34) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 34)) (b (_ BitVec 34))) (_ BitVec 34) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 34) (bvsdiv x y))
(define-fun right () (_ BitVec 34) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
