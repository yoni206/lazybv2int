
(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(define-fun left () (_ BitVec 32) (bvneg x))
(define-fun right () (_ BitVec 32) (bvadd (bvnot x) (_ bv1 32) ))
(assert (distinct left right))
(check-sat)

