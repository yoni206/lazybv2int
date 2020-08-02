
(set-logic QF_BV)
(declare-fun x () (_ BitVec 10))
(declare-fun y () (_ BitVec 10))
(define-fun mins () (_ BitVec 10) (_ bv512 10))

(define-fun negative ((a (_ BitVec 10))) Bool (bvuge a (_ bv512 10)))
(define-fun abs ((a (_ BitVec 10))) (_ BitVec 10) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 10)) (b (_ BitVec 10))) (_ BitVec 10) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 10) (bvsdiv x y))
(define-fun right () (_ BitVec 10) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
