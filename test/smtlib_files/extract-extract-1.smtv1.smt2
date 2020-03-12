(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= ((_ extract 15 1) ((_ extract 31 0) x)) ((_ extract 15 1) x))) )
(check-sat)
