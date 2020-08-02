
(set-logic QF_BV)
(declare-fun x () (_ BitVec 20))
(define-fun left () (_ BitVec 20) (bvneg x))
(define-fun right () (_ BitVec 20) (bvadd (bvnot x) (_ bv1 20) ))
(assert (distinct left right))
(check-sat)

