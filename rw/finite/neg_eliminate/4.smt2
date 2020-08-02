
(set-logic QF_BV)
(declare-fun x () (_ BitVec 4))
(define-fun left () (_ BitVec 4) (bvneg x))
(define-fun right () (_ BitVec 4) (bvadd (bvnot x) (_ bv1 4) ))
(assert (distinct left right))
(check-sat)

