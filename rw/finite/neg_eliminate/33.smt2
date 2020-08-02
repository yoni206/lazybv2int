
(set-logic QF_BV)
(declare-fun x () (_ BitVec 33))
(define-fun left () (_ BitVec 33) (bvneg x))
(define-fun right () (_ BitVec 33) (bvadd (bvnot x) (_ bv1 33) ))
(assert (distinct left right))
(check-sat)

