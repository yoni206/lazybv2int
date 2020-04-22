; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 64))
(declare-fun Y () (_ BitVec 64))
(assert
 (let (($x21 (bvule Y X)))
 (let (($x35 (not $x21)))
 (let ((?x17 (ite (bvult (concat (_ bv0 192) X) (concat (_ bv0 192) Y)) (_ bv1 256) (_ bv0 256))))
 (let (($x36 (and (distinct ?x17 (_ bv0 256)) true)))
 (and (distinct $x36 $x35) true))))))
(check-sat)
