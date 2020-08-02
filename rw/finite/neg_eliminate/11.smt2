
(set-logic QF_BV)
(declare-fun x () (_ BitVec 11))
(define-fun left () (_ BitVec 11) (bvneg x))
(define-fun right () (_ BitVec 11) (bvadd (bvnot x) (_ bv1 11) ))
(assert (distinct left right))
(check-sat)

