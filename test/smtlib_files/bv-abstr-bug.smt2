; COMMAND-LINE: --bv-abstraction --bitblast=eager --no-check-models
;
; BV-abstraction should not be applied
(set-logic QF_BV)

(declare-const a Bool)
(declare-const b Bool)
(declare-const c Bool)
(declare-const d Bool)
(assert
 (or
  (and a b)
  (and c d)
 )
)
(check-sat)
