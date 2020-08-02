
(set-logic QF_BV)
(declare-fun x () (_ BitVec 39))
(define-fun left () (_ BitVec 39) (bvneg x))
(define-fun right () (_ BitVec 39) (bvadd (bvnot x) (_ bv1 39) ))
(assert (distinct left right))
(check-sat)

