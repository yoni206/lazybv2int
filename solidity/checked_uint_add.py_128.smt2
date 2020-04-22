; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 128))
(declare-fun X () (_ BitVec 128))
(assert
 (let (($x25 (not (= ((_ extract 128 128) (bvadd ((_ zero_extend 1) X) ((_ zero_extend 1) Y))) (_ bv0 1)))))
 (let ((?x14 (ite (bvugt (concat (_ bv0 128) X) (bvsub (_ bv340282366920938463463374607431768211455 256) (concat (_ bv0 128) Y))) (_ bv1 256) (_ bv0 256))))
 (let (($x30 (and (distinct ?x14 (_ bv0 256)) true)))
 (and (distinct $x30 $x25) true)))))
(check-sat)
