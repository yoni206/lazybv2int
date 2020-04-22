; benchmark generated from python API
(set-info :status unknown)
(declare-fun Y () (_ BitVec 64))
(declare-fun X () (_ BitVec 64))
(assert
 (let (($x10 (not (= ((_ extract 64 64) (bvadd ((_ zero_extend 1) X) ((_ zero_extend 1) Y))) (_ bv0 1)))))
 (let ((?x23 (ite (bvugt (concat (_ bv0 192) X) (bvsub (_ bv18446744073709551615 256) (concat (_ bv0 192) Y))) (_ bv1 256) (_ bv0 256))))
 (let (($x41 (and (distinct ?x23 (_ bv0 256)) true)))
 (and (distinct $x41 $x10) true)))))
(check-sat)
