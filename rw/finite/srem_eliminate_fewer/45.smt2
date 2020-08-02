
(set-logic QF_BV)
(declare-fun x () (_ BitVec 45))
(declare-fun y () (_ BitVec 45))
(define-fun mins () (_ BitVec 45) (_ bv17592186044416 45))

(define-fun negative ((a (_ BitVec 45))) Bool (bvuge a (_ bv17592186044416 45)))
(define-fun abs ((a (_ BitVec 45))) (_ BitVec 45) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 45)) (b (_ BitVec 45))) (_ BitVec 45) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 45) (bvsrem x y))
(define-fun right () (_ BitVec 45) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
