
(set-logic QF_BV)
(declare-fun x () (_ BitVec 54))
(define-fun left () (_ BitVec 54) (bvneg x))
(define-fun right () (_ BitVec 54) (bvadd (bvnot x) (_ bv1 54) ))
(assert (distinct left right))
(check-sat)

