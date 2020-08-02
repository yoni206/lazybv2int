
(set-logic QF_BV)
(declare-fun x () (_ BitVec 57))
(define-fun left () (_ BitVec 57) (bvneg x))
(define-fun right () (_ BitVec 57) (bvadd (bvnot x) (_ bv1 57) ))
(assert (distinct left right))
(check-sat)

