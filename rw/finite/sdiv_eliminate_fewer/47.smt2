
(set-logic QF_BV)
(declare-fun x () (_ BitVec 47))
(declare-fun y () (_ BitVec 47))
(define-fun mins () (_ BitVec 47) (_ bv70368744177664 47))

(define-fun negative ((a (_ BitVec 47))) Bool (bvuge a (_ bv70368744177664 47)))
(define-fun abs ((a (_ BitVec 47))) (_ BitVec 47) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 47)) (b (_ BitVec 47))) (_ BitVec 47) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 47) (bvsdiv x y))
(define-fun right () (_ BitVec 47) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
