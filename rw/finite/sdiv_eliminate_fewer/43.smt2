
(set-logic QF_BV)
(declare-fun x () (_ BitVec 43))
(declare-fun y () (_ BitVec 43))
(define-fun mins () (_ BitVec 43) (_ bv4398046511104 43))

(define-fun negative ((a (_ BitVec 43))) Bool (bvuge a (_ bv4398046511104 43)))
(define-fun abs ((a (_ BitVec 43))) (_ BitVec 43) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 43)) (b (_ BitVec 43))) (_ BitVec 43) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 43) (bvsdiv x y))
(define-fun right () (_ BitVec 43) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
