(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(assert  (not (= ((_ extract 29 2) (concat x y)) ((_ extract 29 2) y))) )
(check-sat)
