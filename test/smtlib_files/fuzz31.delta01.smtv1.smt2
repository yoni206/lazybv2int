(set-option :incremental false)

(set-logic QF_BV)
(declare-fun v1 () (_ BitVec 4))
(assert  (= (bvmul (_ bv8 4) (bvmul ((_ repeat 1) (_ bv12 4)) ((_ sign_extend 3) (ite (bvule (_ bv8 4) v1) (_ bv1 1) (_ bv0 1))))) (_ bv0 4)) )
(check-sat)
