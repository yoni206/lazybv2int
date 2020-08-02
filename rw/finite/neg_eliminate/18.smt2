
(set-logic QF_BV)
(declare-fun x () (_ BitVec 18))
(define-fun left () (_ BitVec 18) (bvneg x))
(define-fun right () (_ BitVec 18) (bvadd (bvnot x) (_ bv1 18) ))
(assert (distinct left right))
(check-sat)

