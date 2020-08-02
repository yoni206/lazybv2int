
(set-logic QF_BV)
(declare-fun x () (_ BitVec 7))
(define-fun left () (_ BitVec 7) (bvneg x))
(define-fun right () (_ BitVec 7) (bvadd (bvnot x) (_ bv1 7) ))
(assert (distinct left right))
(check-sat)

