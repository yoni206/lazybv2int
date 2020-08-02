
(set-logic QF_BV)
(declare-fun x () (_ BitVec 49))
(define-fun left () (_ BitVec 49) (bvneg x))
(define-fun right () (_ BitVec 49) (bvadd (bvnot x) (_ bv1 49) ))
(assert (distinct left right))
(check-sat)

