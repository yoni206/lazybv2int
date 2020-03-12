(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 6))
(assert (= ((_ extract 5 1) x) ((_ extract 4 0) x)))
(assert (= ((_ extract 0 0) x) (_ bv0 1)))
(assert  (not (= x (_ bv0 6))) )
(check-sat)
