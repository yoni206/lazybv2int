
(set-logic QF_BV)
(declare-fun x () (_ BitVec 10))
(declare-fun y () (_ BitVec 10))
(define-fun mins () (_ BitVec 10) (_ bv512 10))

(define-fun negative ((a (_ BitVec 10))) Bool (bvuge a (_ bv512 10)))
(define-fun abs ((a (_ BitVec 10))) (_ BitVec 10) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 10)) (b (_ BitVec 10))) (_ BitVec 10) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 10) (bvsrem x y))
(define-fun right () (_ BitVec 10) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
