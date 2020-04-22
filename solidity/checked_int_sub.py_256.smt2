; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 256))
(declare-fun X () (_ BitVec 256))
(assert
 (let ((?x42 (ite (bvslt Y (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x37 (bvand ?x42 (ite (bvsgt X (bvadd (_ bv57896044618658097711785492504343953926634992332820282019728792003956564819967 256) Y)) (_ bv1 256) (_ bv0 256)))))
 (let (($x84 (and (distinct ?x37 (_ bv0 256)) true)))
 (let (($x69 (=> (and (bvslt (_ bv0 256) X) (bvslt (_ bv0 256) (bvneg Y))) (bvslt (_ bv0 256) (bvadd X (bvneg Y))))))
 (let (($x53 (bvslt X (_ bv0 256))))
 (let (($x59 (not (ite (= Y (bvshl (_ bv1 256) (_ bv255 256))) $x53 $x69))))
 (and (distinct $x59 $x84) true))))))))
(check-sat)
