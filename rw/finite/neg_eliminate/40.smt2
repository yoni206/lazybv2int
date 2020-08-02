
(set-logic QF_BV)
(declare-fun x () (_ BitVec 40))
(define-fun left () (_ BitVec 40) (bvneg x))
(define-fun right () (_ BitVec 40) (bvadd (bvnot x) (_ bv1 40) ))
(assert (distinct left right))
(check-sat)

