
(set-logic QF_BV)
(declare-fun x () (_ BitVec 28))
(define-fun left () (_ BitVec 28) (bvneg x))
(define-fun right () (_ BitVec 28) (bvadd (bvnot x) (_ bv1 28) ))
(assert (distinct left right))
(check-sat)

