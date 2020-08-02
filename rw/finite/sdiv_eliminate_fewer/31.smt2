
(set-logic QF_BV)
(declare-fun x () (_ BitVec 31))
(declare-fun y () (_ BitVec 31))
(define-fun mins () (_ BitVec 31) (_ bv1073741824 31))

(define-fun negative ((a (_ BitVec 31))) Bool (bvuge a (_ bv1073741824 31)))
(define-fun abs ((a (_ BitVec 31))) (_ BitVec 31) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 31)) (b (_ BitVec 31))) (_ BitVec 31) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 31) (bvsdiv x y))
(define-fun right () (_ BitVec 31) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
