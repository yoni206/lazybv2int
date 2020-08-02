
(set-logic QF_BV)
(declare-fun x () (_ BitVec 26))
(define-fun left () (_ BitVec 26) (bvneg x))
(define-fun right () (_ BitVec 26) (bvadd (bvnot x) (_ bv1 26) ))
(assert (distinct left right))
(check-sat)

