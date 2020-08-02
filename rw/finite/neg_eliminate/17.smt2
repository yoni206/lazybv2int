
(set-logic QF_BV)
(declare-fun x () (_ BitVec 17))
(define-fun left () (_ BitVec 17) (bvneg x))
(define-fun right () (_ BitVec 17) (bvadd (bvnot x) (_ bv1 17) ))
(assert (distinct left right))
(check-sat)

