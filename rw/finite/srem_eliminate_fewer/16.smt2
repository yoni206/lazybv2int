
(set-logic QF_BV)
(declare-fun x () (_ BitVec 16))
(declare-fun y () (_ BitVec 16))
(define-fun mins () (_ BitVec 16) (_ bv32768 16))

(define-fun negative ((a (_ BitVec 16))) Bool (bvuge a (_ bv32768 16)))
(define-fun abs ((a (_ BitVec 16))) (_ BitVec 16) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 16)) (b (_ BitVec 16))) (_ BitVec 16) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 16) (bvsrem x y))
(define-fun right () (_ BitVec 16) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
