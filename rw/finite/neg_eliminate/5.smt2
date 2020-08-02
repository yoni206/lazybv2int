
(set-logic QF_BV)
(declare-fun x () (_ BitVec 5))
(define-fun left () (_ BitVec 5) (bvneg x))
(define-fun right () (_ BitVec 5) (bvadd (bvnot x) (_ bv1 5) ))
(assert (distinct left right))
(check-sat)

