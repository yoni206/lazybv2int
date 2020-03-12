(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 5))
(assert (= ((_ extract 4 3) x) ((_ extract 1 0) x)))
(assert  (not (= ((_ extract 4 4) x) ((_ extract 0 0) x))) )
(check-sat)
