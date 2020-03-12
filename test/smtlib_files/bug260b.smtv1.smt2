(set-option :incremental false)

(set-logic QF_BV)
(declare-fun a () (_ BitVec 32))
(assert  (= (_ bv0 5) (concat (_ bv0 3) ((_ extract 6 5) a))) )
(check-sat)
