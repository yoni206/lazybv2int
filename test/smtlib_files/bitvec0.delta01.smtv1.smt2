(set-option :incremental false)

(set-logic QF_BV)
(declare-fun t () (_ BitVec 32))
(assert  (not (ite (= ((_ extract 4 0) t) ((_ extract 6 2) t)) (and (= ((_ extract 6 6) t) ((_ extract 0 0) t)) (= ((_ extract 1 1) t) ((_ extract 5 5) t))) true)) )
(check-sat)
