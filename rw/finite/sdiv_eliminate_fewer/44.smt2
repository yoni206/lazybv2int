
(set-logic QF_BV)
(declare-fun x () (_ BitVec 44))
(declare-fun y () (_ BitVec 44))
(define-fun mins () (_ BitVec 44) (_ bv8796093022208 44))

(define-fun negative ((a (_ BitVec 44))) Bool (bvuge a (_ bv8796093022208 44)))
(define-fun abs ((a (_ BitVec 44))) (_ BitVec 44) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 44)) (b (_ BitVec 44))) (_ BitVec 44) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 44) (bvsdiv x y))
(define-fun right () (_ BitVec 44) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
