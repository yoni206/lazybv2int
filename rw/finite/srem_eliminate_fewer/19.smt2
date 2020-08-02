
(set-logic QF_BV)
(declare-fun x () (_ BitVec 19))
(declare-fun y () (_ BitVec 19))
(define-fun mins () (_ BitVec 19) (_ bv262144 19))

(define-fun negative ((a (_ BitVec 19))) Bool (bvuge a (_ bv262144 19)))
(define-fun abs ((a (_ BitVec 19))) (_ BitVec 19) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 19)) (b (_ BitVec 19))) (_ BitVec 19) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 19) (bvsrem x y))
(define-fun right () (_ BitVec 19) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
