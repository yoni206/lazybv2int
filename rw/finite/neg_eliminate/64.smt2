
(set-logic QF_BV)
(declare-fun x () (_ BitVec 64))
(define-fun left () (_ BitVec 64) (bvneg x))
(define-fun right () (_ BitVec 64) (bvadd (bvnot x) (_ bv1 64) ))
(assert (distinct left right))
(check-sat)

