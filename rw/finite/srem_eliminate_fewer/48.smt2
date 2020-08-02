
(set-logic QF_BV)
(declare-fun x () (_ BitVec 48))
(declare-fun y () (_ BitVec 48))
(define-fun mins () (_ BitVec 48) (_ bv140737488355328 48))

(define-fun negative ((a (_ BitVec 48))) Bool (bvuge a (_ bv140737488355328 48)))
(define-fun abs ((a (_ BitVec 48))) (_ BitVec 48) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 48)) (b (_ BitVec 48))) (_ BitVec 48) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 48) (bvsrem x y))
(define-fun right () (_ BitVec 48) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
