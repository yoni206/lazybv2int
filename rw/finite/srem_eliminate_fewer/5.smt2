
(set-logic QF_BV)
(declare-fun x () (_ BitVec 5))
(declare-fun y () (_ BitVec 5))
(define-fun mins () (_ BitVec 5) (_ bv16 5))

(define-fun negative ((a (_ BitVec 5))) Bool (bvuge a (_ bv16 5)))
(define-fun abs ((a (_ BitVec 5))) (_ BitVec 5) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 5)) (b (_ BitVec 5))) (_ BitVec 5) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 5) (bvsrem x y))
(define-fun right () (_ BitVec 5) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
