
(set-logic QF_BV)
(declare-fun x () (_ BitVec 28))
(declare-fun y () (_ BitVec 28))
(define-fun mins () (_ BitVec 28) (_ bv134217728 28))

(define-fun negative ((a (_ BitVec 28))) Bool (bvuge a (_ bv134217728 28)))
(define-fun abs ((a (_ BitVec 28))) (_ BitVec 28) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 28)) (b (_ BitVec 28))) (_ BitVec 28) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 28) (bvsrem x y))
(define-fun right () (_ BitVec 28) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
