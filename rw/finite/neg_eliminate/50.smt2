
(set-logic QF_BV)
(declare-fun x () (_ BitVec 50))
(define-fun left () (_ BitVec 50) (bvneg x))
(define-fun right () (_ BitVec 50) (bvadd (bvnot x) (_ bv1 50) ))
(assert (distinct left right))
(check-sat)

