(set-logic QF_BV)

(declare-fun x () (_ BitVec 4))
(assert (not (= (bvmul (bvneg (bvmul #b1111 #b1111)) #b1111) x)))
(check-sat)
