
(set-logic QF_BV)
(declare-fun x () (_ BitVec 22))
(declare-fun y () (_ BitVec 22))
(define-fun mins () (_ BitVec 22) (_ bv2097152 22))

(define-fun negative ((a (_ BitVec 22))) Bool (bvuge a (_ bv2097152 22)))
(define-fun abs ((a (_ BitVec 22))) (_ BitVec 22) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 22)) (b (_ BitVec 22))) (_ BitVec 22) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 22) (bvsrem x y))
(define-fun right () (_ BitVec 22) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
