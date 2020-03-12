(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= ((_ extract 7 2) ((_ extract 31 0) x)) ((_ extract 7 2) x))) )
(check-sat)
