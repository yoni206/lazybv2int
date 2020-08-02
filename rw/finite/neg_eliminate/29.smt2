
(set-logic QF_BV)
(declare-fun x () (_ BitVec 29))
(define-fun left () (_ BitVec 29) (bvneg x))
(define-fun right () (_ BitVec 29) (bvadd (bvnot x) (_ bv1 29) ))
(assert (distinct left right))
(check-sat)

