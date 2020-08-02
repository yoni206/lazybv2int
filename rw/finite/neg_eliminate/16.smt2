
(set-logic QF_BV)
(declare-fun x () (_ BitVec 16))
(define-fun left () (_ BitVec 16) (bvneg x))
(define-fun right () (_ BitVec 16) (bvadd (bvnot x) (_ bv1 16) ))
(assert (distinct left right))
(check-sat)

