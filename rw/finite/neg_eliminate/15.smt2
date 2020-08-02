
(set-logic QF_BV)
(declare-fun x () (_ BitVec 15))
(define-fun left () (_ BitVec 15) (bvneg x))
(define-fun right () (_ BitVec 15) (bvadd (bvnot x) (_ bv1 15) ))
(assert (distinct left right))
(check-sat)

