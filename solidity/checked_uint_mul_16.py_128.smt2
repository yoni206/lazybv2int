; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 128))
(declare-fun X () (_ BitVec 128))
(assert
 (let (($x36 (bvumul_noovfl X Y)))
 (let (($x41 (not $x36)))
 (let ((?x12 (concat (_ bv0 128) Y)))
 (let (($x23 (bvugt ?x12 (ite (= (concat (_ bv0 128) X) (_ bv0 256)) (_ bv0 256) (bvudiv (_ bv340282366920938463463374607431768211455 256) (concat (_ bv0 128) X))))))
 (let ((?x20 (bvand (ite (= (ite (= (concat (_ bv0 128) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (ite $x23 (_ bv1 256) (_ bv0 256)))))
 (let (($x32 (and (distinct ?x20 (_ bv0 256)) true)))
 (and (distinct $x32 $x41) true))))))))
(check-sat)
