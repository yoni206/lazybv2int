; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 64))
(declare-fun X () (_ BitVec 64))
(assert
 (let ((?x49 (ite (= (concat (ite (bvslt Y (_ bv0 64)) (_ bv6277101735386680763835789423207666416102355444464034512895 192) (_ bv0 192)) Y) (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x13 (ite (= (_ bv115792089237316195423570985008687907853269984665640564039448360635876274864128 256) (concat (ite (bvslt X (_ bv0 64)) (_ bv6277101735386680763835789423207666416102355444464034512895 192) (_ bv0 192)) X)) (_ bv1 256) (_ bv0 256))))
 (let ((?x50 (bvand ?x13 ?x49)))
 (let (($x21 (and (distinct ?x50 (_ bv0 256)) true)))
 (let (($x11 (not (not (and (= X (bvshl (_ bv1 64) (_ bv63 64))) (= Y (_ bv18446744073709551615 64)))))))
 (and (distinct $x11 $x21) true)))))))
(check-sat)
