; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 128))
(declare-fun X () (_ BitVec 128))
(assert
 (let ((?x38 (ite (= (concat (ite (bvslt Y (_ bv0 128)) (_ bv340282366920938463463374607431768211455 128) (_ bv0 128)) Y) (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x44 (ite (= (_ bv115792089237316195423570985008687907853099843482180094807725896704197245534208 256) (concat (ite (bvslt X (_ bv0 128)) (_ bv340282366920938463463374607431768211455 128) (_ bv0 128)) X)) (_ bv1 256) (_ bv0 256))))
 (let ((?x40 (bvand ?x44 ?x38)))
 (let (($x12 (and (distinct ?x40 (_ bv0 256)) true)))
 (let (($x37 (not (not (and (= X (bvshl (_ bv1 128) (_ bv127 128))) (= Y (_ bv340282366920938463463374607431768211455 128)))))))
 (and (distinct $x37 $x12) true)))))))
(check-sat)
