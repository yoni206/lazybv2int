(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= (concat (concat (concat (concat (concat (concat (_ bv0 1) (_ bv1 1)) (_ bv0 1)) (_ bv1 1)) (_ bv0 1)) (_ bv1 1)) x) (concat (_ bv21 6) x))) )
(check-sat)
