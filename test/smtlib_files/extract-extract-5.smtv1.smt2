(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= ((_ extract 7 1) ((_ extract 15 1) x)) ((_ extract 8 2) x))) )
(check-sat)
