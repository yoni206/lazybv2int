
(set-logic QF_BV)
(declare-fun x () (_ BitVec 28))
(declare-fun y () (_ BitVec 28))
(define-fun mins () (_ BitVec 28) (_ bv134217728 28))

(define-fun negative ((a (_ BitVec 28))) Bool (bvuge a (_ bv134217728 28)))
(define-fun abs ((a (_ BitVec 28))) (_ BitVec 28) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 28)) (b (_ BitVec 28))) (_ BitVec 28) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 28) (bvsdiv x y))
(define-fun right () (_ BitVec 28) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
