(set-option :incremental false)

(set-logic QF_BV)
(declare-fun v0 () (_ BitVec 4))
(assert  (= ((_ extract 0 0) (bvadd (bvnot v0) (_ bv1 4))) (_ bv0 1)) )
(check-sat)
