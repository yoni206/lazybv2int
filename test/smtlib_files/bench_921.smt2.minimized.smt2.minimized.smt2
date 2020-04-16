(set-logic QF_BV)
(declare-fun x () (_ BitVec 32))
(assert 
  (bvult 
    (bvashr 
      (bvmul 
        (bvashr 
          x
          ((_ zero_extend 24) (_ bv3 8))
        ) 
        ((_ zero_extend 24) (_ bv8 8))
      ) 
      ((_ zero_extend 24) (_ bv3 8))
    ) 
    (_ bv2048 32)
  )
)
(assert (= x (_ bv7 32)))
(check-sat)
(exit)
