; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 8))
(declare-fun Y () (_ BitVec 8))
(assert
 (let ((?x26 (concat (ite (bvslt Y (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) Y)))
 (let (($x40 (bvslt ?x26 (bvsub (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639808 256) (concat (ite (bvslt X (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) X)))))
 (let ((?x32 (ite (bvslt (concat (ite (bvslt X (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x42 (bvand ?x32 (ite $x40 (_ bv1 256) (_ bv0 256)))))
 (let (($x74 (and (distinct ?x42 (_ bv0 256)) true)))
 (let (($x19 (=> (and (bvslt X (_ bv0 8)) (bvslt Y (_ bv0 8))) (bvslt (bvadd X Y) (_ bv0 8)))))
 (let (($x20 (not $x19)))
 (and (distinct $x20 $x74) true)))))))))
(check-sat)
