(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(assert  (not (= ((_ extract 62 1) (concat x y)) (concat ((_ extract 30 0) x) ((_ extract 31 1) y)))) )
(check-sat)
