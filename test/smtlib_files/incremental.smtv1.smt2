(set-option :incremental false)

(set-logic QF_BV)
(declare-fun v4 () (_ BitVec 16))
(declare-fun dummy4 () (_ BitVec 1))
(declare-fun a () (_ BitVec 16))
(assert  (and true true true (and (= ((_ extract 15 13) a) (concat ((_ extract 15 14) v4) dummy4)) (= ((_ extract 14 12) a) (concat dummy4 ((_ extract 13 12) v4)))) (not (= ((_ extract 14 14) v4) ((_ extract 13 13) v4)))) )
(check-sat)
