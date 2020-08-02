
(set-logic QF_BV)
(declare-fun x () (_ BitVec 30))
(declare-fun y () (_ BitVec 30))
(define-fun mins () (_ BitVec 30) (_ bv536870912 30))

(define-fun negative ((a (_ BitVec 30))) Bool (bvuge a (_ bv536870912 30)))
(define-fun abs ((a (_ BitVec 30))) (_ BitVec 30) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 30)) (b (_ BitVec 30))) (_ BitVec 30) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 30) (bvsdiv x y))
(define-fun right () (_ BitVec 30) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
