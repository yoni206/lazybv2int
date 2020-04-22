; benchmark generated from python API
(set-info :status unknown)
(declare-fun A () (_ BitVec 64))
(declare-fun B () (_ BitVec 64))
(declare-fun X () (_ BitVec 64))
(assert
 (bvult A (_ bv64 64)))
(assert
 (bvult B (_ bv64 64)))
(assert
 (let ((?x16 (bvshl (bvlshr ((_ int2bv 64) (- 1)) A) B)))
 (let ((?x26 (ite (bvugt B A) (bvand (bvshl X (bvsub B A)) ?x16) (bvand X ?x16))))
 (let ((?x27 (ite (bvugt A B) (bvand (bvlshr X (bvsub A B)) ?x16) ?x26)))
 (let ((?x12 (bvshl (bvlshr X A) B)))
 (and (distinct ?x12 ?x27) true))))))
(check-sat)
