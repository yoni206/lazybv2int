(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= (concat ((_ extract 2 1) x) ((_ extract 0 0) x)) ((_ extract 2 0) x))) )
(check-sat)
