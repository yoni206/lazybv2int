(set-logic QF_BV)

(declare-fun a () (_ BitVec 4))
(declare-fun b () (_ BitVec 4))
(assert (not (= (bvmul a (_ bv12 4)) (bvshl (bvnot a) (_ bv2 4)))))
(check-sat)
