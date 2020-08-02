
(set-logic QF_BV)
(declare-fun x () (_ BitVec 44))
(define-fun left () (_ BitVec 44) (bvneg x))
(define-fun right () (_ BitVec 44) (bvadd (bvnot x) (_ bv1 44) ))
(assert (distinct left right))
(check-sat)

