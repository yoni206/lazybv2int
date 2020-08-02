
(set-logic QF_BV)
(declare-fun x () (_ BitVec 46))
(declare-fun y () (_ BitVec 46))
(define-fun mins () (_ BitVec 46) (_ bv35184372088832 46))

(define-fun negative ((a (_ BitVec 46))) Bool (bvuge a (_ bv35184372088832 46)))
(define-fun abs ((a (_ BitVec 46))) (_ BitVec 46) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 46)) (b (_ BitVec 46))) (_ BitVec 46) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 46) (bvsdiv x y))
(define-fun right () (_ BitVec 46) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
