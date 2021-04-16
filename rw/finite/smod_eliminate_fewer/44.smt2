
(set-logic QF_BV)
(declare-fun x () (_ BitVec 44))
(declare-fun y () (_ BitVec 44))
(define-fun mins () (_ BitVec 44) (_ bv8796093022208 44))
(define-fun negative ((a (_ BitVec 44))) Bool (bvuge a (_ bv8796093022208 44)))
(define-fun abs ((a (_ BitVec 44))) (_ BitVec 44) (ite (negative a) (bvneg a) a))
(define-fun u ((a (_ BitVec 44)) (b (_ BitVec 44))) (_ BitVec 44) (bvurem (abs a) (abs b)))
(define-fun neg_u ((a (_ BitVec 44)) (b (_ BitVec 44))) (_ BitVec 44) (bvneg (u a b)))
(define-fun cond_0 () Bool (= (u x y) (_ bv0 44)))
(define-fun cond_1 () Bool (and (not (negative x)) (not (negative y))))
(define-fun cond_2 () Bool (and (negative x) (not (negative y))))
(define-fun cond_3 () Bool (and (not (negative x)) (negative y)))
(define-fun left () (_ BitVec 44) (bvsmod x y))
(define-fun right () (_ BitVec 44) (ite cond_0 (u x y) (ite cond_1 (u x y) (ite cond_2 (bvadd (neg_u x y) y) (ite cond_3 (bvadd (u x y) y) (neg_u x y))))))
(assert (distinct left right))
(check-sat)