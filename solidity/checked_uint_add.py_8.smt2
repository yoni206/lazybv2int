; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 8))
(declare-fun X () (_ BitVec 8))
(assert
 (let (($x13 (not (= ((_ extract 8 8) (bvadd ((_ zero_extend 1) X) ((_ zero_extend 1) Y))) (_ bv0 1)))))
 (let ((?x22 (ite (bvugt (concat (_ bv0 248) X) (bvsub (_ bv255 256) (concat (_ bv0 248) Y))) (_ bv1 256) (_ bv0 256))))
 (let (($x23 (and (distinct ?x22 (_ bv0 256)) true)))
 (and (distinct $x23 $x13) true)))))
(check-sat)
