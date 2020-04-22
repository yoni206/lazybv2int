; benchmark generated from python API
(set-info :status unknown)
(declare-fun A () (_ BitVec 8))
(declare-fun X () (_ BitVec 8))
(assert
 (let ((?x20 (bvshl X A)))
 (let ((?x12 (bvshl ((_ int2bv 16) (bv2int X)) ((_ int2bv 16) (bv2int A)))))
 (let ((?x19 ((_ int2bv 8) (bv2int (bvand ?x12 ((_ int2bv 16) (bv2int ((_ int2bv 8) (- 1)))))))))
 (and (distinct ?x19 ?x20) true)))))
(check-sat)
