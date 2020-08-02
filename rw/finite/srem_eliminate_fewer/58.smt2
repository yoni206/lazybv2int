
(set-logic QF_BV)
(declare-fun x () (_ BitVec 58))
(declare-fun y () (_ BitVec 58))
(define-fun mins () (_ BitVec 58) (_ bv144115188075855872 58))

(define-fun negative ((a (_ BitVec 58))) Bool (bvuge a (_ bv144115188075855872 58)))
(define-fun abs ((a (_ BitVec 58))) (_ BitVec 58) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 58)) (b (_ BitVec 58))) (_ BitVec 58) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 58) (bvsrem x y))
(define-fun right () (_ BitVec 58) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
