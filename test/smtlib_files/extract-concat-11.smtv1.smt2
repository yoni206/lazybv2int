(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(assert  (not (= ((_ extract 59 4) (concat x y)) (concat ((_ extract 27 0) x) ((_ extract 31 4) y)))) )
(check-sat)
