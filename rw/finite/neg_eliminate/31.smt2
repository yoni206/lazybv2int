
(set-logic QF_BV)
(declare-fun x () (_ BitVec 31))
(define-fun left () (_ BitVec 31) (bvneg x))
(define-fun right () (_ BitVec 31) (bvadd (bvnot x) (_ bv1 31) ))
(assert (distinct left right))
(check-sat)

