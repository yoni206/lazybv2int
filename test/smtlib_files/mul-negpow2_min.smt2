(set-logic QF_BV)

(declare-fun a () (_ BitVec 2))
(declare-fun b () (_ BitVec 2))
(assert (not (= (bvmul a (_ bv2 2)) (bvshl (bvadd (bvnot a) (_ bv1 2)) (_ bv1 2)))))
(assert (= a (_ bv1 2)))
(check-sat)
