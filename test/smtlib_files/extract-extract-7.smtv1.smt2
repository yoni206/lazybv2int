(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= ((_ extract 3 3) ((_ extract 15 1) x)) ((_ extract 4 4) x))) )
(check-sat)
