(set-option :incremental false)

(set-logic QF_BV)
(assert  (not (= ((_ extract 6 2) (_ bv56 9)) (_ bv14 5))) )
(check-sat)
