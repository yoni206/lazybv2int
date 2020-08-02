
(set-logic QF_BV)
(declare-fun x () (_ BitVec 57))
(declare-fun y () (_ BitVec 57))
(define-fun mins () (_ BitVec 57) (_ bv72057594037927936 57))

(define-fun negative ((a (_ BitVec 57))) Bool (bvuge a (_ bv72057594037927936 57)))
(define-fun abs ((a (_ BitVec 57))) (_ BitVec 57) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 57)) (b (_ BitVec 57))) (_ BitVec 57) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 57) (bvsrem x y))
(define-fun right () (_ BitVec 57) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
