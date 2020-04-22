; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 16))
(declare-fun X () (_ BitVec 16))
(assert
 (let (($x43 (bvumul_noovfl X Y)))
 (let (($x25 (not $x43)))
 (let ((?x36 (concat (_ bv0 240) Y)))
 (let (($x33 (bvugt ?x36 (ite (= (concat (_ bv0 240) X) (_ bv0 256)) (_ bv0 256) (bvudiv (_ bv65535 256) (concat (_ bv0 240) X))))))
 (let ((?x37 (bvand (ite (= (ite (= (concat (_ bv0 240) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (ite $x33 (_ bv1 256) (_ bv0 256)))))
 (let (($x9 (and (distinct ?x37 (_ bv0 256)) true)))
 (and (distinct $x9 $x25) true))))))))
(check-sat)
