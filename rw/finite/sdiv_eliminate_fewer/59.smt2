
(set-logic QF_BV)
(declare-fun x () (_ BitVec 59))
(declare-fun y () (_ BitVec 59))
(define-fun mins () (_ BitVec 59) (_ bv288230376151711744 59))

(define-fun negative ((a (_ BitVec 59))) Bool (bvuge a (_ bv288230376151711744 59)))
(define-fun abs ((a (_ BitVec 59))) (_ BitVec 59) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 59)) (b (_ BitVec 59))) (_ BitVec 59) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 59) (bvsdiv x y))
(define-fun right () (_ BitVec 59) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
