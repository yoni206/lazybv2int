(set-logic QF_BV)



(declare-fun v0 () (_ BitVec 16))
(assert (and
	 (bvult v0 (_ bv3 16))
	 (bvult (_ bv2 16) v0)))
(check-sat)
(exit)
