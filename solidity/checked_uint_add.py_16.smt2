; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 16))
(declare-fun X () (_ BitVec 16))
(assert
 (let (($x26 (not (= ((_ extract 16 16) (bvadd ((_ zero_extend 1) X) ((_ zero_extend 1) Y))) (_ bv0 1)))))
 (let ((?x27 (ite (bvugt (concat (_ bv0 240) X) (bvsub (_ bv65535 256) (concat (_ bv0 240) Y))) (_ bv1 256) (_ bv0 256))))
 (let (($x14 (and (distinct ?x27 (_ bv0 256)) true)))
 (and (distinct $x14 $x26) true)))))
(check-sat)
