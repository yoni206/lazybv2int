; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 8))
(declare-fun X () (_ BitVec 8))
(assert
 (let (($x7 (bvumul_noovfl X Y)))
 (let (($x8 (not $x7)))
 (let ((?x11 (concat (_ bv0 8) Y)))
 (let (($x21 (bvugt ?x11 (ite (= (concat (_ bv0 8) X) (_ bv0 16)) (_ bv0 16) (bvudiv (_ bv255 16) (concat (_ bv0 8) X))))))
 (let ((?x23 (bvand (ite (= (ite (= (concat (_ bv0 8) X) (_ bv0 16)) (_ bv1 16) (_ bv0 16)) (_ bv0 16)) (_ bv1 16) (_ bv0 16)) (ite $x21 (_ bv1 16) (_ bv0 16)))))
 (let (($x24 (and (distinct ?x23 (_ bv0 16)) true)))
 (and (distinct $x24 $x8) true))))))))
(check-sat)
