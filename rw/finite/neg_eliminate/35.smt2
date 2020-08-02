
(set-logic QF_BV)
(declare-fun x () (_ BitVec 35))
(define-fun left () (_ BitVec 35) (bvneg x))
(define-fun right () (_ BitVec 35) (bvadd (bvnot x) (_ bv1 35) ))
(assert (distinct left right))
(check-sat)

