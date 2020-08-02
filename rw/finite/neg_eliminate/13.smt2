
(set-logic QF_BV)
(declare-fun x () (_ BitVec 13))
(define-fun left () (_ BitVec 13) (bvneg x))
(define-fun right () (_ BitVec 13) (bvadd (bvnot x) (_ bv1 13) ))
(assert (distinct left right))
(check-sat)

