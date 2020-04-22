; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 64))
(declare-fun X () (_ BitVec 64))
(assert
 (let (($x11 (bvumul_noovfl X Y)))
 (let (($x42 (not $x11)))
 (let ((?x33 (concat (_ bv0 192) Y)))
 (let (($x38 (bvugt ?x33 (ite (= (concat (_ bv0 192) X) (_ bv0 256)) (_ bv0 256) (bvudiv (_ bv18446744073709551615 256) (concat (_ bv0 192) X))))))
 (let ((?x35 (bvand (ite (= (ite (= (concat (_ bv0 192) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (ite $x38 (_ bv1 256) (_ bv0 256)))))
 (let (($x43 (and (distinct ?x35 (_ bv0 256)) true)))
 (and (distinct $x43 $x42) true))))))))
(check-sat)
