
(set-logic QF_BV)
(declare-fun x () (_ BitVec 51))
(define-fun left () (_ BitVec 51) (bvneg x))
(define-fun right () (_ BitVec 51) (bvadd (bvnot x) (_ bv1 51) ))
(assert (distinct left right))
(check-sat)

