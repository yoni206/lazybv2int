
(set-logic QF_BV)
(declare-fun x () (_ BitVec 56))
(declare-fun y () (_ BitVec 56))
(define-fun mins () (_ BitVec 56) (_ bv36028797018963968 56))

(define-fun negative ((a (_ BitVec 56))) Bool (bvuge a (_ bv36028797018963968 56)))
(define-fun abs ((a (_ BitVec 56))) (_ BitVec 56) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 56)) (b (_ BitVec 56))) (_ BitVec 56) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 56) (bvsrem x y))
(define-fun right () (_ BitVec 56) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
