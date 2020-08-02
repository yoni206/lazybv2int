
(set-logic QF_BV)
(declare-fun x () (_ BitVec 47))
(define-fun left () (_ BitVec 47) (bvneg x))
(define-fun right () (_ BitVec 47) (bvadd (bvnot x) (_ bv1 47) ))
(assert (distinct left right))
(check-sat)

