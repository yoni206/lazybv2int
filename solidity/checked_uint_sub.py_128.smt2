; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 128))
(declare-fun Y () (_ BitVec 128))
(assert
 (let (($x11 (bvule Y X)))
 (let (($x34 (not $x11)))
 (let ((?x9 (ite (bvult (concat (_ bv0 128) X) (concat (_ bv0 128) Y)) (_ bv1 256) (_ bv0 256))))
 (let (($x25 (and (distinct ?x9 (_ bv0 256)) true)))
 (and (distinct $x25 $x34) true))))))
(check-sat)
