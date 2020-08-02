
(set-logic QF_BV)
(declare-fun x () (_ BitVec 19))
(define-fun left () (_ BitVec 19) (bvneg x))
(define-fun right () (_ BitVec 19) (bvadd (bvnot x) (_ bv1 19) ))
(assert (distinct left right))
(check-sat)

