
(set-logic QF_BV)
(declare-fun x () (_ BitVec 38))
(define-fun left () (_ BitVec 38) (bvneg x))
(define-fun right () (_ BitVec 38) (bvadd (bvnot x) (_ bv1 38) ))
(assert (distinct left right))
(check-sat)

