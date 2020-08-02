
(set-logic QF_BV)
(declare-fun x () (_ BitVec 61))
(define-fun left () (_ BitVec 61) (bvneg x))
(define-fun right () (_ BitVec 61) (bvadd (bvnot x) (_ bv1 61) ))
(assert (distinct left right))
(check-sat)

