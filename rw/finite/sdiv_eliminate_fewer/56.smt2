
(set-logic QF_BV)
(declare-fun x () (_ BitVec 56))
(declare-fun y () (_ BitVec 56))
(define-fun mins () (_ BitVec 56) (_ bv36028797018963968 56))

(define-fun negative ((a (_ BitVec 56))) Bool (bvuge a (_ bv36028797018963968 56)))
(define-fun abs ((a (_ BitVec 56))) (_ BitVec 56) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 56)) (b (_ BitVec 56))) (_ BitVec 56) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 56) (bvsdiv x y))
(define-fun right () (_ BitVec 56) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
