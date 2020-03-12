(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 6))
(assert (= ((_ extract 5 2) x) ((_ extract 3 0) x)))
(assert  (not (= ((_ extract 5 4) x) ((_ extract 1 0) x))) )
(check-sat)
