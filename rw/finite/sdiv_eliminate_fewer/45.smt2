
(set-logic QF_BV)
(declare-fun x () (_ BitVec 45))
(declare-fun y () (_ BitVec 45))
(define-fun mins () (_ BitVec 45) (_ bv17592186044416 45))

(define-fun negative ((a (_ BitVec 45))) Bool (bvuge a (_ bv17592186044416 45)))
(define-fun abs ((a (_ BitVec 45))) (_ BitVec 45) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 45)) (b (_ BitVec 45))) (_ BitVec 45) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 45) (bvsdiv x y))
(define-fun right () (_ BitVec 45) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
