; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 16))
(declare-fun X () (_ BitVec 16))
(assert
 (let (($x43 (bvumul_noovfl X Y)))
 (let (($x25 (not $x43)))
 (let ((?x27 (ite (= (ite (= X (_ bv0 16)) (_ bv1 16) (_ bv0 16)) (_ bv0 16)) (_ bv1 16) (_ bv0 16))))
 (let ((?x31 (bvand ?x27 (ite (bvugt Y (ite (= X (_ bv0 16)) (_ bv0 16) (bvudiv (_ bv65535 16) X))) (_ bv1 16) (_ bv0 16)))))
 (let (($x9 (and (distinct ?x31 (_ bv0 16)) true)))
 (and (distinct $x9 $x25) true)))))))
(check-sat)
