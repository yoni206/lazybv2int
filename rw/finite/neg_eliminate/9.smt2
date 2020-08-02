
(set-logic QF_BV)
(declare-fun x () (_ BitVec 9))
(define-fun left () (_ BitVec 9) (bvneg x))
(define-fun right () (_ BitVec 9) (bvadd (bvnot x) (_ bv1 9) ))
(assert (distinct left right))
(check-sat)

