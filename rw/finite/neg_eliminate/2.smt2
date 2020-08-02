
(set-logic QF_BV)
(declare-fun x () (_ BitVec 2))
(define-fun left () (_ BitVec 2) (bvneg x))
(define-fun right () (_ BitVec 2) (bvadd (bvnot x) (_ bv1 2) ))
(assert (distinct left right))
(check-sat)

