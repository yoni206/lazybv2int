; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 32))
(declare-fun Y () (_ BitVec 32))
(assert
 (let ((?x24 (concat (ite (bvslt Y (_ bv0 32)) (_ bv26959946667150639794667015087019630673637144422540572481103610249215 224) (_ bv0 224)) Y)))
 (let (($x59 (bvslt ?x24 (bvsub (_ bv115792089237316195423570985008687907853269984665640564039457584007910982156288 256) (concat (ite (bvslt X (_ bv0 32)) (_ bv26959946667150639794667015087019630673637144422540572481103610249215 224) (_ bv0 224)) X)))))
 (let ((?x28 (ite (bvslt (concat (ite (bvslt X (_ bv0 32)) (_ bv26959946667150639794667015087019630673637144422540572481103610249215 224) (_ bv0 224)) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x45 (bvand ?x28 (ite $x59 (_ bv1 256) (_ bv0 256)))))
 (let (($x100 (and (distinct ?x45 (_ bv0 256)) true)))
 (let (($x47 (=> (and (bvslt X (_ bv0 32)) (bvslt Y (_ bv0 32))) (bvslt (bvadd X Y) (_ bv0 32)))))
 (let (($x48 (not $x47)))
 (and (distinct $x48 $x100) true)))))))))
(check-sat)
