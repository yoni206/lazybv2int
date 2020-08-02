
(set-logic QF_BV)
(declare-fun x () (_ BitVec 21))
(define-fun left () (_ BitVec 21) (bvneg x))
(define-fun right () (_ BitVec 21) (bvadd (bvnot x) (_ bv1 21) ))
(assert (distinct left right))
(check-sat)

