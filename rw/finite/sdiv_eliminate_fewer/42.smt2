
(set-logic QF_BV)
(declare-fun x () (_ BitVec 42))
(declare-fun y () (_ BitVec 42))
(define-fun mins () (_ BitVec 42) (_ bv2199023255552 42))

(define-fun negative ((a (_ BitVec 42))) Bool (bvuge a (_ bv2199023255552 42)))
(define-fun abs ((a (_ BitVec 42))) (_ BitVec 42) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 42)) (b (_ BitVec 42))) (_ BitVec 42) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 42) (bvsdiv x y))
(define-fun right () (_ BitVec 42) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
