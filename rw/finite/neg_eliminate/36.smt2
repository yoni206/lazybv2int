
(set-logic QF_BV)
(declare-fun x () (_ BitVec 36))
(define-fun left () (_ BitVec 36) (bvneg x))
(define-fun right () (_ BitVec 36) (bvadd (bvnot x) (_ bv1 36) ))
(assert (distinct left right))
(check-sat)

