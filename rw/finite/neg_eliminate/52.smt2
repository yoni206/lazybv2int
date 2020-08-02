
(set-logic QF_BV)
(declare-fun x () (_ BitVec 52))
(define-fun left () (_ BitVec 52) (bvneg x))
(define-fun right () (_ BitVec 52) (bvadd (bvnot x) (_ bv1 52) ))
(assert (distinct left right))
(check-sat)

