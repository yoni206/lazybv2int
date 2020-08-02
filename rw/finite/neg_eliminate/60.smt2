
(set-logic QF_BV)
(declare-fun x () (_ BitVec 60))
(define-fun left () (_ BitVec 60) (bvneg x))
(define-fun right () (_ BitVec 60) (bvadd (bvnot x) (_ bv1 60) ))
(assert (distinct left right))
(check-sat)

