
(set-logic QF_BV)
(declare-fun x () (_ BitVec 55))
(define-fun left () (_ BitVec 55) (bvneg x))
(define-fun right () (_ BitVec 55) (bvadd (bvnot x) (_ bv1 55) ))
(assert (distinct left right))
(check-sat)

