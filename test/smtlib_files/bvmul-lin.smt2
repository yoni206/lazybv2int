(set-logic QF_BV)

(declare-fun x () (_ BitVec 4))

(assert (= (bvmul #b1100 x) #b1000))
(check-sat)
