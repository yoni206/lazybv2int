
(set-logic QF_BV)
(declare-fun x () (_ BitVec 34))
(define-fun left () (_ BitVec 34) (bvneg x))
(define-fun right () (_ BitVec 34) (bvadd (bvnot x) (_ bv1 34) ))
(assert (distinct left right))
(check-sat)

