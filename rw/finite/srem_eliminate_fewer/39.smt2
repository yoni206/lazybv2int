
(set-logic QF_BV)
(declare-fun x () (_ BitVec 39))
(declare-fun y () (_ BitVec 39))
(define-fun mins () (_ BitVec 39) (_ bv274877906944 39))

(define-fun negative ((a (_ BitVec 39))) Bool (bvuge a (_ bv274877906944 39)))
(define-fun abs ((a (_ BitVec 39))) (_ BitVec 39) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 39)) (b (_ BitVec 39))) (_ BitVec 39) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 39) (bvsrem x y))
(define-fun right () (_ BitVec 39) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
