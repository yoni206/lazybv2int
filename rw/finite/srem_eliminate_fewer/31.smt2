
(set-logic QF_BV)
(declare-fun x () (_ BitVec 31))
(declare-fun y () (_ BitVec 31))
(define-fun mins () (_ BitVec 31) (_ bv1073741824 31))

(define-fun negative ((a (_ BitVec 31))) Bool (bvuge a (_ bv1073741824 31)))
(define-fun abs ((a (_ BitVec 31))) (_ BitVec 31) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 31)) (b (_ BitVec 31))) (_ BitVec 31) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 31) (bvsrem x y))
(define-fun right () (_ BitVec 31) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
