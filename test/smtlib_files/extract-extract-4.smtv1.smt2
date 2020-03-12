(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (let ((_let_0 ((_ extract 15 1) x))) (not (= ((_ extract 14 0) _let_0) _let_0))) )
(check-sat)
