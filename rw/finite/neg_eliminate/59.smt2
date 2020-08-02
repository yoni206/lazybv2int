
(set-logic QF_BV)
(declare-fun x () (_ BitVec 59))
(define-fun left () (_ BitVec 59) (bvneg x))
(define-fun right () (_ BitVec 59) (bvadd (bvnot x) (_ bv1 59) ))
(assert (distinct left right))
(check-sat)

