; benchmark generated from python API
(set-info :status unknown)
(declare-fun X () (_ BitVec 256))
(declare-fun Y () (_ BitVec 256))
(assert
 (let (($x29 (bvule Y X)))
 (let (($x19 (not $x29)))
 (let ((?x34 (ite (bvult X Y) (_ bv1 256) (_ bv0 256))))
 (let (($x21 (and (distinct ?x34 (_ bv0 256)) true)))
 (and (distinct $x21 $x19) true))))))
(check-sat)
