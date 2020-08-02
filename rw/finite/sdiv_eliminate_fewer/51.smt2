
(set-logic QF_BV)
(declare-fun x () (_ BitVec 51))
(declare-fun y () (_ BitVec 51))
(define-fun mins () (_ BitVec 51) (_ bv1125899906842624 51))

(define-fun negative ((a (_ BitVec 51))) Bool (bvuge a (_ bv1125899906842624 51)))
(define-fun abs ((a (_ BitVec 51))) (_ BitVec 51) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 51)) (b (_ BitVec 51))) (_ BitVec 51) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 51) (bvsdiv x y))
(define-fun right () (_ BitVec 51) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
