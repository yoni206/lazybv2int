
(set-logic QF_BV)
(declare-fun x () (_ BitVec 53))
(define-fun left () (_ BitVec 53) (bvneg x))
(define-fun right () (_ BitVec 53) (bvadd (bvnot x) (_ bv1 53) ))
(assert (distinct left right))
(check-sat)

