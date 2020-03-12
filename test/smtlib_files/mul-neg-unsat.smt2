(set-logic QF_BV)

(declare-fun a () (_ BitVec 32))
(declare-fun b () (_ BitVec 32))
(assert (not (= (bvmul a b) (bvmul (bvneg a) (bvneg b)))))
(check-sat)