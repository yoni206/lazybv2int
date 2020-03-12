; REQUIRES: cadical
; COMMAND-LINE: --incremental --bv-sat-solver=cadical --bitblast=eager
(set-logic QF_BV)
(set-option :incremental true)
(declare-fun a () (_ BitVec 16))
(declare-fun b () (_ BitVec 16))
(declare-fun c () (_ BitVec 16))

(assert (bvult a (bvadd b c)))

(check-sat)

(push 1)
(assert (bvult c b))

(check-sat)


(push 1)
(assert (bvugt c b))

(check-sat)
(pop 2)


(check-sat)
(exit)
