; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 64))
(declare-fun Y () (_ BitVec 64))
(assert
 (let ((?x13 (bvshl Y X)))
 (let ((?x10 (bvshl (_ bv1 64) X)))
 (let ((?x11 (bvmul ?x10 Y)))
 (and (distinct ?x11 ?x13) true)))))
(check-sat)
