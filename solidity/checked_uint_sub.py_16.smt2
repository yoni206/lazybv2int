; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 16))
(declare-fun Y () (_ BitVec 16))
(assert
 (let (($x36 (bvule Y X)))
 (let (($x18 (not $x36)))
 (let ((?x20 (ite (bvult (concat (_ bv0 240) X) (concat (_ bv0 240) Y)) (_ bv1 256) (_ bv0 256))))
 (let (($x9 (and (distinct ?x20 (_ bv0 256)) true)))
 (and (distinct $x9 $x18) true))))))
(check-sat)
