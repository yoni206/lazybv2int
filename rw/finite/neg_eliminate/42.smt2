
(set-logic QF_BV)
(declare-fun x () (_ BitVec 42))
(define-fun left () (_ BitVec 42) (bvneg x))
(define-fun right () (_ BitVec 42) (bvadd (bvnot x) (_ bv1 42) ))
(assert (distinct left right))
(check-sat)

