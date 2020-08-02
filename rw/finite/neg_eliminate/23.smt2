
(set-logic QF_BV)
(declare-fun x () (_ BitVec 23))
(define-fun left () (_ BitVec 23) (bvneg x))
(define-fun right () (_ BitVec 23) (bvadd (bvnot x) (_ bv1 23) ))
(assert (distinct left right))
(check-sat)

