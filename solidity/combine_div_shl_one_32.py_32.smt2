; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 32))
(declare-fun X () (_ BitVec 32))
(assert
 (let ((?x13 (bvlshr X Y)))
 (let ((?x8 (bvshl (_ bv1 32) Y)))
 (let (($x10 (= ?x8 (_ bv0 32))))
 (let ((?x12 (ite $x10 (_ bv0 32) (bvudiv X ?x8))))
 (and (distinct ?x12 ?x13) true))))))
(check-sat)
