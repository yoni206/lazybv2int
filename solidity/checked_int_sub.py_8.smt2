; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 8))
(declare-fun X () (_ BitVec 8))
(assert
 (let ((?x32 (concat (ite (bvslt X (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) X)))
 (let (($x49 (bvsgt ?x32 (bvadd (_ bv127 256) (concat (ite (bvslt Y (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) Y)))))
 (let ((?x41 (ite (bvslt (concat (ite (bvslt Y (_ bv0 8)) (_ bv452312848583266388373324160190187140051835877600158453279131187530910662655 248) (_ bv0 248)) Y) (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x51 (bvand ?x41 (ite $x49 (_ bv1 256) (_ bv0 256)))))
 (let (($x73 (and (distinct ?x51 (_ bv0 256)) true)))
 (let (($x19 (=> (and (bvslt (_ bv0 8) X) (bvslt (_ bv0 8) (bvneg Y))) (bvslt (_ bv0 8) (bvadd X (bvneg Y))))))
 (let (($x13 (bvslt X (_ bv0 8))))
 (let (($x21 (not (ite (= Y (bvshl (_ bv1 8) (_ bv7 8))) $x13 $x19))))
 (and (distinct $x21 $x73) true))))))))))
(check-sat)