(set-logic QF_BV)
(declare-fun a () (_ BitVec 3))
(declare-fun b () (_ BitVec 3))
(assert (bvult (bvor a b) (bvand a b)))
(check-sat)
