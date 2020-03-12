(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(assert (not (= ((_ extract 28 3) (concat x y)) ((_ extract 28 3) y))) )
(check-sat)
