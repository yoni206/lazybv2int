; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 16))
(declare-fun X () (_ BitVec 16))
(assert
 (let ((?x73 (ite (bvsgt Y (_ bv0 16)) (_ bv1 16) (_ bv0 16))))
 (let ((?x24 (ite (bvslt X (_ bv0 16)) (_ bv1 16) (_ bv0 16))))
 (let ((?x41 (bvand (bvand ?x24 ?x73) (ite (bvslt X (ite (= Y (_ bv0 16)) (_ bv0 16) (bvsdiv (_ bv32768 16) Y))) (_ bv1 16) (_ bv0 16)))))
 (let ((?x29 (ite (bvslt Y (_ bv0 16)) (_ bv1 16) (_ bv0 16))))
 (let ((?x60 (ite (bvsgt X (_ bv0 16)) (_ bv1 16) (_ bv0 16))))
 (let ((?x74 (bvand (bvand ?x60 ?x29) (ite (bvslt Y (ite (= X (_ bv0 16)) (_ bv0 16) (bvsdiv (_ bv32768 16) X))) (_ bv1 16) (_ bv0 16)))))
 (let (($x84 (or (and (distinct ?x74 (_ bv0 16)) true) (and (distinct ?x41 (_ bv0 16)) true))))
 (let (($x7 (bvsmul_noudfl X Y)))
 (let (($x8 (not $x7)))
 (and (distinct $x8 $x84) true)))))))))))
(check-sat)
