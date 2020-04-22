; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 256))
(declare-fun X () (_ BitVec 256))
(assert
 (let (($x15 (= Y (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256))))
 (let ((?x24 (ite $x15 (_ bv1 256) (_ bv0 256))))
 (let ((?x25 (bvand (ite (= (_ bv57896044618658097711785492504343953926634992332820282019728792003956564819968 256) X) (_ bv1 256) (_ bv0 256)) ?x24)))
 (let (($x10 (and (distinct ?x25 (_ bv0 256)) true)))
 (let (($x23 (not (not (and (= X (bvshl (_ bv1 256) (_ bv255 256))) $x15)))))
 (and (distinct $x23 $x10) true)))))))
(check-sat)
