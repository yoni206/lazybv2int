(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= ((_ extract 2 2) ((_ extract 7 2) x)) ((_ extract 4 4) x))) )
(check-sat)
