; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 64))
(declare-fun Y () (_ BitVec 64))
(assert
 (let ((?x19 (concat (ite (bvslt Y (_ bv0 64)) (_ bv6277101735386680763835789423207666416102355444464034512895 192) (_ bv0 192)) Y)))
 (let (($x41 (bvslt ?x19 (bvsub (_ bv115792089237316195423570985008687907853269984665640564039448360635876274864128 256) (concat (ite (bvslt X (_ bv0 64)) (_ bv6277101735386680763835789423207666416102355444464034512895 192) (_ bv0 192)) X)))))
 (let ((?x52 (ite (bvslt (concat (ite (bvslt X (_ bv0 64)) (_ bv6277101735386680763835789423207666416102355444464034512895 192) (_ bv0 192)) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x15 (bvand ?x52 (ite $x41 (_ bv1 256) (_ bv0 256)))))
 (let (($x83 (and (distinct ?x15 (_ bv0 256)) true)))
 (let (($x22 (=> (and (bvslt X (_ bv0 64)) (bvslt Y (_ bv0 64))) (bvslt (bvadd X Y) (_ bv0 64)))))
 (let (($x23 (not $x22)))
 (and (distinct $x23 $x83) true)))))))))
(check-sat)
