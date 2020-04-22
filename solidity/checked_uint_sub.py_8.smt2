; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 8))
(declare-fun Y () (_ BitVec 8))
(assert
 (let (($x7 (bvule Y X)))
 (let (($x8 (not $x7)))
 (let ((?x16 (ite (bvult (concat (_ bv0 248) X) (concat (_ bv0 248) Y)) (_ bv1 256) (_ bv0 256))))
 (let (($x17 (and (distinct ?x16 (_ bv0 256)) true)))
 (and (distinct $x17 $x8) true))))))
(check-sat)
