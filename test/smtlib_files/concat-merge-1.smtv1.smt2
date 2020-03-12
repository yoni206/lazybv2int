(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= (concat ((_ extract 4 2) x) ((_ extract 1 0) x)) ((_ extract 4 0) x))) )
(check-sat)
