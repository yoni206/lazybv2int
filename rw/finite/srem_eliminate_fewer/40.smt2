
(set-logic QF_BV)
(declare-fun x () (_ BitVec 40))
(declare-fun y () (_ BitVec 40))
(define-fun mins () (_ BitVec 40) (_ bv549755813888 40))

(define-fun negative ((a (_ BitVec 40))) Bool (bvuge a (_ bv549755813888 40)))
(define-fun abs ((a (_ BitVec 40))) (_ BitVec 40) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 40)) (b (_ BitVec 40))) (_ BitVec 40) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 40) (bvsrem x y))
(define-fun right () (_ BitVec 40) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
