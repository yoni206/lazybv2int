
(set-logic QF_BV)
(declare-fun x () (_ BitVec 27))
(define-fun left () (_ BitVec 27) (bvneg x))
(define-fun right () (_ BitVec 27) (bvadd (bvnot x) (_ bv1 27) ))
(assert (distinct left right))
(check-sat)

