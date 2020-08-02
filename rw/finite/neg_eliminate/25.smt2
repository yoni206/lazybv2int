
(set-logic QF_BV)
(declare-fun x () (_ BitVec 25))
(define-fun left () (_ BitVec 25) (bvneg x))
(define-fun right () (_ BitVec 25) (bvadd (bvnot x) (_ bv1 25) ))
(assert (distinct left right))
(check-sat)

