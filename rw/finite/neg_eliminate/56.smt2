
(set-logic QF_BV)
(declare-fun x () (_ BitVec 56))
(define-fun left () (_ BitVec 56) (bvneg x))
(define-fun right () (_ BitVec 56) (bvadd (bvnot x) (_ bv1 56) ))
(assert (distinct left right))
(check-sat)

