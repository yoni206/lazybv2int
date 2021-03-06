
(set-logic QF_BV)
(declare-fun x () (_ BitVec 25))
(declare-fun y () (_ BitVec 25))
(define-fun mins () (_ BitVec 25) (_ bv16777216 25))

(define-fun negative ((a (_ BitVec 25))) Bool (bvuge a (_ bv16777216 25)))
(define-fun abs ((a (_ BitVec 25))) (_ BitVec 25) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 25)) (b (_ BitVec 25))) (_ BitVec 25) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 25) (bvsrem x y))
(define-fun right () (_ BitVec 25) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
