
(set-logic QF_BV)
(declare-fun x () (_ BitVec 9))
(declare-fun y () (_ BitVec 9))
(define-fun mins () (_ BitVec 9) (_ bv256 9))

(define-fun negative ((a (_ BitVec 9))) Bool (bvuge a (_ bv256 9)))
(define-fun abs ((a (_ BitVec 9))) (_ BitVec 9) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 9)) (b (_ BitVec 9))) (_ BitVec 9) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 9) (bvsrem x y))
(define-fun right () (_ BitVec 9) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
