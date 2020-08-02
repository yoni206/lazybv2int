(set-logic UFNIA)
(declare-fun instantiate_me (Int) Bool)
(declare-fun pow2 (Int) Int)
(declare-fun intand (Int Int Int) Int)
(declare-fun intor (Int Int Int) Int)
(declare-fun intxor (Int Int Int) Int)
(define-fun bitof ((k Int) (l Int) (a Int)) Int (mod (div a (pow2 l)) 2))
(define-fun int_all_but_msb ((k Int) (a Int)) Int (mod a (pow2 (- k 1))))
(define-fun intand_helper ((a Int) (b Int)) Int (ite (and (= a 1) (= b 1) ) 1 0))
(define-fun intor_helper ((a Int) (b Int)) Int (ite (and (= a 0) (= b 0) ) 0 1))
(define-fun intxor_helper ((a Int) (b Int)) Int (ite (or (and (= a 0) (=  b 1)) (and (= a 1) (= b 0))) 1 0))
(define-fun intmax ((k Int)) Int (- (pow2 k) 1))
(define-fun intmin ((k Int)) Int 0)
(define-fun in_range ((k Int) (x Int)) Bool (and (>= x 0) (<= x (intmax k))))
(define-fun intudivtotal ((k Int) (a Int) (b Int)) Int (ite (= b 0) (- (pow2 k) 1) (div a b) ))
(define-fun intmodtotal ((k Int) (a Int) (b Int)) Int (ite (= b 0) a (mod a b)))
(define-fun intneg ((k Int) (a Int)) Int (intmodtotal k (- (pow2 k) a) (pow2 k)))
(define-fun intnot ((k Int) (a Int)) Int (- (intmax k) a))
(define-fun intmins ((k Int)) Int (pow2 (- k 1)))
(define-fun intmaxs ((k Int)) Int (intnot k (intmins k)))
(define-fun intshl ((k Int) (a Int) (b Int)) Int (intmodtotal k (* a (pow2 b)) (pow2 k)))
(define-fun intlshr ((k Int) (a Int) (b Int)) Int (intmodtotal k (intudivtotal k a (pow2 b)) (pow2 k)))
(define-fun intashr ((k Int) (a Int) (b Int) ) Int (ite (= (bitof k (- k 1) a) 0) (intlshr k a b) (intnot k (intlshr k (intnot k a) b))))
(define-fun intconcat ((k Int) (m Int) (a Int) (b Int)) Int (+ (* a (pow2 m)) b))
(define-fun intextract ( (i Int) (j Int) (x Int)) Int (mod (div x (pow2 j)) (pow2 (+ (- i j) 1)) ))
;(define-fun intzeroextend ((k Int) (x Int) (i Int)) Int x)
;(define-fun intsignextend ((k Int) (x Int) (i Int)) Int (ite (>= x (intmins k)) (intconcat i k (intnot i 0) x) (zero_extend x i)))
(define-fun intrepeatonebit ((x Int) (i Int)) Int (ite (= x 0) 0 (intmax i))) ;x is assumed to be either zero or one here!
(define-fun intadd ((k Int) (a Int) (b Int) ) Int (intmodtotal k (+ a b) (pow2 k)))
(define-fun intmul ((k Int) (a Int) (b Int)) Int (intmodtotal k (* a b) (pow2 k)))
(define-fun intsub ((k Int) (a Int) (b Int)) Int (intadd k a (intneg k b)))
(define-fun unsigned_to_signed ((k Int) (x Int)) Int (- (* 2 (int_all_but_msb k x)) x))
(define-fun intslt ((k Int) (a Int) (b Int)) Bool (< (unsigned_to_signed k a) (unsigned_to_signed k b)) )
(define-fun intsgt ((k Int) (a Int) (b Int)) Bool (> (unsigned_to_signed k a) (unsigned_to_signed k b)) )
(define-fun intsle ((k Int) (a Int) (b Int)) Bool (<= (unsigned_to_signed k a) (unsigned_to_signed k b)) )
(define-fun intsge ((k Int) (a Int) (b Int)) Bool (>= (unsigned_to_signed k a) (unsigned_to_signed k b)) )
(define-fun pow2_base_cases () Bool (and (= (pow2 0) 1) (= (pow2 1) 2) (= (pow2 2) 4) (= (pow2 3) 8) ) )
(define-fun pow2_ind_def () Bool (and (= (pow2 0) 1) (forall ((i Int)) (!(=> (> i 0) (= (pow2 i) (* (pow2 (- i 1)) 2))) :pattern ((instantiate_me i))) )))
(define-fun and_ind_def ((k Int)) Bool (forall ((a Int) (b Int)) (!(=> (and (> k 0) (in_range k a) (in_range k b)) (= (intand k a b) (+ (ite (> k 1) (intand (- k 1) (int_all_but_msb k a) (int_all_but_msb k b)) 0) (* (pow2 (- k 1)) (intand_helper (bitof k (- k 1) a) (bitof k (- k 1) b)))))) :pattern ((instantiate_me a) (instantiate_me b))) ))
(define-fun or_ind_def ((k Int)) Bool (forall ((a Int) (b Int))  (! (=> (and (> k 0) (in_range k a) (in_range k b)) (= (intor k a b) (+ (ite (> k 1) (intor (- k 1) (int_all_but_msb k a) (int_all_but_msb k b)) 0) (* (pow2 (- k 1)) (intor_helper (bitof k (- k 1) a) (bitof k (- k 1) b)))))) :pattern ((instantiate_me a) (instantiate_me b))) ))
(define-fun xor_ind_def ((k Int)) Bool (forall ((a Int) (b Int))  (! (=> (and (> k 0) (in_range k a) (in_range k b)) (= (intxor k a b) (+ (ite (> k 1) (intxor (- k 1) (int_all_but_msb k a) (int_all_but_msb k b)) 0) (* (pow2 (- k 1)) (intxor_helper (bitof k (- k 1) a) (bitof k (- k 1) b)))))) :pattern ((instantiate_me a) (instantiate_me b))) ))
;pow2 properties
(define-fun pow2_weak_monotinicity () Bool (forall ((i Int) (j Int)) (=> (and (>= i 0) (>= j 0) ) (=> (<= i j) (<= (pow2 i) (pow2 j))) )))
(define-fun pow2_strong_monotinicity () Bool (forall ((i Int) (j Int)) (=> (and (>= i 0) (>= j 0) ) (=> (< i j) (< (pow2 i) (pow2 j))) ) ) )
(define-fun pow2_modular_power () Bool (forall ((i Int) (j Int) (x Int)) (! (=> (and (>= i 0) (>= j 0) (>= x 0) (distinct (mod (* x (pow2 i)) (pow2 j)) 0)) (< i j) ) :pattern ((instantiate_me i) (instantiate_me j) (instantiate_me x))) ) )
(define-fun pow2_never_even () Bool (forall ((k Int) (x Int)) (! (=> (and (>= k 1) (>= x 0)) (distinct (- (pow2 k) 1) (* 2 x)) ) :pattern ((instantiate_me k) (instantiate_me x))) ) )
(define-fun pow2_always_positive () Bool (forall ((k Int)) (! (=> (>= k 0) (>= (pow2 k) 1) ) :pattern ((instantiate_me k))) ) )
(define-fun pow2_div_zero () Bool (forall ((k Int)) (! (=> (>= k 0) (= (div k (pow2 k)) 0 ) ) :pattern ((instantiate_me k))) ) )
(define-fun pow2_properties () Bool (and pow2_base_cases pow2_weak_monotinicity pow2_strong_monotinicity pow2_modular_power pow2_never_even pow2_always_positive pow2_div_zero ) )
;and properties
(define-fun and_max1 ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a)) (= (intand k a (intmax k)) a)) :pattern ((instantiate_me a))) ))
(define-fun and_max2 ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a)) (= (intand k 0 a) 0   )) :pattern ((instantiate_me a))) ))
(define-fun and_ide ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a)) (= (intand k a a) a)) :pattern ((instantiate_me a))) ))
(define-fun rule_of_contradiction ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a))  (= (intand k (intnot k a) a) 0 )) :pattern ((instantiate_me a))) ))
(define-fun and_sym ((k Int)) Bool (forall ((a Int) (b Int)) (! (=> (and (> k 0) (in_range k a) (in_range k b)) (= (intand k a b) (intand k b a))) :pattern ((instantiate_me a) (instantiate_me b)))))
(define-fun and_difference1 ((k Int)) Bool (forall ((a Int) (b Int) (c Int)) (! (=> (and (distinct a b) (> k 0) (in_range k a) (in_range k b) (in_range k c) ) (or (distinct (intand k a c) b) (distinct (intand k b c) a))) :pattern ((instantiate_me a) (instantiate_me b) (instantiate_me c))) ))
(define-fun and_ranges ((k Int)) Bool (forall ((a Int) (b Int)) (!(=> (and (> k 0) (in_range k a ) (in_range k b ) ) (and (in_range k (intand k a b)) (<= (intand k a b) a) (<= (intand k a b) b) ) ) :pattern ((instantiate_me a) (instantiate_me b) )) ))
(define-fun and_properties ((k Int)) Bool (and (and_max1 k) (and_max2 k) (and_ide k) (rule_of_contradiction k) (and_sym k) (and_difference1 k) (and_ranges k) ))
;or properties
(define-fun or_max1 ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a)) (= (intor k a (intmax k)) (intmax k))) :pattern ((instantiate_me a))) ))
(define-fun or_max2 ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a)) (= (intor k a 0) a)) :pattern ((instantiate_me a)) )))
(define-fun or_ide ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a)) (= (intor k a a) a)) :pattern ((instantiate_me a))) ))
(define-fun excluded_middle ((k Int)) Bool (forall ((a Int)) (!(=> (and (> k 0) (in_range k a)) (and (= (intor k (intnot k a) a) (intmax k)) (= (intor k a (intnot k a)) (intmax k))  )) :pattern ((instantiate_me a)) )))
(define-fun or_difference1 ((k Int)) Bool (forall ((a Int) (b Int) (c Int)) (! (=> (and (distinct a b) (> k 0) (in_range k a) (in_range k b) (in_range k c) ) (or (distinct (intor k a c) b) (distinct (intor k b c) a))) :pattern ((instantiate_me a) (instantiate_me b) (instantiate_me c))) ))
(define-fun or_sym ((k Int)) Bool (forall ((a Int) (b Int)) (! (=> (and (> k 0) (in_range k a) (in_range k b)) (= (intor k a b) (intor k b a))) :pattern ((instantiate_me a) (instantiate_me b)))))
(define-fun or_ranges ((k Int)) Bool (forall ((a Int) (b Int)) (!(=> (and (> k 0) (in_range k a) (in_range k b) ) (and (in_range k (intor k a b)) (>= (intor k a b) a) (>= (intor k a b) b) ) ) :pattern ((instantiate_me a) (instantiate_me b))) ))
(define-fun or_properties ((k Int)) Bool (and (or_max1 k) (or_max2 k) (or_ide k) (excluded_middle k) (or_sym k) (or_difference1 k) (or_ranges k) ))
;xor properties
(define-fun xor_ide ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a) ) (= (intxor k a a) 0)) :pattern ((instantiate_me a))) ))
(define-fun xor_flip ((k Int)) Bool (forall ((a Int)) (! (=> (and (> k 0) (in_range k a)) (= (intxor k a (intnot k a)) (intmax k))) :pattern ((instantiate_me a))) ))
(define-fun xor_sym ((k Int)) Bool (forall ((a Int) (b Int)) (! (=> (and (> k 0) (in_range k a) (in_range k b)) (= (intxor k a b) (intxor k b a))) :pattern ((instantiate_me a) (instantiate_me b)))))
(define-fun xor_ranges ((k Int)) Bool (forall ((a Int) (b Int)) (!(=> (and (> k 0) (in_range k a) (in_range k b) ) (in_range k (intxor k a b)) ) :pattern ((instantiate_me a) (instantiate_me b))) ))
(define-fun xor_properties ((k Int)) Bool (and (xor_ide k) (xor_flip k) (xor_sym k) (xor_ranges k) ))
;combined axioms
(define-fun pow2_ax () Bool (and pow2_ind_def pow2_properties))
(define-fun and_ax ((k Int)) Bool (and (and_ind_def k) (and_properties k)))
(define-fun or_ax ((k Int)) Bool (and (or_ind_def k) (or_properties k)))
(define-fun xor_ax ((k Int)) Bool (and (xor_ind_def k) (xor_properties k)))

; bitwidth
(declare-fun k () Int)

;variables
(declare-fun x () Int)
(declare-fun y () Int)


;two sides of rewrite
(define-fun left () Int (intxor k x y))
(define-fun right () Int (intsub k (intor k x y) (intand k x y) ))

;bitwidth is positive
(assert (> k 0))

;variables are in range
(assert (in_range k x ))
(assert (in_range k y ))

;operations are correct
(assert pow2_properties)
(assert (or_properties k))
(assert (and_properties k))
(assert (xor_properties k))

;rewrite is wrong
(assert (distinct left right))

;templates
(assert (instantiate_me x))
(assert (instantiate_me y))

(check-sat)