
(set-logic QF_BV)
(declare-fun x () (_ BitVec 13))
(declare-fun y () (_ BitVec 13))
(define-fun mins () (_ BitVec 13) (_ bv4096 13))

(define-fun negative ((a (_ BitVec 13))) Bool (bvuge a (_ bv4096 13)))
(define-fun abs ((a (_ BitVec 13))) (_ BitVec 13) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 13)) (b (_ BitVec 13))) (_ BitVec 13) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 13) (bvsrem x y))
(define-fun right () (_ BitVec 13) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
