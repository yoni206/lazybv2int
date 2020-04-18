(set-logic QF_BV)
(declare-fun a () (_ BitVec 4))
(declare-fun b () (_ BitVec 4))
(assert (bvult (bvshl a b) (bvlshr a b)))

(check-sat)
