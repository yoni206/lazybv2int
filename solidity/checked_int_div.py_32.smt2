; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 32))
(declare-fun X () (_ BitVec 32))
(assert
 (let ((?x32 (ite (= (concat (ite (bvslt Y (_ bv0 32)) (_ bv26959946667150639794667015087019630673637144422540572481103610249215 224) (_ bv0 224)) Y) (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x22 (ite (= (_ bv115792089237316195423570985008687907853269984665640564039457584007910982156288 256) (concat (ite (bvslt X (_ bv0 32)) (_ bv26959946667150639794667015087019630673637144422540572481103610249215 224) (_ bv0 224)) X)) (_ bv1 256) (_ bv0 256))))
 (let ((?x33 (bvand ?x22 ?x32)))
 (let (($x41 (and (distinct ?x33 (_ bv0 256)) true)))
 (let (($x20 (not (not (and (= X (bvshl (_ bv1 32) (_ bv31 32))) (= Y (_ bv4294967295 32)))))))
 (and (distinct $x20 $x41) true)))))))
(check-sat)
