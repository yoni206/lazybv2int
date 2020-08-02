
(set-logic QF_BV)
(declare-fun x () (_ BitVec 61))
(declare-fun y () (_ BitVec 61))
(define-fun mins () (_ BitVec 61) (_ bv1152921504606846976 61))

(define-fun negative ((a (_ BitVec 61))) Bool (bvuge a (_ bv1152921504606846976 61)))
(define-fun abs ((a (_ BitVec 61))) (_ BitVec 61) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 61)) (b (_ BitVec 61))) (_ BitVec 61) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 61) (bvsrem x y))
(define-fun right () (_ BitVec 61) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
