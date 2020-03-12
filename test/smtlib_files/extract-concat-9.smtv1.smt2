(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(assert  (not (= ((_ extract 61 2) (concat x y)) (concat ((_ extract 29 0) x) ((_ extract 31 2) y)))) )
(check-sat)
