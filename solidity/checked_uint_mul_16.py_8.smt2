; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 8))
(declare-fun X () (_ BitVec 8))
(assert
 (let (($x7 (bvumul_noovfl X Y)))
 (let (($x8 (not $x7)))
 (let ((?x11 (concat (_ bv0 248) Y)))
 (let (($x21 (bvugt ?x11 (ite (= (concat (_ bv0 248) X) (_ bv0 256)) (_ bv0 256) (bvudiv (_ bv255 256) (concat (_ bv0 248) X))))))
 (let ((?x23 (bvand (ite (= (ite (= (concat (_ bv0 248) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (ite $x21 (_ bv1 256) (_ bv0 256)))))
 (let (($x24 (and (distinct ?x23 (_ bv0 256)) true)))
 (and (distinct $x24 $x8) true))))))))
(check-sat)
