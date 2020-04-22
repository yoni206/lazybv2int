; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 256))
(declare-fun X () (_ BitVec 256))
(assert
 (let ((?x13 (bvlshr X Y)))
 (let ((?x8 (bvshl (_ bv1 256) Y)))
 (let (($x10 (= ?x8 (_ bv0 256))))
 (let ((?x12 (ite $x10 (_ bv0 256) (bvudiv X ?x8))))
 (and (distinct ?x12 ?x13) true))))))
(check-sat)
