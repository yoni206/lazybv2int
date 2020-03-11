; COMMAND-LINE: --solve-bv-as-int=1 --no-check-models  --no-check-unsat-cores --no-check-proofs
; COMMAND-LINE: --solve-bv-as-int=5 --no-check-models  --no-check-unsat-cores --no-check-proofs
; EXPECT: unsat
(set-logic QF_BV)
(declare-fun s () (_ BitVec 1))
(declare-fun t () (_ BitVec 1))
;(assert (not (= (bvlshr s (bvor (bvand t #b0000) s)) #b0000)))
(assert (distinct (bvand t s) #b0))
(assert (= s #b0))
(check-sat)
(exit)
