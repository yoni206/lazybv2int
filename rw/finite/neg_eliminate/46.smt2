
(set-logic QF_BV)
(declare-fun x () (_ BitVec 46))
(define-fun left () (_ BitVec 46) (bvneg x))
(define-fun right () (_ BitVec 46) (bvadd (bvnot x) (_ bv1 46) ))
(assert (distinct left right))
(check-sat)

