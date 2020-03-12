(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= (concat ((_ extract 8 4) x) ((_ extract 3 0) x)) ((_ extract 8 0) x))) )
(check-sat)
