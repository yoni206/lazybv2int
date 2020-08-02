
(set-logic QF_BV)
(declare-fun x () (_ BitVec 12))
(define-fun left () (_ BitVec 12) (bvneg x))
(define-fun right () (_ BitVec 12) (bvadd (bvnot x) (_ bv1 12) ))
(assert (distinct left right))
(check-sat)

