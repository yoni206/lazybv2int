
(set-logic QF_BV)
(declare-fun x () (_ BitVec 37))
(define-fun left () (_ BitVec 37) (bvneg x))
(define-fun right () (_ BitVec 37) (bvadd (bvnot x) (_ bv1 37) ))
(assert (distinct left right))
(check-sat)

