(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(declare-fun y () (_ BitVec 32))
(assert  (not (= ((_ extract 60 3) (concat x y)) (concat ((_ extract 28 0) x) ((_ extract 31 3) y)))) )
(check-sat)
