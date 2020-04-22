; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 32))
(declare-fun X () (_ BitVec 32))
(assert
 (let (($x32 (bvumul_noovfl X Y)))
 (let (($x5 (not $x32)))
 (let ((?x21 (concat (_ bv0 224) Y)))
 (let (($x12 (bvugt ?x21 (ite (= (concat (_ bv0 224) X) (_ bv0 256)) (_ bv0 256) (bvudiv (_ bv4294967295 256) (concat (_ bv0 224) X))))))
 (let ((?x22 (bvand (ite (= (ite (= (concat (_ bv0 224) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (ite $x12 (_ bv1 256) (_ bv0 256)))))
 (let (($x7 (and (distinct ?x22 (_ bv0 256)) true)))
 (and (distinct $x7 $x5) true))))))))
(check-sat)
