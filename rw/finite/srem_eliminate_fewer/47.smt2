
(set-logic QF_BV)
(declare-fun x () (_ BitVec 47))
(declare-fun y () (_ BitVec 47))
(define-fun mins () (_ BitVec 47) (_ bv70368744177664 47))

(define-fun negative ((a (_ BitVec 47))) Bool (bvuge a (_ bv70368744177664 47)))
(define-fun abs ((a (_ BitVec 47))) (_ BitVec 47) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 47)) (b (_ BitVec 47))) (_ BitVec 47) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 47) (bvsrem x y))
(define-fun right () (_ BitVec 47) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
