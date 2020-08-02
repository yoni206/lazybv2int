
(set-logic QF_BV)
(declare-fun x () (_ BitVec 10))
(define-fun left () (_ BitVec 10) (bvneg x))
(define-fun right () (_ BitVec 10) (bvadd (bvnot x) (_ bv1 10) ))
(assert (distinct left right))
(check-sat)

