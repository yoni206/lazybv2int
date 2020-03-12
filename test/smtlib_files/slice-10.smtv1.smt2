(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 8))
(assert (= ((_ extract 3 0) x) (_ bv0 4)))
(assert (= ((_ extract 7 4) x) (_ bv15 4)))
(assert  (not (= x (_ bv240 8))) )
(check-sat)
