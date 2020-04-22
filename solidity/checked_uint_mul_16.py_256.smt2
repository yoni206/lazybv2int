; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 256))
(declare-fun X () (_ BitVec 256))
(assert
 (let (($x21 (bvumul_noovfl X Y)))
 (let (($x26 (not $x21)))
 (let ((?x27 (ite (= (ite (= X (_ bv0 256)) (_ bv1 256) (_ bv0 256)) (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x7 (bvand ?x27 (ite (bvugt Y (ite (= X (_ bv0 256)) (_ bv0 256) (bvudiv (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256) X))) (_ bv1 256) (_ bv0 256)))))
 (let (($x11 (and (distinct ?x7 (_ bv0 256)) true)))
 (and (distinct $x11 $x26) true)))))))
(check-sat)
