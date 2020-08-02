
(set-logic QF_BV)
(declare-fun x () (_ BitVec 54))
(declare-fun y () (_ BitVec 54))
(define-fun mins () (_ BitVec 54) (_ bv9007199254740992 54))

(define-fun negative ((a (_ BitVec 54))) Bool (bvuge a (_ bv9007199254740992 54)))
(define-fun abs ((a (_ BitVec 54))) (_ BitVec 54) (ite (negative a) (bvneg a) a))
(define-fun abs_div ((a (_ BitVec 54)) (b (_ BitVec 54))) (_ BitVec 54) (bvudiv (abs a) (abs b)))
(define-fun left () (_ BitVec 54) (bvsdiv x y))
(define-fun right () (_ BitVec 54) (ite (xor (negative x) (negative y)) (bvneg (abs_div x y)) (abs_div x y)))
(assert (distinct left right))
(check-sat)
