; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 32))
(declare-fun Y () (_ BitVec 32))
(assert
 (let (($x25 (bvule Y X)))
 (let (($x5 (not $x25)))
 (let ((?x6 (ite (bvult (concat (_ bv0 224) X) (concat (_ bv0 224) Y)) (_ bv1 256) (_ bv0 256))))
 (let (($x7 (and (distinct ?x6 (_ bv0 256)) true)))
 (and (distinct $x7 $x5) true))))))
(check-sat)
