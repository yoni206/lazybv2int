; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 256))
(declare-fun Y () (_ BitVec 256))
(assert
 (let (($x24 (bvslt X (_ bv0 256))))
 (let ((?x10 (ite $x24 (_ bv1 256) (_ bv0 256))))
 (let ((?x50 (bvand ?x10 (ite (bvslt Y (bvsub (_ bv57896044618658097711785492504343953926634992332820282019728792003956564819968 256) X)) (_ bv1 256) (_ bv0 256)))))
 (let (($x85 (and (distinct ?x50 (_ bv0 256)) true)))
 (let (($x12 (not (=> (and $x24 (bvslt Y (_ bv0 256))) (bvslt (bvadd X Y) (_ bv0 256))))))
 (and (distinct $x12 $x85) true)))))))
(check-sat)
