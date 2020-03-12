(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 8))
(assert (= x (_ bv85 8)))
(assert  (not (= (concat (concat (concat ((_ extract 0 0) x) ((_ extract 2 2) x)) ((_ extract 4 4) x)) ((_ extract 6 6) x)) (_ bv15 4))) )
(check-sat)
