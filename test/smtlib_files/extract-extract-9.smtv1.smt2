(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= ((_ extract 3 1) ((_ extract 7 2) x)) ((_ extract 5 3) x))) )
(check-sat)
