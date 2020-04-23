(set-info :smt-lib-version 2.6)
(set-logic QF_BV)



(assert (= #b1 (bvsdiv #b0 #b0)))
(assert (= #b10 (bvsmod #b10 #b00)))

(check-sat)
(exit)
