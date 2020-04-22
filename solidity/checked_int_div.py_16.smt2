; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 16))
(declare-fun X () (_ BitVec 16))
(assert
 (let ((?x49 (ite (= (concat (ite (bvslt Y (_ bv0 16)) (_ bv1766847064778384329583297500742918515827483896875618958121606201292619775 240) (_ bv0 240)) Y) (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x45 (ite (= (_ bv115792089237316195423570985008687907853269984665640564039457584007913129607168 256) (concat (ite (bvslt X (_ bv0 16)) (_ bv1766847064778384329583297500742918515827483896875618958121606201292619775 240) (_ bv0 240)) X)) (_ bv1 256) (_ bv0 256))))
 (let ((?x50 (bvand ?x45 ?x49)))
 (let (($x25 (and (distinct ?x50 (_ bv0 256)) true)))
 (let (($x40 (not (not (and (= X (bvshl (_ bv1 16) (_ bv15 16))) (= Y (_ bv65535 16)))))))
 (and (distinct $x40 $x25) true)))))))
(check-sat)
