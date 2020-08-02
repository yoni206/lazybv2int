
(set-logic QF_BV)
(declare-fun x () (_ BitVec 30))
(declare-fun y () (_ BitVec 30))
(define-fun mins () (_ BitVec 30) (_ bv536870912 30))

(define-fun negative ((a (_ BitVec 30))) Bool (bvuge a (_ bv536870912 30)))
(define-fun abs ((a (_ BitVec 30))) (_ BitVec 30) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 30)) (b (_ BitVec 30))) (_ BitVec 30) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 30) (bvsrem x y))
(define-fun right () (_ BitVec 30) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
