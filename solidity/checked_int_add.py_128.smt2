; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 128))
(declare-fun Y () (_ BitVec 128))
(assert
 (let ((?x23 (concat (ite (bvslt Y (_ bv0 128)) (_ bv340282366920938463463374607431768211455 128) (_ bv0 128)) Y)))
 (let (($x27 (bvslt ?x23 (bvsub (_ bv115792089237316195423570985008687907853099843482180094807725896704197245534208 256) (concat (ite (bvslt X (_ bv0 128)) (_ bv340282366920938463463374607431768211455 128) (_ bv0 128)) X)))))
 (let ((?x14 (ite (bvslt (concat (ite (bvslt X (_ bv0 128)) (_ bv340282366920938463463374607431768211455 128) (_ bv0 128)) X) (_ bv0 256)) (_ bv1 256) (_ bv0 256))))
 (let ((?x9 (bvand ?x14 (ite $x27 (_ bv1 256) (_ bv0 256)))))
 (let (($x32 (and (distinct ?x9 (_ bv0 256)) true)))
 (let (($x8 (=> (and (bvslt X (_ bv0 128)) (bvslt Y (_ bv0 128))) (bvslt (bvadd X Y) (_ bv0 128)))))
 (let (($x18 (not $x8)))
 (and (distinct $x18 $x32) true)))))))))
(check-sat)
