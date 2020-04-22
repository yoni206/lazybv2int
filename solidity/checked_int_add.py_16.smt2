; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 16))
(declare-fun Y () (_ BitVec 16))
(assert
 (let ((?x49 (concat (ite (bvslt Y (_ bv0 16)) (_ bv1766847064778384329583297500742918515827483896875618958121606201292619775 240) (_ bv0 240)) Y)))
 (let (($x34 (bvslt ?x49 (bvsub (_ bv115792089237316195423570985008687907853269984665640564039457584007913129607168 256) (concat (ite (bvslt X (_ bv0 16)) (_ bv1766847064778384329583297500742918515827483896875618958121606201292619775 240) (_ bv0 240)) X)))))
 (let ((?x56 (ite (bvslt (concat (ite (bvslt X (_ bv0 16)) (_ bv1766847064778384329583297500742918515827483896875618958121606201292619775 240) (_ bv0 240)) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x35 (bvand ?x56 (ite $x34 (_ bv1 256) (_ bv0 256)))))
 (let (($x81 (and (distinct ?x35 (_ bv0 256)) true)))
 (let (($x13 (=> (and (bvslt X (_ bv0 16)) (bvslt Y (_ bv0 16))) (bvslt (bvadd X Y) (_ bv0 16)))))
 (let (($x14 (not $x13)))
 (and (distinct $x14 $x81) true)))))))))
(check-sat)
