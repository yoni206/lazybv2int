(set-option :incremental false)

(set-logic QF_BV)
(assert  (bvult (bvsmod (_ bv0 9) ((_ sign_extend 4) (_ bv29 5))) (_ bv1 9)) )
(check-sat)
