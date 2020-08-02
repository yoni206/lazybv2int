
(set-logic QF_BV)
(declare-fun x () (_ BitVec 20))
(declare-fun y () (_ BitVec 20))
(define-fun mins () (_ BitVec 20) (_ bv524288 20))

(define-fun negative ((a (_ BitVec 20))) Bool (bvuge a (_ bv524288 20)))
(define-fun abs ((a (_ BitVec 20))) (_ BitVec 20) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 20)) (b (_ BitVec 20))) (_ BitVec 20) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 20) (bvsrem x y))
(define-fun right () (_ BitVec 20) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
