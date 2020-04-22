; benchmark generated from python API
(set-info :status unknown)
(declare-fun B () (_ BitVec 256))
(declare-fun A () (_ BitVec 256))
(declare-fun X () (_ BitVec 256))
(assert
 (bvult B (_ bv256 256)))
(assert
 (bvult B (_ bv256 256)))
(assert
 (let ((?x14 (bvshl A B)))
 (let ((?x15 (bvshl X B)))
 (let ((?x16 (bvand ?x15 ?x14)))
 (let ((?x13 (bvshl (bvand A X) B)))
 (and (distinct ?x13 ?x16) true))))))
(check-sat)
