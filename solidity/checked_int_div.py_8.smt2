; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 8))
(declare-fun X () (_ BitVec 8))
(assert
 (let ((?x32 (ite (= (concat (ite (bvslt Y (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) Y) (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x29 (ite (= (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639808 256) (concat (ite (bvslt X (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) X)) (_ bv1 256) (_ bv0 256))))
 (let ((?x33 (bvand ?x29 ?x32)))
 (let (($x34 (and (distinct ?x33 (_ bv0 256)) true)))
 (let (($x15 (not (not (and (= X (bvshl (_ bv1 8) (_ bv7 8))) (= Y (_ bv255 8)))))))
 (and (distinct $x15 $x34) true)))))))
(check-sat)
