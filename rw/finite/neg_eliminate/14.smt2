
(set-logic QF_BV)
(declare-fun x () (_ BitVec 14))
(define-fun left () (_ BitVec 14) (bvneg x))
(define-fun right () (_ BitVec 14) (bvadd (bvnot x) (_ bv1 14) ))
(assert (distinct left right))
(check-sat)

