; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 32))
(declare-fun X () (_ BitVec 32))
(assert
 (let (($x17 (not (= ((_ extract 32 32) (bvadd ((_ zero_extend 1) X) ((_ zero_extend 1) Y))) (_ bv0 1)))))
 (let ((?x6 (ite (bvugt (concat (_ bv0 224) X) (bvsub (_ bv4294967295 256) (concat (_ bv0 224) Y))) (_ bv1 256) (_ bv0 256))))
 (let (($x7 (and (distinct ?x6 (_ bv0 256)) true)))
 (and (distinct $x7 $x17) true)))))
(check-sat)
