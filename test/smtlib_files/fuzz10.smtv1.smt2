(set-option :incremental false)

(set-logic QF_BV)
(declare-fun v0 () (_ BitVec 1))
(assert  (bvsgt v0 v0) )
(check-sat)
