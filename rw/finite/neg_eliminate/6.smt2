
(set-logic QF_BV)
(declare-fun x () (_ BitVec 6))
(define-fun left () (_ BitVec 6) (bvneg x))
(define-fun right () (_ BitVec 6) (bvadd (bvnot x) (_ bv1 6) ))
(assert (distinct left right))
(check-sat)

