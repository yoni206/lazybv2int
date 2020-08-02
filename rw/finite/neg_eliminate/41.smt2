
(set-logic QF_BV)
(declare-fun x () (_ BitVec 41))
(define-fun left () (_ BitVec 41) (bvneg x))
(define-fun right () (_ BitVec 41) (bvadd (bvnot x) (_ bv1 41) ))
(assert (distinct left right))
(check-sat)

