

(set-logic QF_BV)
(declare-fun v0 () (_ BitVec 1))
(declare-fun v1 () (_ BitVec 10))
(assert (= v1 ((_ repeat 10) v0)))
(check-sat)
