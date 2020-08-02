
(set-logic QF_BV)
(declare-fun x () (_ BitVec 1))
(define-fun left () (_ BitVec 1) (bvneg x))
(define-fun right () (_ BitVec 1) (bvadd (bvnot x) (_ bv1 1) ))
(assert (distinct left right))
(check-sat)

