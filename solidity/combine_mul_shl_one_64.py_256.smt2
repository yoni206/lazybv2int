; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 256))
(declare-fun Y () (_ BitVec 256))
(assert
 (let ((?x13 (bvshl Y X)))
 (let ((?x10 (bvshl (_ bv1 256) X)))
 (let ((?x11 (bvmul ?x10 Y)))
 (and (distinct ?x11 ?x13) true)))))
(check-sat)
