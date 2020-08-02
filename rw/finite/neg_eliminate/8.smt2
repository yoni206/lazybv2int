
(set-logic QF_BV)
(declare-fun x () (_ BitVec 8))
(define-fun left () (_ BitVec 8) (bvneg x))
(define-fun right () (_ BitVec 8) (bvadd (bvnot x) (_ bv1 8) ))
(assert (distinct left right))
(check-sat)

