
(set-logic QF_BV)
(declare-fun x () (_ BitVec 63))
(declare-fun y () (_ BitVec 63))
(define-fun mins () (_ BitVec 63) (_ bv4611686018427387904 63))

(define-fun negative ((a (_ BitVec 63))) Bool (bvuge a (_ bv4611686018427387904 63)))
(define-fun abs ((a (_ BitVec 63))) (_ BitVec 63) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 63)) (b (_ BitVec 63))) (_ BitVec 63) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 63) (bvsrem x y))
(define-fun right () (_ BitVec 63) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
