; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 256))
(declare-fun X () (_ BitVec 256))
(assert
 (let (($x15 (not (= ((_ extract 256 256) (bvadd ((_ zero_extend 1) X) ((_ zero_extend 1) Y))) (_ bv0 1)))))
 (let ((?x34 (ite (bvugt X (bvsub (_ bv115792089237316195423570985008687907853269984665640564039457584007913129639935 256) Y)) (_ bv1 256) (_ bv0 256))))
 (let (($x19 (and (distinct ?x34 (_ bv0 256)) true)))
 (and (distinct $x19 $x15) true)))))
(check-sat)
