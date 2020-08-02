
(set-logic QF_BV)
(declare-fun x () (_ BitVec 48))
(define-fun left () (_ BitVec 48) (bvneg x))
(define-fun right () (_ BitVec 48) (bvadd (bvnot x) (_ bv1 48) ))
(assert (distinct left right))
(check-sat)

