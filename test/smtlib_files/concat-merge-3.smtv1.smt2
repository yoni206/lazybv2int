(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= (concat ((_ extract 16 8) x) ((_ extract 7 0) x)) ((_ extract 16 0) x))) )
(check-sat)
