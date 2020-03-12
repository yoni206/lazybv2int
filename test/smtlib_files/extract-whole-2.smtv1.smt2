(set-option :incremental false)

(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert  (not (= (concat (concat (concat (concat (concat (concat x (_ bv0 1)) (_ bv1 1)) (_ bv0 1)) (_ bv1 1)) (_ bv0 1)) (_ bv1 1)) (concat x (_ bv21 6)))) )
(check-sat)
