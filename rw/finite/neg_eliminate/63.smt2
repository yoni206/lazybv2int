
(set-logic QF_BV)
(declare-fun x () (_ BitVec 63))
(define-fun left () (_ BitVec 63) (bvneg x))
(define-fun right () (_ BitVec 63) (bvadd (bvnot x) (_ bv1 63) ))
(assert (distinct left right))
(check-sat)

