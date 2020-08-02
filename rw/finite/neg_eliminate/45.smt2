
(set-logic QF_BV)
(declare-fun x () (_ BitVec 45))
(define-fun left () (_ BitVec 45) (bvneg x))
(define-fun right () (_ BitVec 45) (bvadd (bvnot x) (_ bv1 45) ))
(assert (distinct left right))
(check-sat)

