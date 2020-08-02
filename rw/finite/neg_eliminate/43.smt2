
(set-logic QF_BV)
(declare-fun x () (_ BitVec 43))
(define-fun left () (_ BitVec 43) (bvneg x))
(define-fun right () (_ BitVec 43) (bvadd (bvnot x) (_ bv1 43) ))
(assert (distinct left right))
(check-sat)

