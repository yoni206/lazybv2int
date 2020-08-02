
(set-logic QF_BV)
(declare-fun x () (_ BitVec 27))
(declare-fun y () (_ BitVec 27))
(define-fun mins () (_ BitVec 27) (_ bv67108864 27))

(define-fun negative ((a (_ BitVec 27))) Bool (bvuge a (_ bv67108864 27)))
(define-fun abs ((a (_ BitVec 27))) (_ BitVec 27) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 27)) (b (_ BitVec 27))) (_ BitVec 27) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 27) (bvsrem x y))
(define-fun right () (_ BitVec 27) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
