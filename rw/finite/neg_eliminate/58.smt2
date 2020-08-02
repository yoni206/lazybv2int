
(set-logic QF_BV)
(declare-fun x () (_ BitVec 58))
(define-fun left () (_ BitVec 58) (bvneg x))
(define-fun right () (_ BitVec 58) (bvadd (bvnot x) (_ bv1 58) ))
(assert (distinct left right))
(check-sat)

