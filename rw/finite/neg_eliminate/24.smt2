
(set-logic QF_BV)
(declare-fun x () (_ BitVec 24))
(define-fun left () (_ BitVec 24) (bvneg x))
(define-fun right () (_ BitVec 24) (bvadd (bvnot x) (_ bv1 24) ))
(assert (distinct left right))
(check-sat)

