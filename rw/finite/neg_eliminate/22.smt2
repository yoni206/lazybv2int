
(set-logic QF_BV)
(declare-fun x () (_ BitVec 22))
(define-fun left () (_ BitVec 22) (bvneg x))
(define-fun right () (_ BitVec 22) (bvadd (bvnot x) (_ bv1 22) ))
(assert (distinct left right))
(check-sat)

