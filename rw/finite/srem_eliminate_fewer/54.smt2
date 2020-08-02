
(set-logic QF_BV)
(declare-fun x () (_ BitVec 54))
(declare-fun y () (_ BitVec 54))
(define-fun mins () (_ BitVec 54) (_ bv9007199254740992 54))

(define-fun negative ((a (_ BitVec 54))) Bool (bvuge a (_ bv9007199254740992 54)))
(define-fun abs ((a (_ BitVec 54))) (_ BitVec 54) (ite (negative a) (bvneg a) a))
(define-fun abs_rem ((a (_ BitVec 54)) (b (_ BitVec 54))) (_ BitVec 54) (bvurem (abs a) (abs b)))
(define-fun left () (_ BitVec 54) (bvsrem x y))
(define-fun right () (_ BitVec 54) (ite (negative x) (bvneg (abs_rem x y)) (abs_rem x y)))
(assert (distinct left right))
(check-sat)
