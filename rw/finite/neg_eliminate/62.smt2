
(set-logic QF_BV)
(declare-fun x () (_ BitVec 62))
(define-fun left () (_ BitVec 62) (bvneg x))
(define-fun right () (_ BitVec 62) (bvadd (bvnot x) (_ bv1 62) ))
(assert (distinct left right))
(check-sat)

