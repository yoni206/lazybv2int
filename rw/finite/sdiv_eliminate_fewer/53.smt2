
(set-logic QF_BV)
(declare-fun x () (_ BitVec 53))
(declare-fun y () (_ BitVec 53))
(define-fun mins () (_ BitVec 53) (_ bv4503599627370496 53))

(define-fun negative ((a (_ BitVec 53))) Bool (bvuge a (_ bv4503599627370496 53)))
(define-fun abs ((a (_ BitVec 53))) (_ BitVec 53) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 53)) (b (_ BitVec 53))) (_ BitVec 53) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 53) (bvsdiv x y))
(define-fun right () (_ BitVec 53) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
