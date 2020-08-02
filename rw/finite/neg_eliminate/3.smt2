
(set-logic QF_BV)
(declare-fun x () (_ BitVec 3))
(define-fun left () (_ BitVec 3) (bvneg x))
(define-fun right () (_ BitVec 3) (bvadd (bvnot x) (_ bv1 3) ))
(assert (distinct left right))
(check-sat)

