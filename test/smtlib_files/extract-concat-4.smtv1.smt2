(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(assert  (not (= ((_ extract 31 0) (concat x y)) ((_ extract 31 0) y))) )
(check-sat)
