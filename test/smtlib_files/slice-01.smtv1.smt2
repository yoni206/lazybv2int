(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 64))
(declare-fun y () (_ BitVec 32))
(declare-fun z () (_ BitVec 32))
(assert (= x (concat y z)))
(assert  (not (= ((_ extract 63 32) x) y)) )
(check-sat)
