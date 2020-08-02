
(set-logic QF_BV)
(declare-fun x () (_ BitVec 30))
(define-fun left () (_ BitVec 30) (bvneg x))
(define-fun right () (_ BitVec 30) (bvadd (bvnot x) (_ bv1 30) ))
(assert (distinct left right))
(check-sat)

