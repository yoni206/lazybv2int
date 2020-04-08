#include "bw_functions.h"
#include <math.h>
#include "theory/bv/theory_bv_utils.h"
using namespace CVC4::kind;
using namespace CVC4;
// (define-fun int_bvand_1_lia ((s Int) (t Int)) Int (ite (= 0 s) 0 t))
Node int_bvand_1_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_3 = nm->mkNode(EQUAL, const_rational_0, s);
  Node ite_1 = nm->mkNode(ITE, equal_3, const_rational_0, t);
  return ite_1;
}

// (define-fun int_bvand_1_nia ((s Int) (t Int)) Int (ite (= 0 s) 0 t))
Node int_bvand_1_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_3 = nm->mkNode(EQUAL, const_rational_0, s);
  Node ite_1 = nm->mkNode(ITE, equal_3, const_rational_0, t);
  return ite_1;
}

// (define-fun int_bvand_2_lia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (* s t) (ite (= t 2) 0 (* s s))) (ite (>= s (* s t)) (ite (= 0 (*
// s t)) (* s t) (ite (= s 2) 0 (* t t))) (ite (>= t s) s t))))
Node int_bvand_2_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_16 = nm->mkNode(MULT, s, s);
  Node equal_18 = nm->mkNode(EQUAL, s, mult_16);
  Node mult_11 = nm->mkNode(MULT, s, t);
  Node geq_13 = nm->mkNode(GEQ, s, mult_11);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_17 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node ite_15 = nm->mkNode(ITE, equal_17, const_rational_0, mult_16);
  Node ite_14 = nm->mkNode(ITE, geq_13, mult_11, ite_15);
  Node equal_12 = nm->mkNode(EQUAL, const_rational_0, mult_11);
  Node equal_9 = nm->mkNode(EQUAL, s, const_rational_2);
  Node mult_7 = nm->mkNode(MULT, t, t);
  Node ite_6 = nm->mkNode(ITE, equal_9, const_rational_0, mult_7);
  Node ite_5 = nm->mkNode(ITE, equal_12, mult_11, ite_6);
  Node geq_4 = nm->mkNode(GEQ, t, s);
  Node ite_3 = nm->mkNode(ITE, geq_4, s, t);
  Node ite_2 = nm->mkNode(ITE, geq_13, ite_5, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_18, ite_14, ite_2);
  return ite_1;
}

// (define-fun int_bvand_2_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= 0 s)
// (* s t) (ite (>= s t) (ite (= 0 s) 0 s) (ite (= t 2) 0 (ite (= s 1) (* s s)
// s)))) (ite (= 0 t) (* s t) (ite (= s 3) (ite (= t 1) (* t t) t) 0))))
Node int_bvand_2_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_24 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_22 = nm->mkNode(EQUAL, const_rational_0, s);
  Node mult_11 = nm->mkNode(MULT, s, t);
  Node geq_23 = nm->mkNode(GEQ, s, t);
  Node ite_21 = nm->mkNode(ITE, equal_22, const_rational_0, s);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_19 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_17 = nm->mkNode(MULT, s, s);
  Node ite_16 = nm->mkNode(ITE, equal_18, mult_17, s);
  Node ite_15 = nm->mkNode(ITE, equal_19, const_rational_0, ite_16);
  Node ite_14 = nm->mkNode(ITE, geq_23, ite_21, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_22, mult_11, ite_14);
  Node equal_12 = nm->mkNode(EQUAL, const_rational_0, t);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_9 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_7 = nm->mkNode(EQUAL, t, const_rational_1);
  Node mult_6 = nm->mkNode(MULT, t, t);
  Node ite_5 = nm->mkNode(ITE, equal_7, mult_6, t);
  Node ite_3 = nm->mkNode(ITE, equal_9, ite_5, const_rational_0);
  Node ite_2 = nm->mkNode(ITE, equal_12, mult_11, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_24, ite_13, ite_2);
  return ite_1;
}

// (define-fun int_bvand_3_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (* s t) (ite (>= s t) s (ite (= t 2) 0 (ite (= t 3) (ite (= s 1) (* s s) s)
// (ite (= t 4) (ite (= s 1) 0 (ite (= s 2) 0 0)) (ite (= t 5) (ite (= s 1) (* s
// s) (ite (= s 2) 0 (ite (= s 3) 1 s))) (ite (= t 6) (ite (= s 1) 0 (ite (= s
// 2) s (ite (= s 3) 2 (ite (= s 5) 4 s)))) (ite (= s 1) (* s s) (ite (= s 2) s
// (ite (= s 6) s (ite (= s 3) s (ite (= s 4) s s)))))))))))) (ite (= t 0) (* s
// t) (ite (= t 1) (ite (= s 2) 0 (ite (= s 3) (* t t) (ite (= s 4) 0 (ite (= s
// 5) (* t t) (ite (= s 6) 0 (* t t)))))) (ite (= t 2) (ite (= s 3) t (ite (= s
// 4) 0 (ite (= s 5) 0 (ite (= s 6) t (ite (>= t s) s t))))) (ite (= t 3) (ite
// (= s 4) 0 (ite (= s 5) 1 (ite (= s 6) 2 (ite (>= t s) s t)))) (ite (= t 4)
// (ite (= s 5) t (ite (= s 6) t (ite (>= t s) s t))) (ite (= t 5) (ite (= s 6)
// 4 (ite (>= t s) s t)) (ite (>= t s) s t)))))))))
Node int_bvand_3_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_9 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_70 = nm->mkNode(EQUAL, s, const_rational_0);
  Node mult_42 = nm->mkNode(MULT, s, t);
  Node geq_69 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_33 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_27 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_56 = nm->mkNode(MULT, s, s);
  Node ite_68 = nm->mkNode(ITE, equal_57, mult_56, s);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_19 = nm->mkNode(EQUAL, t, const_rational_4);
  Node equal_40 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_67 = nm->mkNode(ITE, equal_40, const_rational_0, const_rational_0);
  Node ite_66 = nm->mkNode(ITE, equal_57, const_rational_0, ite_67);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_14 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_32 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_65 = nm->mkNode(ITE, equal_32, const_rational_1, s);
  Node ite_64 = nm->mkNode(ITE, equal_40, const_rational_0, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_57, mult_56, ite_64);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_62 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_61 = nm->mkNode(ITE, equal_18, const_rational_4, s);
  Node ite_60 = nm->mkNode(ITE, equal_32, const_rational_2, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_40, s, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_57, const_rational_0, ite_59);
  Node equal_12 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_55 = nm->mkNode(ITE, equal_26, s, s);
  Node ite_54 = nm->mkNode(ITE, equal_32, s, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_12, s, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_40, s, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_57, mult_56, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_62, ite_58, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_14, ite_63, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_19, ite_66, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_27, ite_68, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_33, const_rational_0, ite_47);
  Node ite_45 = nm->mkNode(ITE, geq_69, s, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_70, mult_42, ite_45);
  Node equal_43 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_41 = nm->mkNode(EQUAL, t, const_rational_1);
  Node mult_39 = nm->mkNode(MULT, t, t);
  Node ite_38 = nm->mkNode(ITE, equal_12, const_rational_0, mult_39);
  Node ite_37 = nm->mkNode(ITE, equal_18, mult_39, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_26, const_rational_0, ite_37);
  Node ite_35 = nm->mkNode(ITE, equal_32, mult_39, ite_36);
  Node ite_34 = nm->mkNode(ITE, equal_40, const_rational_0, ite_35);
  Node ite_8 = nm->mkNode(ITE, geq_9, s, t);
  Node ite_17 = nm->mkNode(ITE, equal_12, t, ite_8);
  Node ite_31 = nm->mkNode(ITE, equal_18, const_rational_0, ite_17);
  Node ite_30 = nm->mkNode(ITE, equal_26, const_rational_0, ite_31);
  Node ite_29 = nm->mkNode(ITE, equal_32, t, ite_30);
  Node ite_22 = nm->mkNode(ITE, equal_12, const_rational_2, ite_8);
  Node ite_21 = nm->mkNode(ITE, equal_18, const_rational_1, ite_22);
  Node ite_20 = nm->mkNode(ITE, equal_26, const_rational_0, ite_21);
  Node ite_16 = nm->mkNode(ITE, equal_18, t, ite_17);
  Node ite_10 = nm->mkNode(ITE, equal_12, const_rational_4, ite_8);
  Node ite_7 = nm->mkNode(ITE, equal_14, ite_10, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_19, ite_16, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_27, ite_20, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_33, ite_29, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_41, ite_34, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_43, mult_42, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_9, ite_44, ite_2);
  return ite_1;
}

// (define-fun int_bvand_3_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 7)
// s (ite (= s 0) (* s t) (ite (>= s t) s (ite (= s 6) s (ite (= t 2) 0 (ite (=
// t 3) (ite (= s 1) (* s s) s) (ite (= t 4) (ite (= s 1) 0 (ite (= s 3) 0 0))
// (ite (= t 5) (ite (= s 1) (* s s) (ite (= s 2) 0 (ite (= s 3) 1 s))) (ite (=
// t 6) (ite (= s 1) 0 (ite (= s 2) s (ite (= s 3) 2 (ite (= s 4) s 4)))) (ite
// (= s 1) (* s s) (ite (= s 5) s (ite (= s 2) s (ite (= s 3) s s)))))))))))))
// (ite (= t 0) (* s t) (ite (= t 1) (ite (= s 2) 0 (ite (= s 3) (* t t) (ite (=
// s 4) 0 (ite (= s 5) (* t t) (ite (= s 7) (* t t) 0))))) (ite (= t 2) (ite (=
// s 3) t (ite (= s 4) 0 (ite (= s 5) 0 (ite (= s 6) t t)))) (ite (= t 3) (ite
// (= s 4) 0 (ite (= s 5) 1 (ite (= s 6) 2 t))) (ite (= t 4) (ite (= s 5) t (ite
// (= s 6) t t)) (ite (= t 5) (ite (= s 6) 4 t) t))))))))
Node int_bvand_3_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_72 = nm->mkNode(GEQ, t, s);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_38 = nm->mkNode(EQUAL, s, const_rational_7);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_71 = nm->mkNode(EQUAL, s, const_rational_0);
  Node mult_42 = nm->mkNode(MULT, s, t);
  Node geq_70 = nm->mkNode(GEQ, s, t);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_10 = nm->mkNode(EQUAL, s, const_rational_6);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_31 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_25 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_58 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_57 = nm->mkNode(MULT, s, s);
  Node ite_69 = nm->mkNode(ITE, equal_58, mult_57, s);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_17 = nm->mkNode(EQUAL, t, const_rational_4);
  Node equal_30 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_68 = nm->mkNode(ITE, equal_30, const_rational_0, const_rational_0);
  Node ite_67 = nm->mkNode(ITE, equal_58, const_rational_0, ite_68);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_12 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_40 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_66 = nm->mkNode(ITE, equal_30, const_rational_1, s);
  Node ite_65 = nm->mkNode(ITE, equal_40, const_rational_0, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_58, mult_57, ite_65);
  Node equal_63 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_24 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_62 = nm->mkNode(ITE, equal_24, s, const_rational_4);
  Node ite_61 = nm->mkNode(ITE, equal_30, const_rational_2, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_40, s, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_58, const_rational_0, ite_60);
  Node equal_16 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_56 = nm->mkNode(ITE, equal_30, s, s);
  Node ite_55 = nm->mkNode(ITE, equal_40, s, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_16, s, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_58, mult_57, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_63, ite_59, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_12, ite_64, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_17, ite_67, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_25, ite_69, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_31, const_rational_0, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_10, s, ite_48);
  Node ite_46 = nm->mkNode(ITE, geq_70, s, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_71, mult_42, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_38, s, ite_45);
  Node equal_43 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_41 = nm->mkNode(EQUAL, t, const_rational_1);
  Node mult_37 = nm->mkNode(MULT, t, t);
  Node ite_36 = nm->mkNode(ITE, equal_38, mult_37, const_rational_0);
  Node ite_35 = nm->mkNode(ITE, equal_16, mult_37, ite_36);
  Node ite_34 = nm->mkNode(ITE, equal_24, const_rational_0, ite_35);
  Node ite_33 = nm->mkNode(ITE, equal_30, mult_37, ite_34);
  Node ite_32 = nm->mkNode(ITE, equal_40, const_rational_0, ite_33);
  Node ite_15 = nm->mkNode(ITE, equal_10, t, t);
  Node ite_29 = nm->mkNode(ITE, equal_16, const_rational_0, ite_15);
  Node ite_28 = nm->mkNode(ITE, equal_24, const_rational_0, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_30, t, ite_28);
  Node ite_20 = nm->mkNode(ITE, equal_10, const_rational_2, t);
  Node ite_19 = nm->mkNode(ITE, equal_16, const_rational_1, ite_20);
  Node ite_18 = nm->mkNode(ITE, equal_24, const_rational_0, ite_19);
  Node ite_14 = nm->mkNode(ITE, equal_16, t, ite_15);
  Node ite_8 = nm->mkNode(ITE, equal_10, const_rational_4, t);
  Node ite_7 = nm->mkNode(ITE, equal_12, ite_8, t);
  Node ite_6 = nm->mkNode(ITE, equal_17, ite_14, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_25, ite_18, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_31, ite_27, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_41, ite_32, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_43, mult_42, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_72, ite_44, ite_2);
  return ite_1;
}

// (define-fun int_bvand_4_lia ((s Int) (t Int)) Int (ite (>= 3 s) (ite (not (=
// s 3)) (ite (>= t (* s t)) (ite (not (= s 2)) (ite (>= s (* s t)) (* s t) (ite
// (>= 3 t) (ite (>= 2 t) 0 (* s s)) (ite (= t 4) 0 (ite (= t 5) (* s s) (ite (=
// t 6) 0 (ite (= t 7) (* s s) (ite (= t 8) 0 (ite (= t 9) (* s s) (ite (= t 10)
// 0 (ite (= t 11) (* s s) (ite (= t 12) 0 (ite (= t 13) (* s s) (ite (= t 14) 0
// (* s s)))))))))))))) (* s t)) (ite (>= s (* s t)) 0 (ite (>= t (* s s)) (ite
// (= t 14) s (ite (>= (* s s) t) 0 (ite (= t 5) 0 (ite (= t 6) s (ite (= t 7) s
// (ite (= t 8) 0 (ite (= t 9) 0 (ite (= t 10) s (ite (= t 11) s (ite (= t 12) 0
// (ite (= t 13) 0 s))))))))))) (ite (not (= t 3)) (ite (= 0 t) (* s t) s) s))))
// (ite (>= t (* s t)) (* s t) (ite (>= s (* s t)) (* t t) (ite (>= t s) (ite
// (>= t (* s s)) (ite (>= (* s s) t) 1 (ite (= t 10) 2 (ite (= t 11) s (ite (=
// t 12) 0 (ite (= t 14) 2 (ite (= t 13) 1 s)))))) (ite (>= 3 t) (ite (= 0 t) (*
// s t) s) (ite (= t 4) 0 (ite (= t 5) 1 (ite (= t 6) 2 (ite (= t 7) s 0))))))
// t)))) (ite (>= t (* s t)) (* s t) (ite (>= s (* s t)) (ite (= s 4) 0 (ite (=
// s 5) (* t t) (ite (= s 6) 0 (ite (= s 7) (* t t) (ite (= s 8) 0 (ite (= s 9)
// (* t t) (ite (= s 10) 0 (ite (= s 11) (* t t) (ite (= s 12) 0 (ite (= s 13)
// (* t t) (ite (= s 15) (* t t) 0))))))))))) (ite (>= (* t t) s) (ite (>= t s)
// (ite (>= s t) (ite (= 0 t) (* s t) s) (ite (= t 5) s (ite (= t 6) (ite (= s
// 4) s 4) (ite (= t 7) (ite (= s 6) s (ite (= s 5) s s)) (ite (= t 8) (ite (= s
// 7) 0 (ite (= s 4) 0 (ite (= s 6) 0 0))) (ite (= t 9) (ite (= s 4) 0 (ite (= s
// 5) 1 (ite (= s 8) s (ite (= s 6) 0 1)))) (ite (= t 10) (ite (= s 4) 0 (ite (=
// s 5) 0 (ite (= s 6) 2 (ite (= s 7) 2 (ite (= s 8) s 8))))) (ite (= t 11) (ite
// (= s 4) 0 (ite (= s 5) 1 (ite (= s 10) s (ite (= s 6) 2 (ite (= s 7) 3 (ite
// (= s 8) s s)))))) (ite (= s 14) s (ite (= t 12) (ite (= s 4) s (ite (= s 5) 4
// (ite (= s 6) 4 (ite (= s 7) 4 (ite (= s 8) s (ite (= s 9) 8 (ite (= s 10) 8
// 8))))))) (ite (= t 13) (ite (= s 4) s (ite (= s 5) s (ite (= s 6) 4 (ite (= s
// 7) 5 (ite (= s 8) s (ite (= s 9) s (ite (= s 10) 8 (ite (= s 11) 9 s))))))))
// (ite (= t 14) (ite (= s 13) 12 (ite (= s 4) s (ite (= s 5) 4 (ite (= s 6) s
// (ite (= s 7) 6 (ite (= s 8) s (ite (= s 9) 8 (ite (= s 10) s (ite (= s 11) 10
// s))))))))) (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 7) s (ite
// (= s 8) s (ite (= s 9) s (ite (= s 10) s (ite (= s 11) s (ite (= s 12) s
// s))))))))))))))))))))) (ite (>= 3 t) (ite (not (= t 3)) 0 (ite (>= s (* t t))
// 1 (ite (>= s (* t 2)) (ite (= s (* t 2)) 2 (ite (= s 7) t 0)) (ite (= s 4) 0
// 1)))) (ite (>= s (* t 2)) (ite (>= s (* t 3)) (ite (= s (* t 3)) (ite (= t 4)
// t t) (ite (= s 13) t (ite (= s 15) t t))) (ite (= s (* t 2)) (ite (= t 4) 0
// (ite (= s 14) 6 (ite (= t 5) 0 4))) (ite (= t 4) (ite (= s 9) 0 (ite (= s 10)
// 0 0)) (ite (= t 5) (ite (= s 14) 4 (ite (= s 11) 1 (ite (= s 12) 4 t))) (ite
// (= t 6) (ite (= s 13) 4 (ite (= s 14) t t)) t))))) (ite (= t 4) (ite (= s 5)
// t (ite (= s 6) t t)) (ite (= t 5) (ite (= s 6) 4 (ite (= s 7) t (ite (= s 8)
// 0 1))) (ite (= t 6) (ite (= s 7) t (ite (= s 8) 0 (ite (= s 9) 0 (ite (= s
// 10) 2 2)))) (ite (= t 7) (ite (= s 8) 0 (ite (= s 9) 1 (ite (= s 10) 2 (ite
// (= s 11) 3 (ite (= s 12) 4 5))))) (ite (= t 8) (ite (= s 9) t (ite (= s 10) t
// (ite (= s 11) t (ite (= s 12) t (ite (= s 13) t (ite (= s 14) t t)))))) (ite
// (= t 9) (ite (= s 10) 8 (ite (= s 11) t (ite (= s 12) 8 (ite (= s 13) t (ite
// (= s 14) 8 t))))) (ite (= t 10) (ite (= s 11) t (ite (= s 12) 8 (ite (= s 13)
// 8 (ite (= s 14) t t)))) (ite (= t 11) (ite (= s 12) 8 (ite (= s 13) 9 (ite (=
// s 14) 10 t))) (ite (= t 12) (ite (= s 13) t (ite (= s 15) t t)) (ite (= t 13)
// (ite (= s 15) t 12) t))))))))))))) (ite (not (= t 3)) (ite (>= s (* t (* t
// t))) (ite (= s (* t (* t t))) 0 (ite (= s 9) 0 (ite (= s 10) t (ite (= s 11)
// t (ite (= s 12) 0 (ite (= s 13) 0 (ite (= s 15) t t))))))) (ite (>= s (* t
// 3)) (ite (= s (* t 3)) t t) 0)) (ite (= s 10) 2 (ite (= s 11) t (ite (= s 12)
// 0 (ite (= s 13) 1 (ite (= s 14) 2 t)))))))))))
Node int_bvand_4_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node geq_281 = nm->mkNode(GEQ, const_rational_3, s);
  Node equal_280 = nm->mkNode(EQUAL, s, const_rational_3);
  Node not_279 = nm->mkNode(NOT, equal_280);
  Node mult_209 = nm->mkNode(MULT, s, t);
  Node geq_226 = nm->mkNode(GEQ, t, mult_209);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_278 = nm->mkNode(EQUAL, s, const_rational_2);
  Node not_277 = nm->mkNode(NOT, equal_278);
  Node geq_225 = nm->mkNode(GEQ, s, mult_209);
  Node geq_140 = nm->mkNode(GEQ, const_rational_3, t);
  Node geq_276 = nm->mkNode(GEQ, const_rational_2, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node mult_244 = nm->mkNode(MULT, s, s);
  Node ite_275 = nm->mkNode(ITE, geq_276, const_rational_0, mult_244);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_112 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_108 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_102 = nm->mkNode(EQUAL, t, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_95 = nm->mkNode(EQUAL, t, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_86 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_80 = nm->mkNode(EQUAL, t, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_69 = nm->mkNode(EQUAL, t, const_rational_11);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_64 = nm->mkNode(EQUAL, t, const_rational_12);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_62 = nm->mkNode(EQUAL, t, const_rational_13);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_171 = nm->mkNode(EQUAL, t, const_rational_14);
  Node ite_274 = nm->mkNode(ITE, equal_171, const_rational_0, mult_244);
  Node ite_273 = nm->mkNode(ITE, equal_62, mult_244, ite_274);
  Node ite_272 = nm->mkNode(ITE, equal_64, const_rational_0, ite_273);
  Node ite_271 = nm->mkNode(ITE, equal_69, mult_244, ite_272);
  Node ite_270 = nm->mkNode(ITE, equal_74, const_rational_0, ite_271);
  Node ite_269 = nm->mkNode(ITE, equal_80, mult_244, ite_270);
  Node ite_268 = nm->mkNode(ITE, equal_86, const_rational_0, ite_269);
  Node ite_267 = nm->mkNode(ITE, equal_95, mult_244, ite_268);
  Node ite_266 = nm->mkNode(ITE, equal_102, const_rational_0, ite_267);
  Node ite_265 = nm->mkNode(ITE, equal_108, mult_244, ite_266);
  Node ite_264 = nm->mkNode(ITE, equal_112, const_rational_0, ite_265);
  Node ite_263 = nm->mkNode(ITE, geq_140, ite_275, ite_264);
  Node ite_262 = nm->mkNode(ITE, geq_225, mult_209, ite_263);
  Node ite_261 = nm->mkNode(ITE, not_277, ite_262, mult_209);
  Node geq_245 = nm->mkNode(GEQ, t, mult_244);
  Node geq_243 = nm->mkNode(GEQ, mult_244, t);
  Node ite_260 = nm->mkNode(ITE, equal_62, const_rational_0, s);
  Node ite_259 = nm->mkNode(ITE, equal_64, const_rational_0, ite_260);
  Node ite_258 = nm->mkNode(ITE, equal_69, s, ite_259);
  Node ite_257 = nm->mkNode(ITE, equal_74, s, ite_258);
  Node ite_256 = nm->mkNode(ITE, equal_80, const_rational_0, ite_257);
  Node ite_255 = nm->mkNode(ITE, equal_86, const_rational_0, ite_256);
  Node ite_254 = nm->mkNode(ITE, equal_95, s, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_102, s, ite_254);
  Node ite_252 = nm->mkNode(ITE, equal_108, const_rational_0, ite_253);
  Node ite_251 = nm->mkNode(ITE, geq_243, const_rational_0, ite_252);
  Node ite_250 = nm->mkNode(ITE, equal_171, s, ite_251);
  Node equal_47 = nm->mkNode(EQUAL, t, const_rational_3);
  Node not_46 = nm->mkNode(NOT, equal_47);
  Node equal_210 = nm->mkNode(EQUAL, const_rational_0, t);
  Node ite_208 = nm->mkNode(ITE, equal_210, mult_209, s);
  Node ite_249 = nm->mkNode(ITE, not_46, ite_208, s);
  Node ite_248 = nm->mkNode(ITE, geq_245, ite_250, ite_249);
  Node ite_247 = nm->mkNode(ITE, geq_225, const_rational_0, ite_248);
  Node ite_246 = nm->mkNode(ITE, geq_226, ite_261, ite_247);
  Node mult_44 = nm->mkNode(MULT, t, t);
  Node geq_212 = nm->mkNode(GEQ, t, s);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_242 = nm->mkNode(ITE, equal_62, const_rational_1, s);
  Node ite_241 = nm->mkNode(ITE, equal_171, const_rational_2, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_64, const_rational_0, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_69, s, ite_240);
  Node ite_238 = nm->mkNode(ITE, equal_74, const_rational_2, ite_239);
  Node ite_237 = nm->mkNode(ITE, geq_243, const_rational_1, ite_238);
  Node ite_236 = nm->mkNode(ITE, equal_95, s, const_rational_0);
  Node ite_235 = nm->mkNode(ITE, equal_102, const_rational_2, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_108, const_rational_1, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_112, const_rational_0, ite_234);
  Node ite_232 = nm->mkNode(ITE, geq_140, ite_208, ite_233);
  Node ite_231 = nm->mkNode(ITE, geq_245, ite_237, ite_232);
  Node ite_230 = nm->mkNode(ITE, geq_212, ite_231, t);
  Node ite_229 = nm->mkNode(ITE, geq_225, mult_44, ite_230);
  Node ite_228 = nm->mkNode(ITE, geq_226, mult_209, ite_229);
  Node ite_227 = nm->mkNode(ITE, not_279, ite_246, ite_228);
  Node equal_136 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_111 = nm->mkNode(EQUAL, s, const_rational_5);
  Node equal_107 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_101 = nm->mkNode(EQUAL, s, const_rational_7);
  Node equal_94 = nm->mkNode(EQUAL, s, const_rational_8);
  Node equal_40 = nm->mkNode(EQUAL, s, const_rational_9);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_10);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_11);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_12);
  Node equal_15 = nm->mkNode(EQUAL, s, const_rational_13);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_38 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_224 = nm->mkNode(ITE, equal_38, mult_44, const_rational_0);
  Node ite_223 = nm->mkNode(ITE, equal_15, mult_44, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_18, const_rational_0, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_20, mult_44, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_22, const_rational_0, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_40, mult_44, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_94, const_rational_0, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_101, mult_44, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_107, const_rational_0, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_111, mult_44, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_136, const_rational_0, ite_215);
  Node geq_213 = nm->mkNode(GEQ, mult_44, s);
  Node geq_211 = nm->mkNode(GEQ, s, t);
  Node ite_207 = nm->mkNode(ITE, equal_136, s, const_rational_4);
  Node ite_206 = nm->mkNode(ITE, equal_111, s, s);
  Node ite_205 = nm->mkNode(ITE, equal_107, s, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_107, const_rational_0, const_rational_0);
  Node ite_203 = nm->mkNode(ITE, equal_136, const_rational_0, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_101, const_rational_0, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_107, const_rational_0, const_rational_1);
  Node ite_200 = nm->mkNode(ITE, equal_94, s, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_111, const_rational_1, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_136, const_rational_0, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_94, s, const_rational_8);
  Node ite_196 = nm->mkNode(ITE, equal_101, const_rational_2, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_107, const_rational_2, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_111, const_rational_0, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_136, const_rational_0, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_94, s, s);
  Node ite_191 = nm->mkNode(ITE, equal_101, const_rational_3, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_107, const_rational_2, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_22, s, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_111, const_rational_1, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_136, const_rational_0, ite_188);
  Node equal_12 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_186 = nm->mkNode(ITE, equal_22, const_rational_8, const_rational_8);
  Node ite_185 = nm->mkNode(ITE, equal_40, const_rational_8, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_94, s, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_101, const_rational_4, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_107, const_rational_4, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_111, const_rational_4, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_136, s, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_20, const_rational_9, s);
  Node ite_178 = nm->mkNode(ITE, equal_22, const_rational_8, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_40, s, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_94, s, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_101, const_rational_5, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_107, const_rational_4, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_111, s, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_136, s, ite_173);
  Node ite_170 = nm->mkNode(ITE, equal_20, const_rational_10, s);
  Node ite_169 = nm->mkNode(ITE, equal_22, s, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_40, const_rational_8, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_94, s, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_101, const_rational_6, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_107, s, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_111, const_rational_4, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_136, s, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_15, const_rational_12, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_18, s, s);
  Node ite_160 = nm->mkNode(ITE, equal_20, s, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_22, s, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_40, s, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_94, s, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_101, s, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_107, s, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_111, s, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_136, s, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_171, ite_162, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_62, ite_172, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_64, ite_180, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_12, s, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_69, ite_187, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_74, ite_193, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_80, ite_198, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_86, ite_202, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_95, ite_205, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_102, ite_207, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_108, s, ite_143);
  Node ite_141 = nm->mkNode(ITE, geq_211, ite_208, ite_142);
  Node geq_139 = nm->mkNode(GEQ, s, mult_44);
  Node mult_128 = nm->mkNode(MULT, t, const_rational_2);
  Node geq_131 = nm->mkNode(GEQ, s, mult_128);
  Node equal_127 = nm->mkNode(EQUAL, s, mult_128);
  Node ite_138 = nm->mkNode(ITE, equal_101, t, const_rational_0);
  Node ite_137 = nm->mkNode(ITE, equal_127, const_rational_2, ite_138);
  Node ite_135 = nm->mkNode(ITE, equal_136, const_rational_0, const_rational_1);
  Node ite_134 = nm->mkNode(ITE, geq_131, ite_137, ite_135);
  Node ite_133 = nm->mkNode(ITE, geq_139, const_rational_1, ite_134);
  Node ite_132 = nm->mkNode(ITE, not_46, const_rational_0, ite_133);
  Node mult_28 = nm->mkNode(MULT, t, const_rational_3);
  Node geq_30 = nm->mkNode(GEQ, s, mult_28);
  Node equal_27 = nm->mkNode(EQUAL, s, mult_28);
  Node ite_130 = nm->mkNode(ITE, equal_112, t, t);
  Node ite_37 = nm->mkNode(ITE, equal_38, t, t);
  Node ite_63 = nm->mkNode(ITE, equal_15, t, ite_37);
  Node ite_129 = nm->mkNode(ITE, equal_27, ite_130, ite_63);
  Node ite_126 = nm->mkNode(ITE, equal_108, const_rational_0, const_rational_4);
  Node ite_125 = nm->mkNode(ITE, equal_12, const_rational_6, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_112, const_rational_0, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_22, const_rational_0, const_rational_0);
  Node ite_122 = nm->mkNode(ITE, equal_40, const_rational_0, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_18, const_rational_4, t);
  Node ite_120 = nm->mkNode(ITE, equal_20, const_rational_1, ite_121);
  Node ite_119 = nm->mkNode(ITE, equal_12, const_rational_4, ite_120);
  Node ite_73 = nm->mkNode(ITE, equal_12, t, t);
  Node ite_118 = nm->mkNode(ITE, equal_15, const_rational_4, ite_73);
  Node ite_117 = nm->mkNode(ITE, equal_102, ite_118, t);
  Node ite_116 = nm->mkNode(ITE, equal_108, ite_119, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_112, ite_122, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_127, ite_124, ite_115);
  Node ite_113 = nm->mkNode(ITE, geq_30, ite_129, ite_114);
  Node ite_110 = nm->mkNode(ITE, equal_107, t, t);
  Node ite_109 = nm->mkNode(ITE, equal_111, t, ite_110);
  Node ite_106 = nm->mkNode(ITE, equal_94, const_rational_0, const_rational_1);
  Node ite_105 = nm->mkNode(ITE, equal_101, t, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_107, const_rational_4, ite_105);
  Node ite_100 = nm->mkNode(ITE, equal_22, const_rational_2, const_rational_2);
  Node ite_99 = nm->mkNode(ITE, equal_40, const_rational_0, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_94, const_rational_0, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_101, t, ite_98);
  Node ite_91 = nm->mkNode(ITE, equal_18, const_rational_4, const_rational_5);
  Node ite_90 = nm->mkNode(ITE, equal_20, const_rational_3, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_22, const_rational_2, ite_90);
  Node ite_88 = nm->mkNode(ITE, equal_40, const_rational_1, ite_89);
  Node ite_87 = nm->mkNode(ITE, equal_94, const_rational_0, ite_88);
  Node ite_85 = nm->mkNode(ITE, equal_15, t, ite_73);
  Node ite_84 = nm->mkNode(ITE, equal_18, t, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_20, t, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_22, t, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_40, t, ite_82);
  Node ite_79 = nm->mkNode(ITE, equal_12, const_rational_8, t);
  Node ite_78 = nm->mkNode(ITE, equal_15, t, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_18, const_rational_8, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_20, t, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_22, const_rational_8, ite_76);
  Node ite_72 = nm->mkNode(ITE, equal_15, const_rational_8, ite_73);
  Node ite_71 = nm->mkNode(ITE, equal_18, const_rational_8, ite_72);
  Node ite_70 = nm->mkNode(ITE, equal_20, t, ite_71);
  Node ite_67 = nm->mkNode(ITE, equal_12, const_rational_10, t);
  Node ite_66 = nm->mkNode(ITE, equal_15, const_rational_9, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_18, const_rational_8, ite_66);
  Node ite_61 = nm->mkNode(ITE, equal_38, t, const_rational_12);
  Node ite_60 = nm->mkNode(ITE, equal_62, ite_61, t);
  Node ite_59 = nm->mkNode(ITE, equal_64, ite_63, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_69, ite_65, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_74, ite_70, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_80, ite_75, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_86, ite_81, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_95, ite_87, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_102, ite_97, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_108, ite_104, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_112, ite_109, ite_52);
  Node ite_50 = nm->mkNode(ITE, geq_131, ite_113, ite_51);
  Node ite_49 = nm->mkNode(ITE, geq_140, ite_132, ite_50);
  Node ite_48 = nm->mkNode(ITE, geq_212, ite_141, ite_49);
  Node mult_43 = nm->mkNode(MULT, t, mult_44);
  Node geq_45 = nm->mkNode(GEQ, s, mult_43);
  Node equal_42 = nm->mkNode(EQUAL, s, mult_43);
  Node ite_36 = nm->mkNode(ITE, equal_15, const_rational_0, ite_37);
  Node ite_35 = nm->mkNode(ITE, equal_18, const_rational_0, ite_36);
  Node ite_34 = nm->mkNode(ITE, equal_20, t, ite_35);
  Node ite_33 = nm->mkNode(ITE, equal_22, t, ite_34);
  Node ite_32 = nm->mkNode(ITE, equal_40, const_rational_0, ite_33);
  Node ite_31 = nm->mkNode(ITE, equal_42, const_rational_0, ite_32);
  Node ite_26 = nm->mkNode(ITE, equal_27, t, t);
  Node ite_25 = nm->mkNode(ITE, geq_30, ite_26, const_rational_0);
  Node ite_24 = nm->mkNode(ITE, geq_45, ite_31, ite_25);
  Node ite_10 = nm->mkNode(ITE, equal_12, const_rational_2, t);
  Node ite_9 = nm->mkNode(ITE, equal_15, const_rational_1, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_18, const_rational_0, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_20, t, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_22, const_rational_2, ite_7);
  Node ite_5 = nm->mkNode(ITE, not_46, ite_24, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_213, ite_48, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_225, ite_214, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_226, mult_209, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_281, ite_227, ite_2);
  return ite_1;
}

// (define-fun int_bvand_4_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (* s t) (ite (>= s t) s (ite (= t 2) 0 (ite (= t 3) (ite (= s 1) (* s s) s)
// (ite (= t 4) (ite (= s 1) 0 (ite (= s 2) 0 0)) (ite (= t 5) (ite (= s 1) (* s
// s) (ite (= s 2) 0 (ite (= s 4) s 1))) (ite (= t 6) (ite (= s 1) 0 (ite (= s
// 5) 4 (ite (= s 2) s (ite (= s 3) 2 s)))) (ite (= t 7) (ite (= s 1) (* s s)
// (ite (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s s))))) (ite (= t
// 8) (ite (= s 1) 0 (ite (= s 2) 0 (ite (= s 3) 0 (ite (= s 4) 0 (ite (= s 5) 0
// (ite (= s 7) 0 0)))))) (ite (= t 9) (ite (= s 1) (* s s) (ite (= s 2) 0 (ite
// (= s 3) 1 (ite (= s 4) 0 (ite (= s 5) 1 (ite (= s 6) 0 (ite (= s 7) 1
// s))))))) (ite (= t 10) (ite (= s 1) 0 (ite (= s 2) s (ite (= s 3) 2 (ite (= s
// 4) 0 (ite (= s 5) 0 (ite (= s 6) 2 (ite (= s 7) 2 (ite (= s 8) s 8))))))))
// (ite (= t 11) (ite (= s 1) (* s s) (ite (= s 2) s (ite (= s 3) s (ite (= s 4)
// 0 (ite (= s 5) 1 (ite (= s 6) 2 (ite (= s 7) 3 (ite (= s 8) s (ite (= s 9) s
// s))))))))) (ite (= t 12) (ite (= s 1) 0 (ite (= s 2) 0 (ite (= s 3) 0 (ite (=
// s 4) s (ite (= s 5) 4 (ite (= s 6) 4 (ite (= s 7) 4 (ite (= s 8) s (ite (= s
// 9) 8 (ite (= s 10) 8 8)))))))))) (ite (= t 13) (ite (= s 1) (* s s) (ite (= s
// 2) 0 (ite (= s 3) 1 (ite (= s 4) s (ite (= s 5) s (ite (= s 6) 4 (ite (= s 7)
// 5 (ite (= s 8) s (ite (= s 9) s (ite (= s 10) 8 (ite (= s 12) s 9)))))))))))
// (ite (= t 14) (ite (= s 1) 0 (ite (= s 2) s (ite (= s 3) 2 (ite (= s 4) s
// (ite (= s 5) 4 (ite (= s 6) s (ite (= s 7) 6 (ite (= s 8) s (ite (= s 9) 8
// (ite (= s 10) s (ite (= s 11) 10 (ite (= s 12) s 12)))))))))))) (ite (= s 1)
// (* s s) (ite (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s (ite (= s
// 6) s (ite (= s 7) s (ite (= s 8) s (ite (= s 9) s (ite (= s 10) s (ite (= s
// 11) s (ite (= s 12) s (ite (= s 14) s s)))))))))))))))))))))))))))) (ite (= t
// 0) (* s t) (ite (= t 1) (ite (= s 2) 0 (ite (= s 3) (* t t) (ite (= s 4) 0
// (ite (= s 5) (* t t) (ite (= s 6) 0 (ite (= s 7) (* t t) (ite (= s 8) 0 (ite
// (= s 9) (* t t) (ite (= s 10) 0 (ite (= s 11) (* t t) (ite (= s 12) 0 (ite (=
// s 13) (* t t) (ite (= s 14) 0 (* t t)))))))))))))) (ite (= t 2) (ite (= s 3)
// t (ite (= s 4) 0 (ite (= s 5) 0 (ite (= s 6) t (ite (= s 7) t (ite (= s 8) 0
// (ite (= s 9) 0 (ite (= s 10) t (ite (= s 11) t (ite (= s 12) 0 (ite (= s 13)
// 0 (ite (= s 14) t t)))))))))))) (ite (= t 3) (ite (= s 4) 0 (ite (= s 5) 1
// (ite (= s 6) 2 (ite (= s 7) t (ite (= s 15) t (ite (= s 8) 0 (ite (= s 9) 1
// (ite (= s 10) 2 (ite (= s 11) t (ite (= s 12) 0 (ite (= s 13) 1 2)))))))))))
// (ite (= t 4) (ite (= s 5) t (ite (= s 6) t (ite (= s 7) t (ite (= s 8) 0 (ite
// (= s 9) 0 (ite (= s 10) 0 (ite (= s 11) 0 (ite (= s 15) t (ite (= s 12) t
// (ite (= s 13) t t)))))))))) (ite (= t 5) (ite (= s 6) 4 (ite (= s 7) t (ite
// (= s 8) 0 (ite (= s 9) 1 (ite (= s 10) 0 (ite (= s 11) 1 (ite (= s 12) 4 (ite
// (= s 15) t (ite (= s 13) t 4))))))))) (ite (= t 6) (ite (= s 7) t (ite (= s
// 8) 0 (ite (= s 9) 0 (ite (= s 10) 2 (ite (= s 11) 2 (ite (= s 12) 4 (ite (= s
// 13) 4 (ite (= s 14) t t)))))))) (ite (= t 7) (ite (= s 8) 0 (ite (= s 9) 1
// (ite (= s 10) 2 (ite (= s 15) t (ite (= s 11) 3 (ite (= s 14) 6 (ite (= s 12)
// 4 5))))))) (ite (= t 8) (ite (= s 9) t (ite (= s 10) t (ite (= s 11) t (ite
// (= s 12) t (ite (= s 13) t (ite (= s 14) t t)))))) (ite (= t 9) (ite (= s 10)
// 8 (ite (= s 11) t (ite (= s 12) 8 (ite (= s 13) t (ite (= s 14) 8 t))))) (ite
// (= t 10) (ite (= s 11) t (ite (= s 12) 8 (ite (= s 13) 8 (ite (= s 15) t
// t)))) (ite (= t 11) (ite (= s 12) 8 (ite (= s 13) 9 (ite (= s 14) 10 t)))
// (ite (= t 12) (ite (= s 15) t (ite (= s 13) t t)) (ite (= t 13) (ite (= s 14)
// 12 t) t))))))))))))))))
Node int_bvand_4_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_261 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_260 = nm->mkNode(EQUAL, s, const_rational_0);
  Node mult_148 = nm->mkNode(MULT, s, t);
  Node geq_259 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_131 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_118 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_179 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_178 = nm->mkNode(MULT, s, s);
  Node ite_258 = nm->mkNode(ITE, equal_179, mult_178, s);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_105 = nm->mkNode(EQUAL, t, const_rational_4);
  Node equal_146 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_257 = nm->mkNode(ITE, equal_146, const_rational_0, const_rational_0);
  Node ite_256 = nm->mkNode(ITE, equal_179, const_rational_0, ite_257);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_94 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_117 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_255 = nm->mkNode(ITE, equal_117, s, const_rational_1);
  Node ite_254 = nm->mkNode(ITE, equal_146, const_rational_0, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_179, mult_178, ite_254);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_83 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_104 = nm->mkNode(EQUAL, s, const_rational_5);
  Node equal_130 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_252 = nm->mkNode(ITE, equal_130, const_rational_2, s);
  Node ite_251 = nm->mkNode(ITE, equal_146, s, ite_252);
  Node ite_250 = nm->mkNode(ITE, equal_104, const_rational_4, ite_251);
  Node ite_249 = nm->mkNode(ITE, equal_179, const_rational_0, ite_250);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_73 = nm->mkNode(EQUAL, t, const_rational_7);
  Node ite_248 = nm->mkNode(ITE, equal_104, s, s);
  Node ite_247 = nm->mkNode(ITE, equal_117, s, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_130, s, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_146, s, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_179, mult_178, ite_245);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_57 = nm->mkNode(EQUAL, t, const_rational_8);
  Node equal_82 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_243 = nm->mkNode(ITE, equal_82, const_rational_0, const_rational_0);
  Node ite_242 = nm->mkNode(ITE, equal_104, const_rational_0, ite_243);
  Node ite_241 = nm->mkNode(ITE, equal_117, const_rational_0, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_130, const_rational_0, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_146, const_rational_0, ite_240);
  Node ite_238 = nm->mkNode(ITE, equal_179, const_rational_0, ite_239);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_49 = nm->mkNode(EQUAL, t, const_rational_9);
  Node equal_93 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_237 = nm->mkNode(ITE, equal_82, const_rational_1, s);
  Node ite_236 = nm->mkNode(ITE, equal_93, const_rational_0, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_104, const_rational_1, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_117, const_rational_0, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_130, const_rational_1, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_146, const_rational_0, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_179, mult_178, ite_232);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_42 = nm->mkNode(EQUAL, t, const_rational_10);
  Node equal_72 = nm->mkNode(EQUAL, s, const_rational_8);
  Node ite_230 = nm->mkNode(ITE, equal_72, s, const_rational_8);
  Node ite_229 = nm->mkNode(ITE, equal_82, const_rational_2, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_93, const_rational_2, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_104, const_rational_0, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_117, const_rational_0, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_130, const_rational_2, ite_226);
  Node ite_224 = nm->mkNode(ITE, equal_146, s, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_179, const_rational_0, ite_224);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_35 = nm->mkNode(EQUAL, t, const_rational_11);
  Node equal_56 = nm->mkNode(EQUAL, s, const_rational_9);
  Node ite_222 = nm->mkNode(ITE, equal_56, s, s);
  Node ite_221 = nm->mkNode(ITE, equal_72, s, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_82, const_rational_3, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_93, const_rational_2, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_104, const_rational_1, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_117, const_rational_0, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_130, s, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_146, s, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_179, mult_178, ite_215);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_27 = nm->mkNode(EQUAL, t, const_rational_12);
  Node equal_48 = nm->mkNode(EQUAL, s, const_rational_10);
  Node ite_213 = nm->mkNode(ITE, equal_48, const_rational_8, const_rational_8);
  Node ite_212 = nm->mkNode(ITE, equal_56, const_rational_8, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_72, s, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_82, const_rational_4, ite_211);
  Node ite_209 = nm->mkNode(ITE, equal_93, const_rational_4, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_104, const_rational_4, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_117, s, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_130, const_rational_0, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_146, const_rational_0, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_179, const_rational_0, ite_205);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_20 = nm->mkNode(EQUAL, t, const_rational_13);
  Node equal_34 = nm->mkNode(EQUAL, s, const_rational_12);
  Node ite_203 = nm->mkNode(ITE, equal_34, s, const_rational_9);
  Node ite_202 = nm->mkNode(ITE, equal_48, const_rational_8, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_56, s, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_72, s, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_82, const_rational_5, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_93, const_rational_4, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_104, s, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_117, s, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_130, const_rational_1, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_146, const_rational_0, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_179, mult_178, ite_194);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_192 = nm->mkNode(EQUAL, t, const_rational_14);
  Node equal_41 = nm->mkNode(EQUAL, s, const_rational_11);
  Node ite_191 = nm->mkNode(ITE, equal_34, s, const_rational_12);
  Node ite_190 = nm->mkNode(ITE, equal_41, const_rational_10, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_48, s, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_56, const_rational_8, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_72, s, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_82, const_rational_6, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_93, s, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_104, const_rational_4, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_117, s, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_130, const_rational_2, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_146, s, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_179, const_rational_0, ite_181);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_177 = nm->mkNode(ITE, equal_18, s, s);
  Node ite_176 = nm->mkNode(ITE, equal_34, s, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_41, s, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_48, s, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_56, s, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_72, s, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_82, s, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_93, s, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_104, s, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_117, s, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_130, s, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_146, s, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_179, mult_178, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_192, ite_180, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_20, ite_193, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_27, ite_204, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_35, ite_214, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_42, ite_223, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_49, ite_231, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_57, ite_238, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_73, ite_244, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_83, ite_249, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_94, ite_253, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_105, ite_256, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_118, ite_258, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_131, const_rational_0, ite_153);
  Node ite_151 = nm->mkNode(ITE, geq_259, s, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_260, mult_148, ite_151);
  Node equal_149 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_147 = nm->mkNode(EQUAL, t, const_rational_1);
  Node mult_145 = nm->mkNode(MULT, t, t);
  Node equal_24 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_144 = nm->mkNode(ITE, equal_18, const_rational_0, mult_145);
  Node ite_143 = nm->mkNode(ITE, equal_24, mult_145, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_34, const_rational_0, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_41, mult_145, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_48, const_rational_0, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_56, mult_145, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_72, const_rational_0, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_82, mult_145, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_93, const_rational_0, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_104, mult_145, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_117, const_rational_0, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_130, mult_145, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_146, const_rational_0, ite_133);
  Node ite_55 = nm->mkNode(ITE, equal_18, t, t);
  Node ite_129 = nm->mkNode(ITE, equal_24, const_rational_0, ite_55);
  Node ite_128 = nm->mkNode(ITE, equal_34, const_rational_0, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_41, t, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_48, t, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_56, const_rational_0, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_72, const_rational_0, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_82, t, ite_124);
  Node ite_122 = nm->mkNode(ITE, equal_93, t, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_104, const_rational_0, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_117, const_rational_0, ite_121);
  Node ite_119 = nm->mkNode(ITE, equal_130, t, ite_120);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_116 = nm->mkNode(ITE, equal_24, const_rational_1, const_rational_2);
  Node ite_115 = nm->mkNode(ITE, equal_34, const_rational_0, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_41, t, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_48, const_rational_2, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_56, const_rational_1, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_72, const_rational_0, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_25, t, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_82, t, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_93, const_rational_2, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_104, const_rational_1, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_117, const_rational_0, ite_107);
  Node ite_23 = nm->mkNode(ITE, equal_24, t, t);
  Node ite_103 = nm->mkNode(ITE, equal_34, t, ite_23);
  Node ite_102 = nm->mkNode(ITE, equal_25, t, ite_103);
  Node ite_101 = nm->mkNode(ITE, equal_41, const_rational_0, ite_102);
  Node ite_100 = nm->mkNode(ITE, equal_48, const_rational_0, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_56, const_rational_0, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_72, const_rational_0, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_82, t, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_93, t, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_104, t, ite_96);
  Node ite_92 = nm->mkNode(ITE, equal_24, t, const_rational_4);
  Node ite_91 = nm->mkNode(ITE, equal_25, t, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_34, const_rational_4, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_41, const_rational_1, ite_90);
  Node ite_88 = nm->mkNode(ITE, equal_48, const_rational_0, ite_89);
  Node ite_87 = nm->mkNode(ITE, equal_56, const_rational_1, ite_88);
  Node ite_86 = nm->mkNode(ITE, equal_72, const_rational_0, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_82, t, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_93, const_rational_4, ite_85);
  Node ite_81 = nm->mkNode(ITE, equal_24, const_rational_4, ite_55);
  Node ite_80 = nm->mkNode(ITE, equal_34, const_rational_4, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_41, const_rational_2, ite_80);
  Node ite_78 = nm->mkNode(ITE, equal_48, const_rational_2, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_56, const_rational_0, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_72, const_rational_0, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_82, t, ite_76);
  Node ite_64 = nm->mkNode(ITE, equal_34, const_rational_4, const_rational_5);
  Node ite_63 = nm->mkNode(ITE, equal_18, const_rational_6, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_41, const_rational_3, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_25, t, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_48, const_rational_2, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_56, const_rational_1, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_72, const_rational_0, ite_59);
  Node ite_54 = nm->mkNode(ITE, equal_24, t, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_34, t, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_41, t, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_48, t, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_56, t, ite_51);
  Node ite_47 = nm->mkNode(ITE, equal_18, const_rational_8, t);
  Node ite_46 = nm->mkNode(ITE, equal_24, t, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_34, const_rational_8, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_41, t, ite_45);
  Node ite_43 = nm->mkNode(ITE, equal_48, const_rational_8, ite_44);
  Node ite_40 = nm->mkNode(ITE, equal_25, t, t);
  Node ite_39 = nm->mkNode(ITE, equal_24, const_rational_8, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_34, const_rational_8, ite_39);
  Node ite_37 = nm->mkNode(ITE, equal_41, t, ite_38);
  Node ite_30 = nm->mkNode(ITE, equal_18, const_rational_10, t);
  Node ite_29 = nm->mkNode(ITE, equal_24, const_rational_9, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_34, const_rational_8, ite_29);
  Node ite_22 = nm->mkNode(ITE, equal_25, t, ite_23);
  Node ite_16 = nm->mkNode(ITE, equal_18, const_rational_12, t);
  Node ite_15 = nm->mkNode(ITE, equal_20, ite_16, t);
  Node ite_14 = nm->mkNode(ITE, equal_27, ite_22, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_35, ite_28, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_42, ite_37, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_49, ite_43, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_57, ite_50, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_73, ite_58, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_83, ite_75, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_94, ite_84, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_105, ite_95, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_118, ite_106, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_131, ite_119, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_147, ite_132, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_149, mult_148, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_261, ite_150, ite_2);
  return ite_1;
}

// (define-fun int_bvor_1_lia ((s Int) (t Int)) Int (ite (= 0 s) t s))
Node int_bvor_1_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_2 = nm->mkNode(EQUAL, const_rational_0, s);
  Node ite_1 = nm->mkNode(ITE, equal_2, t, s);
  return ite_1;
}

// (define-fun int_bvor_1_nia ((s Int) (t Int)) Int (ite (= 0 s) t s))
Node int_bvor_1_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_2 = nm->mkNode(EQUAL, const_rational_0, s);
  Node ite_1 = nm->mkNode(ITE, equal_2, t, s);
  return ite_1;
}

// (define-fun int_bvor_2_lia ((s Int) (t Int)) Int (ite (= 0 s) t (ite (= s t)
// t (ite (= 0 t) s 3))))
Node int_bvor_2_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_8 = nm->mkNode(EQUAL, const_rational_0, s);
  Node equal_7 = nm->mkNode(EQUAL, s, t);
  Node equal_5 = nm->mkNode(EQUAL, const_rational_0, t);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node ite_3 = nm->mkNode(ITE, equal_5, s, const_rational_3);
  Node ite_2 = nm->mkNode(ITE, equal_7, t, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_8, t, ite_2);
  return ite_1;
}

// (define-fun int_bvor_2_nia ((s Int) (t Int)) Int (ite (= 0 s) t (ite (= s t)
// t (ite (= 0 t) s 3))))
Node int_bvor_2_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_8 = nm->mkNode(EQUAL, const_rational_0, s);
  Node equal_7 = nm->mkNode(EQUAL, s, t);
  Node equal_5 = nm->mkNode(EQUAL, const_rational_0, t);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node ite_3 = nm->mkNode(ITE, equal_5, s, const_rational_3);
  Node ite_2 = nm->mkNode(ITE, equal_7, t, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_8, t, ite_2);
  return ite_1;
}

// (define-fun int_bvor_3_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (ite (= s t) t t) (ite (>= s t) t (ite (= t 2) (* s 3) (ite (= t 3) (ite (= s
// 1) (* s t) t) (ite (= t 4) (ite (= s 1) (* s 5) (ite (= s 2) (* s 3) 7)) (ite
// (= t 5) (ite (= s 1) (* s t) (ite (= s 2) 7 (ite (= s 3) 7 t))) (ite (= s 1)
// (* s 7) (ite (= s 2) t (ite (= s 3) 7 (ite (= s 4) t (ite (= s 6) t
// 7))))))))))) (ite (= t 0) (ite (= s 1) (* s s) (ite (= s 2) s (ite (= s 3)
// (ite (= s t) t s) (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s s)))))) (ite
// (= t 1) (ite (= s 2) (* t 3) (ite (= s 3) (* s t) (ite (= s 4) (* t 5) (ite
// (= s 5) (* s t) (* t 7))))) (ite (= t 2) (ite (= s 7) s (ite (= s 6) (* t 3)
// (ite (= s 3) (ite (= s t) t s) (ite (= s 4) (* t 3) 7)))) (ite (= s 7) (ite
// (= t 3) s (ite (= t 5) s (ite (= t 4) s s))) (ite (= t 3) (ite (= s 4) 7 (ite
// (= s 5) 7 7)) (ite (= t 4) (ite (= s 6) s s) 7))))))))
Node int_bvor_3_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_78 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_77 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_32 = nm->mkNode(EQUAL, s, t);
  Node ite_76 = nm->mkNode(ITE, equal_32, t, t);
  Node geq_75 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_34 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node mult_72 = nm->mkNode(MULT, s, const_rational_3);
  Node equal_19 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_41 = nm->mkNode(MULT, s, t);
  Node ite_74 = nm->mkNode(ITE, equal_52, mult_41, t);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_12 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node mult_73 = nm->mkNode(MULT, s, const_rational_5);
  Node equal_43 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node ite_71 = nm->mkNode(ITE, equal_43, mult_72, const_rational_7);
  Node ite_70 = nm->mkNode(ITE, equal_52, mult_73, ite_71);
  Node equal_24 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_33 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_69 = nm->mkNode(ITE, equal_33, const_rational_7, t);
  Node ite_68 = nm->mkNode(ITE, equal_43, const_rational_7, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_52, mult_41, ite_68);
  Node mult_66 = nm->mkNode(MULT, s, const_rational_7);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_10 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_65 = nm->mkNode(ITE, equal_10, t, const_rational_7);
  Node ite_64 = nm->mkNode(ITE, equal_18, t, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_33, const_rational_7, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_43, t, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_52, mult_66, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_24, ite_67, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_12, ite_70, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_19, ite_74, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_34, mult_72, ite_58);
  Node ite_56 = nm->mkNode(ITE, geq_75, t, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_77, ite_76, ite_56);
  Node equal_53 = nm->mkNode(EQUAL, t, const_rational_0);
  Node mult_51 = nm->mkNode(MULT, s, s);
  Node ite_31 = nm->mkNode(ITE, equal_32, t, s);
  Node equal_16 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_9 = nm->mkNode(ITE, equal_10, s, s);
  Node ite_50 = nm->mkNode(ITE, equal_16, s, ite_9);
  Node ite_49 = nm->mkNode(ITE, equal_18, s, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_33, ite_31, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_43, s, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_52, mult_51, ite_47);
  Node equal_44 = nm->mkNode(EQUAL, t, const_rational_1);
  Node mult_30 = nm->mkNode(MULT, t, const_rational_3);
  Node mult_42 = nm->mkNode(MULT, t, const_rational_5);
  Node mult_40 = nm->mkNode(MULT, t, const_rational_7);
  Node ite_39 = nm->mkNode(ITE, equal_16, mult_41, mult_40);
  Node ite_38 = nm->mkNode(ITE, equal_18, mult_42, ite_39);
  Node ite_37 = nm->mkNode(ITE, equal_33, mult_41, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_43, mult_30, ite_37);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_29 = nm->mkNode(ITE, equal_18, mult_30, const_rational_7);
  Node ite_28 = nm->mkNode(ITE, equal_33, ite_31, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_10, mult_30, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_25, s, ite_27);
  Node ite_23 = nm->mkNode(ITE, equal_12, s, s);
  Node ite_22 = nm->mkNode(ITE, equal_24, s, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_19, s, ite_22);
  Node ite_15 = nm->mkNode(ITE, equal_16, const_rational_7, const_rational_7);
  Node ite_14 = nm->mkNode(ITE, equal_18, const_rational_7, ite_15);
  Node ite_7 = nm->mkNode(ITE, equal_12, ite_9, const_rational_7);
  Node ite_6 = nm->mkNode(ITE, equal_19, ite_14, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_25, ite_21, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_34, ite_26, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_44, ite_36, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_53, ite_46, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_78, ite_55, ite_2);
  return ite_1;
}

// (define-fun int_bvor_3_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (+ s t) (ite (>= s t) t (ite (= t 2) (+ s t) (ite (= s 6) (+ s 1) (ite (= t
// 3) (ite (= s 2) (+ s 1) (* s t)) (ite (= t 4) (+ s t) (ite (= s 5) (+ s 2)
// (ite (= t 5) (ite (= s 4) (+ s 1) (ite (= s 1) (* s t) (ite (= s 2) (+ s t)
// (+ s 4)))) (ite (= s 1) (* s 7) (ite (= s 2) t (ite (= s 3) (+ s 4)
// t))))))))))) (ite (= t 0) (+ s t) (ite (= t 1) (ite (= s 2) (+ s t) (ite (= s
// 3) (* s t) (ite (= s 4) (+ s t) (ite (= s 7) (* s t) (ite (= s 5) (* s t) (+
// s t)))))) (ite (= t 2) (ite (= s 3) (ite (= s t) t s) (ite (= s 4) (+ s t)
// (ite (= s 5) (+ s t) (ite (= s 6) s (ite (>= t s) t s))))) (ite (= t 3) (ite
// (= s 4) (+ s t) (ite (= s 5) (+ s 2) (ite (= s 6) (+ s 1) (ite (>= t s) t
// s)))) (ite (= t 4) (ite (= s 5) s (ite (= s 6) s (ite (>= t s) t s))) (ite (=
// t 5) (ite (= s 7) (ite (>= t s) t s) (+ s 1)) (ite (>= t s) t s)))))))))
Node int_bvor_3_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_9 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_69 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_29 = nm->mkNode(PLUS, s, t);
  Node geq_68 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_39 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_19 = nm->mkNode(EQUAL, s, const_rational_6);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node plus_11 = nm->mkNode(PLUS, s, const_rational_1);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_31 = nm->mkNode(EQUAL, t, const_rational_3);
  Node equal_46 = nm->mkNode(EQUAL, s, const_rational_2);
  Node mult_45 = nm->mkNode(MULT, s, t);
  Node ite_67 = nm->mkNode(ITE, equal_46, plus_11, mult_45);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_22 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_21 = nm->mkNode(EQUAL, s, const_rational_5);
  Node plus_27 = nm->mkNode(PLUS, s, const_rational_2);
  Node equal_15 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_30 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_63 = nm->mkNode(EQUAL, s, const_rational_1);
  Node plus_61 = nm->mkNode(PLUS, s, const_rational_4);
  Node ite_66 = nm->mkNode(ITE, equal_46, plus_29, plus_61);
  Node ite_65 = nm->mkNode(ITE, equal_63, mult_45, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_30, plus_11, ite_65);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node mult_62 = nm->mkNode(MULT, s, const_rational_7);
  Node equal_38 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_60 = nm->mkNode(ITE, equal_38, plus_61, t);
  Node ite_59 = nm->mkNode(ITE, equal_46, t, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_63, mult_62, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_15, ite_64, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_21, plus_27, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_22, plus_29, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_31, ite_67, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_19, plus_11, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_39, plus_29, ite_53);
  Node ite_51 = nm->mkNode(ITE, geq_68, t, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_69, plus_29, ite_51);
  Node equal_48 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_47 = nm->mkNode(EQUAL, t, const_rational_1);
  Node equal_13 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_44 = nm->mkNode(ITE, equal_21, mult_45, plus_29);
  Node ite_43 = nm->mkNode(ITE, equal_13, mult_45, ite_44);
  Node ite_42 = nm->mkNode(ITE, equal_30, plus_29, ite_43);
  Node ite_41 = nm->mkNode(ITE, equal_38, mult_45, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_46, plus_29, ite_41);
  Node equal_37 = nm->mkNode(EQUAL, s, t);
  Node ite_36 = nm->mkNode(ITE, equal_37, t, s);
  Node ite_8 = nm->mkNode(ITE, geq_9, t, s);
  Node ite_18 = nm->mkNode(ITE, equal_19, s, ite_8);
  Node ite_35 = nm->mkNode(ITE, equal_21, plus_29, ite_18);
  Node ite_34 = nm->mkNode(ITE, equal_30, plus_29, ite_35);
  Node ite_33 = nm->mkNode(ITE, equal_38, ite_36, ite_34);
  Node ite_26 = nm->mkNode(ITE, equal_19, plus_11, ite_8);
  Node ite_25 = nm->mkNode(ITE, equal_21, plus_27, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_30, plus_29, ite_25);
  Node ite_17 = nm->mkNode(ITE, equal_21, s, ite_18);
  Node ite_10 = nm->mkNode(ITE, equal_13, ite_8, plus_11);
  Node ite_7 = nm->mkNode(ITE, equal_15, ite_10, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_22, ite_17, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_31, ite_24, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_39, ite_33, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_47, ite_40, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_48, plus_29, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_9, ite_50, ite_2);
  return ite_1;
}

// (define-fun int_bvor_4_lia ((s Int) (t Int)) Int (ite (>= 3 s) (ite (not (= s
// 3)) (ite (>= t (* s t)) (ite (not (= s 2)) (ite (>= s (* s t)) (ite (not (>=
// t s)) (* s s) t) (ite (>= 3 t) (* s 3) (ite (= t 4) (+ s t) (ite (= t 5) (* s
// t) (ite (= t 6) (+ s t) (ite (= t 7) (* s t) (ite (= t 8) (+ s t) (ite (= t
// 13) (* s t) (ite (= t 12) (+ s t) (ite (= t 9) (* s t) (ite (= t 10) (+ s t)
// (ite (= t 11) (* s t) (* s 15))))))))))))) (+ s t)) (ite (>= s (* s t)) (+ s
// t) (ite (>= t (* s s)) (ite (>= (* s s) t) (+ s t) (ite (= t 5) (+ s t) (ite
// (= t 6) (* s 3) (ite (= t 7) t (ite (= t 8) (+ s t) (ite (= t 9) (+ s t) (ite
// (= t 10) (* s 5) (ite (= t 13) (+ s t) (ite (= t 11) t (ite (= t 12) (+ s t)
// t)))))))))) (ite (not (= t 3)) t t)))) (ite (>= t (* s t)) (+ s t) (ite (>= s
// (* s t)) (* s t) (ite (>= t s) (ite (>= t (* s s)) (ite (>= (* s s) t) 11
// (ite (= t 10) 11 (ite (= t 11) t (* s 5)))) (ite (= t 8) (+ s t) (ite (>= 3
// t) t (ite (= t 4) (+ s t) (ite (= t 5) 7 (ite (= t 6) 7 t)))))) s)))) (ite
// (>= t (* s t)) (+ s t) (ite (>= s (* s t)) (ite (= s 4) (+ s t) (ite (= s 5)
// (* s t) (ite (= s 6) (+ s t) (ite (= s 7) (* s t) (ite (= s 8) (+ s t) (ite
// (= s 9) (* s t) (ite (= s 10) (+ s t) (ite (= s 11) (* s t) (ite (= s 12) (+
// s t) (ite (= s 15) (* s t) (ite (= s 13) (* s t) (+ s t)))))))))))) (ite (>=
// (* t t) s) (ite (>= t s) (ite (>= s t) t (ite (= t 5) t (ite (= t 6) (ite (=
// s 5) 7 t) (ite (= t 7) (ite (= s 4) t (ite (= s 5) t t)) (ite (= t 8) (+ s t)
// (ite (= t 9) (ite (= s 4) (+ s t) (ite (= s 5) 13 (ite (= s 6) (+ s t) (ite
// (= s 8) t 15)))) (ite (= t 10) (ite (= s 9) 11 (ite (= s 4) (+ s t) (ite (= s
// 5) (+ s t) (ite (= s 6) 14 (ite (= s 7) 15 t))))) (ite (= t 11) (ite (= s 4)
// (+ s t) (ite (= s 10) t (ite (= s 5) (* s 3) (ite (= s 6) 15 (ite (= s 7) 15
// (ite (= s 8) t t)))))) (ite (= t 12) (ite (= s 4) (* s 3) (ite (= s 5) 13
// (ite (= s 6) 14 (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) 13 (ite (= s 10)
// 14 15))))))) (ite (= t 13) (ite (= s 4) t (ite (= s 5) t (ite (= s 12) t (ite
// (= s 6) 15 (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) t (ite (= s 10) 15
// 15)))))))) (ite (= s 4) t (ite (= s 5) (* s 3) (ite (= s 6) t (ite (= s 14) t
// (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) 15 (ite (= s 10) t (ite (= s 11)
// 15 (ite (= s 12) t 15)))))))))))))))))))) (ite (= s 15) (ite (>= s (* s t))
// (* s t) (ite (>= (* t t) s) (ite (>= t s) t (ite (>= s (* t 2)) (ite (>= s (*
// t 3)) (ite (= s (* t 3)) (* t 3) s) s) s)) (ite (= t 3) (* t 5) s))) (ite (>=
// 3 t) (ite (not (= t 3)) (+ s t) (ite (>= s (* t t)) 11 (ite (>= s (* t 2))
// (ite (= s (* t 2)) 7 (ite (= s 7) s (+ s t))) (ite (= s 4) (+ s t) 7)))) (ite
// (>= s (* t 2)) (ite (>= s (* t 3)) (ite (= s (* t 3)) (* t 3) (ite (= s 13) s
// s)) (ite (= s 14) (ite (= t 7) 15 (ite (= t 5) (* t 3) s)) (ite (= s (* t 2))
// (ite (= t 4) (+ s t) (ite (= t 5) (+ s t) 14)) (ite (= t 4) (+ s t) (ite (= t
// 5) (ite (= s 11) (* t 3) (ite (= s 12) 13 s)) 15))))) (ite (= t 4) (ite (= s
// 5) s (ite (= s 6) s s)) (ite (= t 5) (ite (= s 6) 7 (ite (= s 7) s (ite (= s
// 8) (+ s t) 13))) (ite (= t 6) (ite (= s 7) s (ite (= s 8) (+ s t) (ite (= s
// 9) (+ s t) (ite (= s 10) 14 15)))) (ite (= t 7) (ite (= s 8) (+ s t) (ite (=
// s 9) 15 (ite (= s 10) 15 (ite (= s 11) 15 (ite (= s 12) 15 15))))) (ite (= t
// 8) (ite (= s 9) s (ite (= s 10) s (ite (= s 11) s (ite (= s 12) s (ite (= s
// 14) s s))))) (ite (= t 9) (ite (= s 10) 11 (ite (= s 11) s (ite (= s 14) 15
// (ite (= s 12) 13 s)))) (ite (= t 10) (ite (= s 11) s (ite (= s 12) 14 (ite (=
// s 14) s 15))) (ite (= t 11) (ite (= s 12) 15 (ite (= s 13) 15 15)) (ite (= t
// 12) (ite (= s 13) s s) 15))))))))))))) (ite (not (= t 3)) (ite (>= s (* t (*
// t t))) (ite (= s (* t (* t t))) (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) (*
// t 5) (ite (= s 11) s (ite (= s 12) (+ s t) (ite (= s 13) (+ s t) (ite (= s
// 14) (* t 7) (ite (>= t (* s t)) (+ s t) (ite (>= s (* s t)) (* s t) (ite (>=
// (* t t) s) (ite (>= t s) t (ite (>= s (* t 2)) (ite (>= s (* t 3)) (ite (= s
// (* t 3)) (* t 3) s) s) s)) (ite (= t 3) (* t 5) s))))))))))) (ite (>= s (* t
// 3)) (ite (= s (* t 3)) (* t 3) s) (+ s t))) (ite (= s 10) 11 (ite (= s 11) s
// (* t 5)))))))))
Node int_bvor_4_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node geq_258 = nm->mkNode(GEQ, const_rational_3, s);
  Node equal_257 = nm->mkNode(EQUAL, s, const_rational_3);
  Node not_256 = nm->mkNode(NOT, equal_257);
  Node mult_43 = nm->mkNode(MULT, s, t);
  Node geq_45 = nm->mkNode(GEQ, t, mult_43);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_255 = nm->mkNode(EQUAL, s, const_rational_2);
  Node not_254 = nm->mkNode(NOT, equal_255);
  Node geq_44 = nm->mkNode(GEQ, s, mult_43);
  Node geq_40 = nm->mkNode(GEQ, t, s);
  Node not_253 = nm->mkNode(NOT, geq_40);
  Node mult_222 = nm->mkNode(MULT, s, s);
  Node ite_252 = nm->mkNode(ITE, not_253, mult_222, t);
  Node geq_139 = nm->mkNode(GEQ, const_rational_3, t);
  Node mult_161 = nm->mkNode(MULT, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_117 = nm->mkNode(EQUAL, t, const_rational_4);
  Node plus_16 = nm->mkNode(PLUS, s, t);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_113 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_107 = nm->mkNode(EQUAL, t, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_101 = nm->mkNode(EQUAL, t, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_93 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_170 = nm->mkNode(EQUAL, t, const_rational_13);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_75 = nm->mkNode(EQUAL, t, const_rational_12);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_87 = nm->mkNode(EQUAL, t, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_82 = nm->mkNode(EQUAL, t, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_78 = nm->mkNode(EQUAL, t, const_rational_11);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node mult_251 = nm->mkNode(MULT, s, const_rational_15);
  Node ite_250 = nm->mkNode(ITE, equal_78, mult_43, mult_251);
  Node ite_249 = nm->mkNode(ITE, equal_82, plus_16, ite_250);
  Node ite_248 = nm->mkNode(ITE, equal_87, mult_43, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_75, plus_16, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_170, mult_43, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_93, plus_16, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_101, mult_43, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_107, plus_16, ite_244);
  Node ite_242 = nm->mkNode(ITE, equal_113, mult_43, ite_243);
  Node ite_241 = nm->mkNode(ITE, equal_117, plus_16, ite_242);
  Node ite_240 = nm->mkNode(ITE, geq_139, mult_161, ite_241);
  Node ite_239 = nm->mkNode(ITE, geq_44, ite_252, ite_240);
  Node ite_238 = nm->mkNode(ITE, not_254, ite_239, plus_16);
  Node geq_223 = nm->mkNode(GEQ, t, mult_222);
  Node geq_221 = nm->mkNode(GEQ, mult_222, t);
  Node mult_220 = nm->mkNode(MULT, s, const_rational_5);
  Node ite_237 = nm->mkNode(ITE, equal_75, plus_16, t);
  Node ite_236 = nm->mkNode(ITE, equal_78, t, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_170, plus_16, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_82, mult_220, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_87, plus_16, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_93, plus_16, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_101, t, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_107, mult_161, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_113, plus_16, ite_230);
  Node ite_228 = nm->mkNode(ITE, geq_221, plus_16, ite_229);
  Node equal_33 = nm->mkNode(EQUAL, t, const_rational_3);
  Node not_59 = nm->mkNode(NOT, equal_33);
  Node ite_227 = nm->mkNode(ITE, not_59, t, t);
  Node ite_226 = nm->mkNode(ITE, geq_223, ite_228, ite_227);
  Node ite_225 = nm->mkNode(ITE, geq_44, plus_16, ite_226);
  Node ite_224 = nm->mkNode(ITE, geq_45, ite_238, ite_225);
  Node ite_219 = nm->mkNode(ITE, equal_78, t, mult_220);
  Node ite_218 = nm->mkNode(ITE, equal_82, const_rational_11, ite_219);
  Node ite_217 = nm->mkNode(ITE, geq_221, const_rational_11, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_107, const_rational_7, t);
  Node ite_215 = nm->mkNode(ITE, equal_113, const_rational_7, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_117, plus_16, ite_215);
  Node ite_213 = nm->mkNode(ITE, geq_139, t, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_93, plus_16, ite_213);
  Node ite_211 = nm->mkNode(ITE, geq_223, ite_217, ite_212);
  Node ite_210 = nm->mkNode(ITE, geq_40, ite_211, s);
  Node ite_209 = nm->mkNode(ITE, geq_44, mult_43, ite_210);
  Node ite_208 = nm->mkNode(ITE, geq_45, plus_16, ite_209);
  Node ite_207 = nm->mkNode(ITE, not_256, ite_224, ite_208);
  Node equal_135 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_116 = nm->mkNode(EQUAL, s, const_rational_5);
  Node equal_112 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_106 = nm->mkNode(EQUAL, s, const_rational_7);
  Node equal_100 = nm->mkNode(EQUAL, s, const_rational_8);
  Node equal_54 = nm->mkNode(EQUAL, s, const_rational_9);
  Node equal_12 = nm->mkNode(EQUAL, s, const_rational_10);
  Node equal_10 = nm->mkNode(EQUAL, s, const_rational_11);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_12);
  Node equal_140 = nm->mkNode(EQUAL, s, const_rational_15);
  Node equal_50 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_206 = nm->mkNode(ITE, equal_50, mult_43, plus_16);
  Node ite_205 = nm->mkNode(ITE, equal_140, mult_43, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_52, plus_16, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_10, mult_43, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_12, plus_16, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_54, mult_43, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_100, plus_16, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_106, mult_43, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_112, plus_16, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_116, mult_43, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_135, plus_16, ite_197);
  Node mult_42 = nm->mkNode(MULT, t, t);
  Node geq_41 = nm->mkNode(GEQ, mult_42, s);
  Node geq_195 = nm->mkNode(GEQ, s, t);
  Node ite_194 = nm->mkNode(ITE, equal_116, const_rational_7, t);
  Node ite_193 = nm->mkNode(ITE, equal_116, t, t);
  Node ite_192 = nm->mkNode(ITE, equal_135, t, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_100, t, const_rational_15);
  Node ite_190 = nm->mkNode(ITE, equal_112, plus_16, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_116, const_rational_13, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_135, plus_16, ite_189);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node ite_187 = nm->mkNode(ITE, equal_106, const_rational_15, t);
  Node ite_186 = nm->mkNode(ITE, equal_112, const_rational_14, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_116, plus_16, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_135, plus_16, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_54, const_rational_11, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_100, t, t);
  Node ite_181 = nm->mkNode(ITE, equal_106, const_rational_15, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_112, const_rational_15, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_116, mult_161, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_12, t, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_135, plus_16, ite_178);
  Node ite_105 =
      nm->mkNode(ITE, equal_12, const_rational_14, const_rational_15);
  Node ite_176 = nm->mkNode(ITE, equal_54, const_rational_13, ite_105);
  Node ite_175 = nm->mkNode(ITE, equal_100, t, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_106, const_rational_15, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_112, const_rational_14, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_116, const_rational_13, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_135, mult_161, ite_172);
  Node ite_169 =
      nm->mkNode(ITE, equal_12, const_rational_15, const_rational_15);
  Node ite_168 = nm->mkNode(ITE, equal_54, t, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_100, t, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_106, const_rational_15, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_112, const_rational_15, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_52, t, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_116, t, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_135, t, ite_163);
  Node equal_48 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_160 = nm->mkNode(ITE, equal_52, t, const_rational_15);
  Node ite_159 = nm->mkNode(ITE, equal_10, const_rational_15, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_12, t, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_54, const_rational_15, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_100, t, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_106, const_rational_15, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_48, t, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_112, t, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_116, mult_161, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_135, t, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_170, ite_162, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_75, ite_171, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_78, ite_177, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_82, ite_183, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_87, ite_188, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_93, plus_16, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_101, ite_192, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_107, ite_194, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_113, t, ite_143);
  Node ite_141 = nm->mkNode(ITE, geq_195, t, ite_142);
  Node mult_38 = nm->mkNode(MULT, t, const_rational_2);
  Node geq_37 = nm->mkNode(GEQ, s, mult_38);
  Node mult_18 = nm->mkNode(MULT, t, const_rational_3);
  Node geq_21 = nm->mkNode(GEQ, s, mult_18);
  Node equal_20 = nm->mkNode(EQUAL, s, mult_18);
  Node ite_17 = nm->mkNode(ITE, equal_20, mult_18, s);
  Node ite_36 = nm->mkNode(ITE, geq_21, ite_17, s);
  Node ite_35 = nm->mkNode(ITE, geq_37, ite_36, s);
  Node ite_34 = nm->mkNode(ITE, geq_40, t, ite_35);
  Node mult_8 = nm->mkNode(MULT, t, const_rational_5);
  Node ite_32 = nm->mkNode(ITE, equal_33, mult_8, s);
  Node ite_31 = nm->mkNode(ITE, geq_41, ite_34, ite_32);
  Node ite_30 = nm->mkNode(ITE, geq_44, mult_43, ite_31);
  Node geq_138 = nm->mkNode(GEQ, s, mult_42);
  Node equal_127 = nm->mkNode(EQUAL, s, mult_38);
  Node ite_137 = nm->mkNode(ITE, equal_106, s, plus_16);
  Node ite_136 = nm->mkNode(ITE, equal_127, const_rational_7, ite_137);
  Node ite_134 = nm->mkNode(ITE, equal_135, plus_16, const_rational_7);
  Node ite_133 = nm->mkNode(ITE, geq_37, ite_136, ite_134);
  Node ite_132 = nm->mkNode(ITE, geq_138, const_rational_11, ite_133);
  Node ite_131 = nm->mkNode(ITE, not_59, plus_16, ite_132);
  Node ite_74 = nm->mkNode(ITE, equal_50, s, s);
  Node ite_130 = nm->mkNode(ITE, equal_20, mult_18, ite_74);
  Node ite_129 = nm->mkNode(ITE, equal_113, mult_18, s);
  Node ite_128 = nm->mkNode(ITE, equal_101, const_rational_15, ite_129);
  Node ite_126 = nm->mkNode(ITE, equal_113, plus_16, const_rational_14);
  Node ite_125 = nm->mkNode(ITE, equal_117, plus_16, ite_126);
  Node ite_86 = nm->mkNode(ITE, equal_52, const_rational_13, s);
  Node ite_124 = nm->mkNode(ITE, equal_10, mult_18, ite_86);
  Node ite_123 = nm->mkNode(ITE, equal_113, ite_124, const_rational_15);
  Node ite_122 = nm->mkNode(ITE, equal_117, plus_16, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_127, ite_125, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_48, ite_128, ite_121);
  Node ite_119 = nm->mkNode(ITE, geq_21, ite_130, ite_120);
  Node ite_115 = nm->mkNode(ITE, equal_112, s, s);
  Node ite_114 = nm->mkNode(ITE, equal_116, s, ite_115);
  Node ite_111 = nm->mkNode(ITE, equal_100, plus_16, const_rational_13);
  Node ite_110 = nm->mkNode(ITE, equal_106, s, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_112, const_rational_7, ite_110);
  Node ite_104 = nm->mkNode(ITE, equal_54, plus_16, ite_105);
  Node ite_103 = nm->mkNode(ITE, equal_100, plus_16, ite_104);
  Node ite_102 = nm->mkNode(ITE, equal_106, s, ite_103);
  Node ite_99 = nm->mkNode(ITE, equal_52, const_rational_15, const_rational_15);
  Node ite_98 = nm->mkNode(ITE, equal_10, const_rational_15, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_12, const_rational_15, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_54, const_rational_15, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_100, plus_16, ite_96);
  Node ite_92 = nm->mkNode(ITE, equal_48, s, s);
  Node ite_91 = nm->mkNode(ITE, equal_52, s, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_10, s, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_12, s, ite_90);
  Node ite_88 = nm->mkNode(ITE, equal_54, s, ite_89);
  Node ite_85 = nm->mkNode(ITE, equal_48, const_rational_15, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_10, s, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_12, const_rational_11, ite_84);
  Node ite_81 = nm->mkNode(ITE, equal_48, s, const_rational_15);
  Node ite_80 = nm->mkNode(ITE, equal_52, const_rational_14, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_10, s, ite_80);
  Node ite_77 = nm->mkNode(ITE, equal_50, const_rational_15, const_rational_15);
  Node ite_76 = nm->mkNode(ITE, equal_52, const_rational_15, ite_77);
  Node ite_72 = nm->mkNode(ITE, equal_75, ite_74, const_rational_15);
  Node ite_71 = nm->mkNode(ITE, equal_78, ite_76, ite_72);
  Node ite_70 = nm->mkNode(ITE, equal_82, ite_79, ite_71);
  Node ite_69 = nm->mkNode(ITE, equal_87, ite_83, ite_70);
  Node ite_68 = nm->mkNode(ITE, equal_93, ite_88, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_101, ite_95, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_107, ite_102, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_113, ite_109, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_117, ite_114, ite_65);
  Node ite_63 = nm->mkNode(ITE, geq_37, ite_119, ite_64);
  Node ite_62 = nm->mkNode(ITE, geq_139, ite_131, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_140, ite_30, ite_62);
  Node ite_60 = nm->mkNode(ITE, geq_40, ite_141, ite_61);
  Node mult_57 = nm->mkNode(MULT, t, mult_42);
  Node geq_58 = nm->mkNode(GEQ, s, mult_57);
  Node equal_56 = nm->mkNode(EQUAL, s, mult_57);
  Node mult_46 = nm->mkNode(MULT, t, const_rational_7);
  Node ite_29 = nm->mkNode(ITE, geq_45, plus_16, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_48, mult_46, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_50, plus_16, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_52, plus_16, ite_27);
  Node ite_25 = nm->mkNode(ITE, equal_10, s, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_12, mult_8, ite_25);
  Node ite_23 = nm->mkNode(ITE, equal_54, plus_16, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_56, plus_16, ite_23);
  Node ite_15 = nm->mkNode(ITE, geq_21, ite_17, plus_16);
  Node ite_14 = nm->mkNode(ITE, geq_58, ite_22, ite_15);
  Node ite_7 = nm->mkNode(ITE, equal_10, s, mult_8);
  Node ite_6 = nm->mkNode(ITE, equal_12, const_rational_11, ite_7);
  Node ite_5 = nm->mkNode(ITE, not_59, ite_14, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_41, ite_60, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_44, ite_196, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_45, plus_16, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_258, ite_207, ite_2);
  return ite_1;
}

// (define-fun int_bvor_4_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (+ s t) (ite (>= s t) t (ite (= t 2) (+ s t) (ite (= t 3) (ite (= s 1) (* s
// t) (+ s 1)) (ite (= t 4) (+ s t) (ite (= s 14) (+ s 1) (ite (= t 5) (ite (= s
// 1) (* s t) (ite (= s 2) (+ s t) (ite (= s 4) (+ s 1) (+ s 4)))) (ite (= t 6)
// (ite (= s 1) (+ s t) (ite (= s 5) (+ s 2) (ite (= s 2) (* s 3) (ite (= s 3)
// (+ s 4) (+ s 2))))) (ite (= t 7) (ite (= s 1) (* s t) (ite (= s 2) (+ s 5)
// (ite (= s 3) (+ s 4) (ite (= s 4) (+ s 3) (ite (= s 5) (+ s 2) (+ s 1))))))
// (ite (= t 8) (+ s t) (ite (= t 9) (ite (= s 1) (* s t) (ite (= s 2) (+ s t)
// (ite (= s 3) (+ s 8) (ite (= s 4) (+ s t) (ite (= s 5) (+ s 8) (ite (= s 6)
// (+ s t) (ite (= s 8) (+ s 1) (+ s 8)))))))) (ite (= t 10) (ite (= s 1) (+ s
// t) (ite (= s 2) (* s 5) (ite (= s 3) (+ s 8) (ite (= s 4) (+ s t) (ite (= s
// 5) (+ s t) (ite (= s 6) (+ s 8) (ite (= s 7) (+ s 8) (+ s 2)))))))) (ite (= t
// 11) (ite (= s 1) (* s t) (ite (= s 2) (+ s 9) (ite (= s 3) (+ s 8) (ite (= s
// 4) (+ s t) (ite (= s 5) (* s 3) (ite (= s 10) (+ s 1) (ite (= s 6) (+ s 9)
// (ite (= s 7) (+ s 8) (ite (= s 8) (+ s 3) (+ s 2)))))))))) (ite (= t 12) (ite
// (= s 1) (+ s t) (ite (= s 2) (+ s t) (ite (= s 3) (+ s t) (ite (= s 4) (* s
// 3) (ite (= s 5) (+ s 8) (ite (= s 6) (+ s 8) (ite (= s 7) (+ s 8) (+ s
// 4)))))))) (ite (= t 13) (ite (= s 1) (* s t) (ite (= s 2) (+ s t) (ite (= s
// 3) (* s 5) (ite (= s 4) (+ s 9) (ite (= s 5) (+ s 8) (ite (= s 6) (+ s 9)
// (ite (= s 7) (+ s 8) (ite (= s 8) (+ s 5) (ite (= s 9) (+ s 4) (ite (= s 10)
// (+ s 5) (ite (= s 11) (+ s 4) (+ s 1)))))))))))) (ite (= s 1) (* s 15) (ite
// (= s 2) t (ite (= s 3) (* s 5) (ite (= s 4) t (ite (= s 5) (* s 3) (ite (= s
// 6) t (ite (= s 7) (+ s 8) (ite (= s 8) t (ite (= s 9) (+ s 6) (ite (= s 10) t
// (ite (= s 11) (+ s 4) (ite (= s 13) (+ s 2) t))))))))))))))))))))))))))) (ite
// (= t 0) (+ s t) (ite (= t 1) (ite (= s 2) (+ s t) (ite (= s 3) (* s t) (ite
// (= s 4) (+ s t) (ite (= s 5) (* s t) (ite (= s 6) (+ s t) (ite (= s 7) (* s
// t) (ite (= s 8) (+ s t) (ite (= s 9) (* s t) (ite (= s 10) (+ s t) (ite (= s
// 11) (* s t) (ite (= s 12) (+ s t) (ite (= s 13) (* s t) (ite (= s 14) (+ s t)
// (* s t)))))))))))))) (ite (= t 2) (ite (= s 3) (+ t 1) (ite (= s 4) (+ s t)
// (ite (= s 5) (+ s t) (ite (= s 15) s (ite (= s 6) (* t 3) (ite (= s 7) s (ite
// (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) s (ite (= s 11) s (ite (=
// s 12) (+ s t) (ite (= s 13) (+ s t) s)))))))))))) (ite (= t 3) (ite (= s 4)
// (+ s t) (ite (= s 5) (+ s 2) (ite (= s 6) (+ s 1) (ite (= s 7) (+ t 4) (ite
// (= s 8) (+ s t) (ite (= s 9) (+ s 2) (ite (= s 10) (+ s 1) (ite (= s 11) s
// (ite (= s 12) (+ s t) (ite (= s 13) (+ s 2) (ite (= s 14) (+ s 1)
// s))))))))))) (ite (= t 4) (ite (= s 5) (+ t 1) (ite (= s 6) (+ t 2) (ite (= s
// 7) (+ t 3) (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) (+ s t)
// (ite (= s 11) (+ s t) (ite (= s 12) (* t 3) (ite (= s 13) s (ite (= s 14) s
// s)))))))))) (ite (= t 5) (ite (= s 6) (+ s 1) (ite (= s 7) (+ t 2) (ite (= s
// 8) (+ s t) (ite (= s 9) (+ s 4) (ite (= s 10) (+ s t) (ite (= s 11) (* t 3)
// (ite (= s 12) (+ s 1) (ite (= s 13) s (* t 3))))))))) (ite (= t 6) (ite (= s
// 7) (+ t 1) (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) (+ s 4)
// (ite (= s 11) (+ s 4) (ite (= s 12) (+ s 2) (ite (= s 13) (+ s 2) (ite (= s
// 15) s s)))))))) (ite (= t 7) (ite (= s 8) (+ s t) (ite (= s 9) (+ s 6) (ite
// (= s 10) (+ s 5) (ite (= s 11) (+ s 4) (ite (= s 12) (+ s 3) (ite (= s 13) (+
// s 2) (ite (= s 14) (+ s 1) s))))))) (ite (= t 8) (ite (= s 9) (+ t 1) (ite (=
// s 10) (+ t 2) (ite (= s 11) (+ t 3) (ite (= s 12) (+ t 4) (ite (= s 13) s
// (ite (= s 15) s s)))))) (ite (= t 9) (ite (= s 10) (+ s 1) (ite (= s 11) (+ t
// 2) (ite (= s 12) (+ s 1) (ite (= s 13) (+ t 4) (ite (= s 15) s (+ s 1))))))
// (ite (= t 10) (ite (= s 11) (+ t 1) (ite (= s 12) (+ s 2) (ite (= s 13) (+ s
// 2) (ite (= s 14) (+ t 4) s)))) (ite (= t 11) (+ t 4) (ite (= t 12) (ite (= s
// 13) (+ t 1) (ite (= s 15) (+ t 3) (+ t 2))) (ite (= t 13) (+ t 2) (+ t
// 1)))))))))))))))))
Node int_bvor_4_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_245 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_244 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_77 = nm->mkNode(PLUS, s, t);
  Node geq_243 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_137 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_123 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_187 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_151 = nm->mkNode(MULT, s, t);
  Node plus_51 = nm->mkNode(PLUS, s, const_rational_1);
  Node ite_242 = nm->mkNode(ITE, equal_187, mult_151, plus_51);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_112 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_39 = nm->mkNode(EQUAL, s, const_rational_14);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_100 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_152 = nm->mkNode(EQUAL, s, const_rational_2);
  Node equal_122 = nm->mkNode(EQUAL, s, const_rational_4);
  Node plus_72 = nm->mkNode(PLUS, s, const_rational_4);
  Node ite_241 = nm->mkNode(ITE, equal_122, plus_51, plus_72);
  Node ite_240 = nm->mkNode(ITE, equal_152, plus_77, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_187, mult_151, ite_240);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_89 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_111 = nm->mkNode(EQUAL, s, const_rational_5);
  Node plus_41 = nm->mkNode(PLUS, s, const_rational_2);
  Node mult_184 = nm->mkNode(MULT, s, const_rational_3);
  Node equal_136 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_238 = nm->mkNode(ITE, equal_136, plus_72, plus_41);
  Node ite_237 = nm->mkNode(ITE, equal_152, mult_184, ite_238);
  Node ite_236 = nm->mkNode(ITE, equal_111, plus_41, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_187, plus_77, ite_236);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_79 = nm->mkNode(EQUAL, t, const_rational_7);
  Node plus_73 = nm->mkNode(PLUS, s, const_rational_5);
  Node plus_71 = nm->mkNode(PLUS, s, const_rational_3);
  Node ite_234 = nm->mkNode(ITE, equal_111, plus_41, plus_51);
  Node ite_233 = nm->mkNode(ITE, equal_122, plus_71, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_136, plus_72, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_152, plus_73, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_187, mult_151, ite_231);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_62 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_53 = nm->mkNode(EQUAL, t, const_rational_9);
  Node plus_183 = nm->mkNode(PLUS, s, const_rational_8);
  Node equal_99 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_78 = nm->mkNode(EQUAL, s, const_rational_8);
  Node ite_229 = nm->mkNode(ITE, equal_78, plus_51, plus_183);
  Node ite_228 = nm->mkNode(ITE, equal_99, plus_77, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_111, plus_183, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_122, plus_77, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_136, plus_183, ite_226);
  Node ite_224 = nm->mkNode(ITE, equal_152, plus_77, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_187, mult_151, ite_224);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_44 = nm->mkNode(EQUAL, t, const_rational_10);
  Node mult_185 = nm->mkNode(MULT, s, const_rational_5);
  Node equal_88 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_222 = nm->mkNode(ITE, equal_88, plus_183, plus_41);
  Node ite_221 = nm->mkNode(ITE, equal_99, plus_183, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_111, plus_77, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_122, plus_77, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_136, plus_183, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_152, mult_185, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_187, plus_77, ite_217);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_33 = nm->mkNode(EQUAL, t, const_rational_11);
  Node plus_199 = nm->mkNode(PLUS, s, const_rational_9);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_10);
  Node ite_215 = nm->mkNode(ITE, equal_78, plus_71, plus_41);
  Node ite_214 = nm->mkNode(ITE, equal_88, plus_183, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_99, plus_199, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_52, plus_51, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_111, mult_184, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_122, plus_77, ite_211);
  Node ite_209 = nm->mkNode(ITE, equal_136, plus_183, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_152, plus_199, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_187, mult_151, ite_208);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_29 = nm->mkNode(EQUAL, t, const_rational_12);
  Node ite_206 = nm->mkNode(ITE, equal_88, plus_183, plus_72);
  Node ite_205 = nm->mkNode(ITE, equal_99, plus_183, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_111, plus_183, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_122, mult_184, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_136, plus_77, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_152, plus_77, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_187, plus_77, ite_201);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_20 = nm->mkNode(EQUAL, t, const_rational_13);
  Node equal_61 = nm->mkNode(EQUAL, s, const_rational_9);
  Node equal_43 = nm->mkNode(EQUAL, s, const_rational_11);
  Node ite_198 = nm->mkNode(ITE, equal_43, plus_72, plus_51);
  Node ite_197 = nm->mkNode(ITE, equal_52, plus_73, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_61, plus_72, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_78, plus_73, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_88, plus_183, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_99, plus_199, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_111, plus_183, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_122, plus_199, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_136, mult_185, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_152, plus_77, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_187, mult_151, ite_189);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node mult_186 = nm->mkNode(MULT, s, const_rational_15);
  Node plus_75 = nm->mkNode(PLUS, s, const_rational_6);
  Node equal_28 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_182 = nm->mkNode(ITE, equal_28, plus_41, t);
  Node ite_181 = nm->mkNode(ITE, equal_43, plus_72, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_52, t, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_61, plus_75, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_78, t, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_88, plus_183, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_99, t, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_111, mult_184, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_122, t, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_136, mult_185, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_152, t, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_187, mult_186, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_20, ite_188, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_29, ite_200, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_33, ite_207, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_44, ite_216, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_53, ite_223, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_62, plus_77, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_79, ite_230, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_89, ite_235, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_100, ite_239, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_39, plus_51, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_112, plus_77, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_123, ite_242, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_137, plus_77, ite_159);
  Node ite_157 = nm->mkNode(ITE, geq_243, t, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_244, plus_77, ite_157);
  Node equal_154 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_153 = nm->mkNode(EQUAL, t, const_rational_1);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_12);
  Node ite_150 = nm->mkNode(ITE, equal_39, plus_77, mult_151);
  Node ite_149 = nm->mkNode(ITE, equal_28, mult_151, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_42, plus_77, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_43, mult_151, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_52, plus_77, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_61, mult_151, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_78, plus_77, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_88, mult_151, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_99, plus_77, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_111, mult_151, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_122, plus_77, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_136, mult_151, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_152, plus_77, ite_139);
  Node plus_16 = nm->mkNode(PLUS, t, const_rational_1);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_15);
  Node mult_98 = nm->mkNode(MULT, t, const_rational_3);
  Node ite_135 = nm->mkNode(ITE, equal_28, plus_77, s);
  Node ite_134 = nm->mkNode(ITE, equal_42, plus_77, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_43, s, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_52, s, ite_133);
  Node ite_131 = nm->mkNode(ITE, equal_61, plus_77, ite_132);
  Node ite_130 = nm->mkNode(ITE, equal_78, plus_77, ite_131);
  Node ite_129 = nm->mkNode(ITE, equal_88, s, ite_130);
  Node ite_128 = nm->mkNode(ITE, equal_99, mult_98, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_26, s, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_111, plus_77, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_122, plus_77, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_136, plus_16, ite_125);
  Node plus_31 = nm->mkNode(PLUS, t, const_rational_4);
  Node ite_70 = nm->mkNode(ITE, equal_39, plus_51, s);
  Node ite_69 = nm->mkNode(ITE, equal_28, plus_41, ite_70);
  Node ite_121 = nm->mkNode(ITE, equal_42, plus_77, ite_69);
  Node ite_120 = nm->mkNode(ITE, equal_43, s, ite_121);
  Node ite_119 = nm->mkNode(ITE, equal_52, plus_51, ite_120);
  Node ite_118 = nm->mkNode(ITE, equal_61, plus_41, ite_119);
  Node ite_117 = nm->mkNode(ITE, equal_78, plus_77, ite_118);
  Node ite_116 = nm->mkNode(ITE, equal_88, plus_31, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_99, plus_51, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_111, plus_41, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_122, plus_77, ite_114);
  Node plus_18 = nm->mkNode(PLUS, t, const_rational_2);
  Node plus_24 = nm->mkNode(PLUS, t, const_rational_3);
  Node ite_110 = nm->mkNode(ITE, equal_39, s, s);
  Node ite_109 = nm->mkNode(ITE, equal_28, s, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_42, mult_98, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_43, plus_77, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_52, plus_77, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_61, plus_77, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_78, plus_77, ite_105);
  Node ite_103 = nm->mkNode(ITE, equal_88, plus_24, ite_104);
  Node ite_102 = nm->mkNode(ITE, equal_99, plus_18, ite_103);
  Node ite_101 = nm->mkNode(ITE, equal_111, plus_16, ite_102);
  Node ite_97 = nm->mkNode(ITE, equal_28, s, mult_98);
  Node ite_96 = nm->mkNode(ITE, equal_42, plus_51, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_43, mult_98, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_52, plus_77, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_61, plus_72, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_78, plus_77, ite_93);
  Node ite_91 = nm->mkNode(ITE, equal_88, plus_18, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_99, plus_51, ite_91);
  Node ite_60 = nm->mkNode(ITE, equal_26, s, s);
  Node ite_87 = nm->mkNode(ITE, equal_28, plus_41, ite_60);
  Node ite_86 = nm->mkNode(ITE, equal_42, plus_41, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_43, plus_72, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_52, plus_72, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_61, plus_77, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_78, plus_77, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_88, plus_16, ite_82);
  Node ite_68 = nm->mkNode(ITE, equal_42, plus_71, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_43, plus_72, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_52, plus_73, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_61, plus_75, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_78, plus_77, ite_65);
  Node ite_59 = nm->mkNode(ITE, equal_28, s, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_42, plus_31, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_43, plus_24, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_52, plus_18, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_61, plus_16, ite_56);
  Node ite_50 = nm->mkNode(ITE, equal_26, s, plus_51);
  Node ite_49 = nm->mkNode(ITE, equal_28, plus_31, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_42, plus_51, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_43, plus_18, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_52, plus_51, ite_47);
  Node ite_38 = nm->mkNode(ITE, equal_39, plus_31, s);
  Node ite_37 = nm->mkNode(ITE, equal_28, plus_41, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_42, plus_41, ite_37);
  Node ite_35 = nm->mkNode(ITE, equal_43, plus_16, ite_36);
  Node ite_23 = nm->mkNode(ITE, equal_26, plus_24, plus_18);
  Node ite_22 = nm->mkNode(ITE, equal_28, plus_16, ite_23);
  Node ite_15 = nm->mkNode(ITE, equal_20, plus_18, plus_16);
  Node ite_14 = nm->mkNode(ITE, equal_29, ite_22, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_33, plus_31, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_44, ite_35, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_53, ite_46, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_62, ite_55, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_79, ite_64, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_89, ite_81, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_100, ite_90, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_112, ite_101, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_123, ite_113, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_137, ite_124, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_153, ite_138, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_154, plus_77, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_245, ite_156, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_1_lia ((s Int) (t Int)) Int (ite (= s t) 0 1))
Node int_bvxor_1_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_4 = nm->mkNode(EQUAL, s, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_1 = nm->mkNode(ITE, equal_4, const_rational_0, const_rational_1);
  return ite_1;
}

// (define-fun int_bvxor_1_nia ((s Int) (t Int)) Int (ite (= s t) 0 1))
Node int_bvxor_1_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_4 = nm->mkNode(EQUAL, s, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_1 = nm->mkNode(ITE, equal_4, const_rational_0, const_rational_1);
  return ite_1;
}

// (define-fun int_bvxor_2_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (ite (= s t) 0 t) (ite (>= s t) 0 (ite (= t 2) (* s 3) (ite (= s 1) (* s 2)
// 1)))) (ite (= t 0) (ite (= s 1) (* s s) (ite (= s 2) s s)) (ite (= t 1) (ite
// (= s 3) (* t 2) (* t 3)) 1))))
Node int_bvxor_2_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_30 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_29 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_28 = nm->mkNode(EQUAL, s, t);
  Node ite_27 = nm->mkNode(ITE, equal_28, const_rational_0, t);
  Node geq_26 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_25 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node mult_24 = nm->mkNode(MULT, s, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_16 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_23 = nm->mkNode(MULT, s, const_rational_2);
  Node ite_22 = nm->mkNode(ITE, equal_16, mult_23, const_rational_1);
  Node ite_21 = nm->mkNode(ITE, equal_25, mult_24, ite_22);
  Node ite_20 = nm->mkNode(ITE, geq_26, const_rational_0, ite_21);
  Node ite_19 = nm->mkNode(ITE, equal_29, ite_27, ite_20);
  Node equal_17 = nm->mkNode(EQUAL, t, const_rational_0);
  Node mult_15 = nm->mkNode(MULT, s, s);
  Node equal_14 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_13 = nm->mkNode(ITE, equal_14, s, s);
  Node ite_12 = nm->mkNode(ITE, equal_16, mult_15, ite_13);
  Node equal_11 = nm->mkNode(EQUAL, t, const_rational_1);
  Node equal_10 = nm->mkNode(EQUAL, s, const_rational_3);
  Node mult_8 = nm->mkNode(MULT, t, const_rational_2);
  Node mult_6 = nm->mkNode(MULT, t, const_rational_3);
  Node ite_5 = nm->mkNode(ITE, equal_10, mult_8, mult_6);
  Node ite_3 = nm->mkNode(ITE, equal_11, ite_5, const_rational_1);
  Node ite_2 = nm->mkNode(ITE, equal_17, ite_12, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_30, ite_19, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_2_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= 0 s)
// (+ s t) (ite (>= s t) (ite (= 0 s) t 0) (ite (= t 2) (+ s t) (ite (= s 1) (+
// s s) 1)))) (ite (= 0 t) (+ s t) (ite (= t 1) (ite (= s 2) (+ s t) (+ t t))
// 1))))
Node int_bvxor_2_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_23 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_21 = nm->mkNode(EQUAL, const_rational_0, s);
  Node plus_7 = nm->mkNode(PLUS, s, t);
  Node geq_22 = nm->mkNode(GEQ, s, t);
  Node ite_20 = nm->mkNode(ITE, equal_21, t, const_rational_0);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_19 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_1);
  Node plus_17 = nm->mkNode(PLUS, s, s);
  Node ite_16 = nm->mkNode(ITE, equal_18, plus_17, const_rational_1);
  Node ite_15 = nm->mkNode(ITE, equal_19, plus_7, ite_16);
  Node ite_14 = nm->mkNode(ITE, geq_22, ite_20, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_21, plus_7, ite_14);
  Node equal_11 = nm->mkNode(EQUAL, const_rational_0, t);
  Node equal_10 = nm->mkNode(EQUAL, t, const_rational_1);
  Node equal_8 = nm->mkNode(EQUAL, s, const_rational_2);
  Node plus_6 = nm->mkNode(PLUS, t, t);
  Node ite_5 = nm->mkNode(ITE, equal_8, plus_7, plus_6);
  Node ite_3 = nm->mkNode(ITE, equal_10, ite_5, const_rational_1);
  Node ite_2 = nm->mkNode(ITE, equal_11, plus_7, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_23, ite_13, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_3_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (ite (= s t) 0 t) (ite (>= s t) 0 (ite (= t 2) (* s 3) (ite (= t 3) (ite (= s
// 2) 1 (* s 2)) (ite (= t 4) (ite (= s 1) (* s 5) (ite (= s 2) (* s 3) 7)) (ite
// (= t 5) (ite (= s 1) (* s 4) (ite (= s 2) 7 (ite (= s 3) (* s 2) 1))) (ite (=
// t 6) (ite (= s 1) (* s 7) (ite (= s 2) (* s s) (ite (= s 5) 3 (ite (= s 4) 2
// 5)))) (ite (= s 6) 1 (ite (= s 1) (* s 6) (ite (= s 2) 5 (ite (= s 3) 4 (ite
// (= s 4) 3 2)))))))))))) (ite (= t 0) s (ite (= t 1) (ite (= s 7) (* t 6) (ite
// (= s 6) (* t 7) (ite (= s 2) (* t 3) (ite (= s 3) (* t 2) (ite (= s 4) (* t
// 5) (* t 4)))))) (ite (= t 2) (ite (= s 3) 1 (ite (= s 4) (* t 3) (ite (= s 5)
// 7 (ite (= s 7) 5 (* t t))))) (ite (= t 3) (ite (= s 4) 7 (ite (= s 5) (* t 2)
// (ite (= s 6) 5 4))) (ite (= t 4) (ite (= s 5) 1 (ite (= s 6) 2 3)) (ite (= t
// 5) (ite (= s 6) 3 2) 1))))))))
Node int_bvxor_3_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_85 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_84 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_83 = nm->mkNode(EQUAL, s, t);
  Node ite_82 = nm->mkNode(ITE, equal_83, const_rational_0, t);
  Node geq_81 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_36 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node mult_78 = nm->mkNode(MULT, s, const_rational_3);
  Node equal_27 = nm->mkNode(EQUAL, t, const_rational_3);
  Node equal_44 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node mult_74 = nm->mkNode(MULT, s, const_rational_2);
  Node ite_80 = nm->mkNode(ITE, equal_44, const_rational_1, mult_74);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_19 = nm->mkNode(EQUAL, t, const_rational_4);
  Node equal_63 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node mult_79 = nm->mkNode(MULT, s, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node ite_77 = nm->mkNode(ITE, equal_44, mult_78, const_rational_7);
  Node ite_76 = nm->mkNode(ITE, equal_63, mult_79, ite_77);
  Node equal_14 = nm->mkNode(EQUAL, t, const_rational_5);
  Node mult_75 = nm->mkNode(MULT, s, const_rational_4);
  Node equal_35 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_73 = nm->mkNode(ITE, equal_35, mult_74, const_rational_1);
  Node ite_72 = nm->mkNode(ITE, equal_44, const_rational_7, ite_73);
  Node ite_71 = nm->mkNode(ITE, equal_63, mult_75, ite_72);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_70 = nm->mkNode(EQUAL, t, const_rational_6);
  Node mult_69 = nm->mkNode(MULT, s, const_rational_7);
  Node mult_68 = nm->mkNode(MULT, s, s);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_5);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_67 = nm->mkNode(ITE, equal_26, const_rational_2, const_rational_5);
  Node ite_66 = nm->mkNode(ITE, equal_18, const_rational_3, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_44, mult_68, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_63, mult_69, ite_65);
  Node equal_12 = nm->mkNode(EQUAL, s, const_rational_6);
  Node mult_62 = nm->mkNode(MULT, s, const_rational_6);
  Node ite_61 = nm->mkNode(ITE, equal_26, const_rational_3, const_rational_2);
  Node ite_60 = nm->mkNode(ITE, equal_35, const_rational_4, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_44, const_rational_5, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_63, mult_62, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_12, const_rational_1, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_70, ite_64, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_14, ite_71, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_19, ite_76, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_27, ite_80, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_36, mult_78, ite_53);
  Node ite_51 = nm->mkNode(ITE, geq_81, const_rational_0, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_84, ite_82, ite_51);
  Node equal_48 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_47 = nm->mkNode(EQUAL, t, const_rational_1);
  Node equal_33 = nm->mkNode(EQUAL, s, const_rational_7);
  Node mult_46 = nm->mkNode(MULT, t, const_rational_6);
  Node mult_45 = nm->mkNode(MULT, t, const_rational_7);
  Node mult_34 = nm->mkNode(MULT, t, const_rational_3);
  Node mult_24 = nm->mkNode(MULT, t, const_rational_2);
  Node mult_43 = nm->mkNode(MULT, t, const_rational_5);
  Node mult_42 = nm->mkNode(MULT, t, const_rational_4);
  Node ite_41 = nm->mkNode(ITE, equal_26, mult_43, mult_42);
  Node ite_40 = nm->mkNode(ITE, equal_35, mult_24, ite_41);
  Node ite_39 = nm->mkNode(ITE, equal_44, mult_34, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_12, mult_45, ite_39);
  Node ite_37 = nm->mkNode(ITE, equal_33, mult_46, ite_38);
  Node mult_32 = nm->mkNode(MULT, t, t);
  Node ite_31 = nm->mkNode(ITE, equal_33, const_rational_5, mult_32);
  Node ite_30 = nm->mkNode(ITE, equal_18, const_rational_7, ite_31);
  Node ite_29 = nm->mkNode(ITE, equal_26, mult_34, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_35, const_rational_1, ite_29);
  Node ite_23 = nm->mkNode(ITE, equal_12, const_rational_5, const_rational_4);
  Node ite_22 = nm->mkNode(ITE, equal_18, mult_24, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_26, const_rational_7, ite_22);
  Node ite_17 = nm->mkNode(ITE, equal_12, const_rational_2, const_rational_3);
  Node ite_16 = nm->mkNode(ITE, equal_18, const_rational_1, ite_17);
  Node ite_9 = nm->mkNode(ITE, equal_12, const_rational_3, const_rational_2);
  Node ite_7 = nm->mkNode(ITE, equal_14, ite_9, const_rational_1);
  Node ite_6 = nm->mkNode(ITE, equal_19, ite_16, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_27, ite_21, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_36, ite_28, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_47, ite_37, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_48, s, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_85, ite_50, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_3_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (+ s t) (ite (>= s t) 0 (ite (= t 2) (+ s t) (ite (= t 3) (ite (= s 1) (+ s
// s) 1) (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 4) 1 (ite (= s 1) (* s 4)
// (ite (= s 2) (+ s t) (+ s s)))) (ite (= t 6) (ite (= s 1) (+ s t) (ite (= s
// 2) (* s s) (ite (= s 5) 3 (ite (= s 4) 2 (+ s 2))))) (ite (= s 1) (* s 6)
// (ite (= s 6) 1 (ite (= s 2) (+ s 3) (ite (= s 3) (+ s 1) (ite (= s 4) 3
// 2)))))))))))) (ite (= t 0) (+ s t) (ite (= t 1) (ite (= s 2) (+ s t) (ite (=
// s 3) (+ t t) (ite (= s 4) (+ s t) (ite (= s 5) 4 (ite (= s 7) 6 (+ s t))))))
// (ite (= t 2) (ite (= s 3) 1 (ite (= s 4) (+ s t) (ite (= s 5) (+ s t) (ite (=
// s 6) (* t t) 5)))) (ite (= s 7) (ite (= t 6) 1 (ite (= t 3) (+ t 1) (ite (= t
// 4) 3 2))) (ite (= t 3) (ite (= s 4) (+ s t) (ite (= s 5) (+ t t) 5)) (ite (=
// t 4) (ite (= s 5) 1 2) 3))))))))
Node int_bvxor_3_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_78 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_77 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_19 = nm->mkNode(PLUS, s, t);
  Node geq_76 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_37 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_21 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_62 = nm->mkNode(EQUAL, s, const_rational_1);
  Node plus_72 = nm->mkNode(PLUS, s, s);
  Node ite_75 = nm->mkNode(ITE, equal_62, plus_72, const_rational_1);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_14 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_4);
  Node mult_73 = nm->mkNode(MULT, s, const_rational_4);
  Node equal_43 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_71 = nm->mkNode(ITE, equal_43, plus_19, plus_72);
  Node ite_70 = nm->mkNode(ITE, equal_62, mult_73, ite_71);
  Node ite_69 = nm->mkNode(ITE, equal_20, const_rational_1, ite_70);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_26 = nm->mkNode(EQUAL, t, const_rational_6);
  Node mult_68 = nm->mkNode(MULT, s, s);
  Node equal_12 = nm->mkNode(EQUAL, s, const_rational_5);
  Node plus_67 = nm->mkNode(PLUS, s, const_rational_2);
  Node ite_66 = nm->mkNode(ITE, equal_20, const_rational_2, plus_67);
  Node ite_65 = nm->mkNode(ITE, equal_12, const_rational_3, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_43, mult_68, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_62, plus_19, ite_64);
  Node mult_61 = nm->mkNode(MULT, s, const_rational_6);
  Node equal_35 = nm->mkNode(EQUAL, s, const_rational_6);
  Node plus_60 = nm->mkNode(PLUS, s, const_rational_3);
  Node equal_36 = nm->mkNode(EQUAL, s, const_rational_3);
  Node plus_59 = nm->mkNode(PLUS, s, const_rational_1);
  Node ite_58 = nm->mkNode(ITE, equal_20, const_rational_3, const_rational_2);
  Node ite_57 = nm->mkNode(ITE, equal_36, plus_59, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_43, plus_60, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_35, const_rational_1, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_62, mult_61, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_26, ite_63, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_74, ite_69, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_14, plus_19, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_21, ite_75, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_37, plus_19, ite_50);
  Node ite_48 = nm->mkNode(ITE, geq_76, const_rational_0, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_77, plus_19, ite_48);
  Node equal_45 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_44 = nm->mkNode(EQUAL, t, const_rational_1);
  Node plus_18 = nm->mkNode(PLUS, t, t);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_28 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_42 = nm->mkNode(ITE, equal_28, const_rational_6, plus_19);
  Node ite_41 = nm->mkNode(ITE, equal_12, const_rational_4, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_20, plus_19, ite_41);
  Node ite_39 = nm->mkNode(ITE, equal_36, plus_18, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_43, plus_19, ite_39);
  Node mult_34 = nm->mkNode(MULT, t, t);
  Node ite_33 = nm->mkNode(ITE, equal_35, mult_34, const_rational_5);
  Node ite_32 = nm->mkNode(ITE, equal_12, plus_19, ite_33);
  Node ite_31 = nm->mkNode(ITE, equal_20, plus_19, ite_32);
  Node ite_30 = nm->mkNode(ITE, equal_36, const_rational_1, ite_31);
  Node plus_25 = nm->mkNode(PLUS, t, const_rational_1);
  Node ite_24 = nm->mkNode(ITE, equal_14, const_rational_3, const_rational_2);
  Node ite_23 = nm->mkNode(ITE, equal_21, plus_25, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_26, const_rational_1, ite_23);
  Node ite_17 = nm->mkNode(ITE, equal_12, plus_18, const_rational_5);
  Node ite_16 = nm->mkNode(ITE, equal_20, plus_19, ite_17);
  Node ite_9 = nm->mkNode(ITE, equal_12, const_rational_1, const_rational_2);
  Node ite_7 = nm->mkNode(ITE, equal_14, ite_9, const_rational_3);
  Node ite_6 = nm->mkNode(ITE, equal_21, ite_16, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_28, ite_22, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_37, ite_30, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_44, ite_38, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_45, plus_19, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_78, ite_47, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_4_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// t (ite (>= s t) 0 (ite (= t 2) (* s 3) (ite (= t 3) (ite (= s 2) 1 (* s 2))
// (ite (= t 4) (ite (= s 1) (* s 5) (ite (= s 2) (* s 3) 7)) (ite (= t 5) (ite
// (= s 1) (* s 4) (ite (= s 2) 7 (ite (= s 3) (* s 2) 1))) (ite (= t 6) (ite (=
// s 1) (* s 7) (ite (= s 2) (* s s) (ite (= s 5) 3 (ite (= s 3) 5 2)))) (ite (=
// t 7) (ite (= s 1) (* s 6) (ite (= s 2) 5 (ite (= s 3) 4 (ite (= s 6) 1 (ite
// (= s 4) 3 2))))) (ite (= t 8) (ite (= s 1) (* s 9) (ite (= s 2) (* s 5) (ite
// (= s 3) 11 (ite (= s 4) (* s 3) (ite (= s 5) 13 (ite (= s 6) 14 15)))))) (ite
// (= t 9) (ite (= s 1) (* s 8) (ite (= s 2) 11 (ite (= s 3) 10 (ite (= s 4) 13
// (ite (= s 5) 12 (ite (= s 6) 15 (ite (= s 7) (* s 2) 1))))))) (ite (= t 10)
// (ite (= s 1) (* s 11) (ite (= s 2) (* s 4) (ite (= s 3) (* s s) (ite (= s 4)
// 14 (ite (= s 5) (* s 3) (ite (= s 6) (* s 2) (ite (= s 7) 13 (ite (= s 8) 2
// 3)))))))) (ite (= t 11) (ite (= s 1) (* s 10) (ite (= s 2) 9 (ite (= s 3) 8
// (ite (= s 4) 15 (ite (= s 5) 14 (ite (= s 6) 13 (ite (= s 7) 12 (ite (= s 8)
// 3 (ite (= s 10) 1 2))))))))) (ite (= t 12) (ite (= s 1) (* s 13) (ite (= s 2)
// (* s 7) (ite (= s 3) (* s 5) (ite (= s 4) (* s 2) (ite (= s 5) 9 (ite (= s 6)
// 10 (ite (= s 7) 11 (ite (= s 8) 4 (ite (= s 9) 5 (ite (= s 10) 6 7))))))))))
// (ite (= t 13) (ite (= s 1) (* s 12) (ite (= s 2) 15 (ite (= s 3) 14 (ite (= s
// 4) 9 (ite (= s 5) 8 (ite (= s 6) 11 (ite (= s 7) 10 (ite (= s 8) 5 (ite (= s
// 9) 4 (ite (= s 10) 7 (ite (= s 12) 1 6))))))))))) (ite (= t 14) (ite (= s 1)
// (* s 15) (ite (= s 2) (* s 6) (ite (= s 3) 13 (ite (= s 4) 10 (ite (= s 5) 11
// (ite (= s 6) 8 (ite (= s 7) 9 (ite (= s 8) 6 (ite (= s 9) 7 (ite (= s 10) 4
// (ite (= s 11) 5 (ite (= s 13) 3 2)))))))))))) (ite (= s 1) (* s 14) (ite (= s
// 2) 13 (ite (= s 3) (* s 4) (ite (= s 4) 11 (ite (= s 5) (* s 2) (ite (= s 6)
// 9 (ite (= s 7) 8 (ite (= s 8) 7 (ite (= s 9) 6 (ite (= s 10) 5 (ite (= s 11)
// 4 (ite (= s 12) 3 (ite (= s 13) 2 1)))))))))))))))))))))))))))) (ite (= t 0)
// (ite (= s 1) (* s s) (ite (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite (= s
// 5) s (ite (= s 6) s (ite (= s 7) s (ite (= s 8) s (ite (= s 9) s (ite (= s
// 10) s (ite (= s 11) s (ite (= s 12) s (ite (= s 13) s (ite (= s 15) s
// s)))))))))))))) (ite (= t 1) (ite (= s 2) (* t 3) (ite (= s 3) (* t 2) (ite
// (= s 4) (* t 5) (ite (= s 5) (* t 4) (ite (= s 6) (* t 7) (ite (= s 7) (* t
// 6) (ite (= s 8) (* t 9) (ite (= s 9) (* t 8) (ite (= s 10) (* t 11) (ite (= s
// 11) (* t 10) (ite (= s 12) (* t 13) (ite (= s 13) (* t 12) (ite (= s 15) (* t
// 14) (* t 15)))))))))))))) (ite (= t 2) (ite (= s 3) 1 (ite (= s 4) (* t 3)
// (ite (= s 5) 7 (ite (= s 6) (* t t) (ite (= s 7) 5 (ite (= s 8) (* t 5) (ite
// (= s 9) 11 (ite (= s 10) (* t 4) (ite (= s 11) 9 (ite (= s 12) (* t 7) (ite
// (= s 13) 15 (ite (= s 14) (* t 6) 13)))))))))))) (ite (= t 3) (ite (= s 4) 7
// (ite (= s 5) (* t 2) (ite (= s 6) 5 (ite (= s 7) 4 (ite (= s 8) 11 (ite (= s
// 9) 10 (ite (= s 10) (* t t) (ite (= s 11) 8 (ite (= s 12) (* t 5) (ite (= s
// 15) (* t 4) (ite (= s 13) 14 13))))))))))) (ite (= t 4) (ite (= s 5) 1 (ite
// (= s 6) 2 (ite (= s 7) 3 (ite (= s 8) (* t 3) (ite (= s 9) 13 (ite (= s 10)
// 14 (ite (= s 11) 15 (ite (= s 12) (* t 2) (ite (= s 13) 9 (ite (= s 14) 10
// 11)))))))))) (ite (= t 5) (ite (= s 6) 3 (ite (= s 7) 2 (ite (= s 8) 13 (ite
// (= s 9) 12 (ite (= s 10) (* t 3) (ite (= s 11) 14 (ite (= s 12) 9 (ite (= s
// 15) (* t 2) (ite (= s 14) 11 8))))))))) (ite (= t 6) (ite (= s 15) 9 (ite (=
// s 7) 1 (ite (= s 8) 14 (ite (= s 9) 15 (ite (= s 14) 8 (ite (= s 10) (* t 2)
// (ite (= s 13) 11 (ite (= s 11) 13 10)))))))) (ite (= t 7) (ite (= s 8) 15
// (ite (= s 9) (* t 2) (ite (= s 10) 13 (ite (= s 15) 8 (ite (= s 11) 12 (ite
// (= s 12) 11 (ite (= s 13) 10 9))))))) (ite (= t 8) (ite (= s 15) 7 (ite (= s
// 9) 1 (ite (= s 14) 6 (ite (= s 10) 2 (ite (= s 11) 3 (ite (= s 12) 4 5))))))
// (ite (= t 9) (ite (= s 10) 3 (ite (= s 11) 2 (ite (= s 12) 5 (ite (= s 13) 4
// (ite (= s 14) 7 6))))) (ite (= t 10) (ite (= s 11) 1 (ite (= s 12) 6 (ite (=
// s 13) 7 (ite (= s 15) 5 4)))) (ite (= t 11) (ite (= s 12) 7 (ite (= s 13) 6
// (ite (= s 15) 4 5))) (ite (= t 12) (ite (= s 15) 3 (ite (= s 13) 1 2)) (ite
// (= t 13) (ite (= s 14) 3 2) 1))))))))))))))))
Node int_bvxor_4_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_305 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_304 = nm->mkNode(EQUAL, s, const_rational_0);
  Node geq_303 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_140 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node mult_271 = nm->mkNode(MULT, s, const_rational_3);
  Node equal_124 = nm->mkNode(EQUAL, t, const_rational_3);
  Node equal_162 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node mult_210 = nm->mkNode(MULT, s, const_rational_2);
  Node ite_302 = nm->mkNode(ITE, equal_162, const_rational_1, mult_210);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_108 = nm->mkNode(EQUAL, t, const_rational_4);
  Node equal_179 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node mult_250 = nm->mkNode(MULT, s, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node ite_301 = nm->mkNode(ITE, equal_162, mult_271, const_rational_7);
  Node ite_300 = nm->mkNode(ITE, equal_179, mult_250, ite_301);
  Node equal_96 = nm->mkNode(EQUAL, t, const_rational_5);
  Node mult_211 = nm->mkNode(MULT, s, const_rational_4);
  Node equal_139 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_299 = nm->mkNode(ITE, equal_139, mult_210, const_rational_1);
  Node ite_298 = nm->mkNode(ITE, equal_162, const_rational_7, ite_299);
  Node ite_297 = nm->mkNode(ITE, equal_179, mult_211, ite_298);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_84 = nm->mkNode(EQUAL, t, const_rational_6);
  Node mult_251 = nm->mkNode(MULT, s, const_rational_7);
  Node mult_178 = nm->mkNode(MULT, s, s);
  Node equal_107 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_296 = nm->mkNode(ITE, equal_139, const_rational_5, const_rational_2);
  Node ite_295 = nm->mkNode(ITE, equal_107, const_rational_3, ite_296);
  Node ite_294 = nm->mkNode(ITE, equal_162, mult_178, ite_295);
  Node ite_293 = nm->mkNode(ITE, equal_179, mult_251, ite_294);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_7);
  Node mult_225 = nm->mkNode(MULT, s, const_rational_6);
  Node equal_95 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_123 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_292 = nm->mkNode(ITE, equal_123, const_rational_3, const_rational_2);
  Node ite_291 = nm->mkNode(ITE, equal_95, const_rational_1, ite_292);
  Node ite_290 = nm->mkNode(ITE, equal_139, const_rational_4, ite_291);
  Node ite_289 = nm->mkNode(ITE, equal_162, const_rational_5, ite_290);
  Node ite_288 = nm->mkNode(ITE, equal_179, mult_225, ite_289);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_63 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node mult_287 = nm->mkNode(MULT, s, const_rational_9);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node ite_286 =
      nm->mkNode(ITE, equal_95, const_rational_14, const_rational_15);
  Node ite_285 = nm->mkNode(ITE, equal_107, const_rational_13, ite_286);
  Node ite_284 = nm->mkNode(ITE, equal_123, mult_271, ite_285);
  Node ite_283 = nm->mkNode(ITE, equal_139, const_rational_11, ite_284);
  Node ite_282 = nm->mkNode(ITE, equal_162, mult_250, ite_283);
  Node ite_281 = nm->mkNode(ITE, equal_179, mult_287, ite_282);
  Node equal_54 = nm->mkNode(EQUAL, t, const_rational_9);
  Node mult_280 = nm->mkNode(MULT, s, const_rational_8);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_83 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_279 = nm->mkNode(ITE, equal_83, mult_210, const_rational_1);
  Node ite_278 = nm->mkNode(ITE, equal_95, const_rational_15, ite_279);
  Node ite_277 = nm->mkNode(ITE, equal_107, const_rational_12, ite_278);
  Node ite_276 = nm->mkNode(ITE, equal_123, const_rational_13, ite_277);
  Node ite_275 = nm->mkNode(ITE, equal_139, const_rational_10, ite_276);
  Node ite_274 = nm->mkNode(ITE, equal_162, const_rational_11, ite_275);
  Node ite_273 = nm->mkNode(ITE, equal_179, mult_280, ite_274);
  Node equal_46 = nm->mkNode(EQUAL, t, const_rational_10);
  Node mult_272 = nm->mkNode(MULT, s, const_rational_11);
  Node equal_73 = nm->mkNode(EQUAL, s, const_rational_8);
  Node ite_270 = nm->mkNode(ITE, equal_73, const_rational_2, const_rational_3);
  Node ite_269 = nm->mkNode(ITE, equal_83, const_rational_13, ite_270);
  Node ite_268 = nm->mkNode(ITE, equal_95, mult_210, ite_269);
  Node ite_267 = nm->mkNode(ITE, equal_107, mult_271, ite_268);
  Node ite_266 = nm->mkNode(ITE, equal_123, const_rational_14, ite_267);
  Node ite_265 = nm->mkNode(ITE, equal_139, mult_178, ite_266);
  Node ite_264 = nm->mkNode(ITE, equal_162, mult_211, ite_265);
  Node ite_263 = nm->mkNode(ITE, equal_179, mult_272, ite_264);
  Node equal_39 = nm->mkNode(EQUAL, t, const_rational_11);
  Node mult_262 = nm->mkNode(MULT, s, const_rational_10);
  Node equal_53 = nm->mkNode(EQUAL, s, const_rational_10);
  Node ite_261 = nm->mkNode(ITE, equal_53, const_rational_1, const_rational_2);
  Node ite_260 = nm->mkNode(ITE, equal_73, const_rational_3, ite_261);
  Node ite_259 = nm->mkNode(ITE, equal_83, const_rational_12, ite_260);
  Node ite_258 = nm->mkNode(ITE, equal_95, const_rational_13, ite_259);
  Node ite_257 = nm->mkNode(ITE, equal_107, const_rational_14, ite_258);
  Node ite_256 = nm->mkNode(ITE, equal_123, const_rational_15, ite_257);
  Node ite_255 = nm->mkNode(ITE, equal_139, const_rational_8, ite_256);
  Node ite_254 = nm->mkNode(ITE, equal_162, const_rational_9, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_179, mult_262, ite_254);
  Node equal_29 = nm->mkNode(EQUAL, t, const_rational_12);
  Node mult_252 = nm->mkNode(MULT, s, const_rational_13);
  Node equal_62 = nm->mkNode(EQUAL, s, const_rational_9);
  Node ite_249 = nm->mkNode(ITE, equal_53, const_rational_6, const_rational_7);
  Node ite_248 = nm->mkNode(ITE, equal_62, const_rational_5, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_73, const_rational_4, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_83, const_rational_11, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_95, const_rational_10, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_107, const_rational_9, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_123, mult_210, ite_244);
  Node ite_242 = nm->mkNode(ITE, equal_139, mult_250, ite_243);
  Node ite_241 = nm->mkNode(ITE, equal_162, mult_251, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_179, mult_252, ite_241);
  Node equal_22 = nm->mkNode(EQUAL, t, const_rational_13);
  Node mult_239 = nm->mkNode(MULT, s, const_rational_12);
  Node equal_38 = nm->mkNode(EQUAL, s, const_rational_12);
  Node ite_238 = nm->mkNode(ITE, equal_38, const_rational_1, const_rational_6);
  Node ite_237 = nm->mkNode(ITE, equal_53, const_rational_7, ite_238);
  Node ite_236 = nm->mkNode(ITE, equal_62, const_rational_4, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_73, const_rational_5, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_83, const_rational_10, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_95, const_rational_11, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_107, const_rational_8, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_123, const_rational_9, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_139, const_rational_14, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_162, const_rational_15, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_179, mult_239, ite_229);
  Node equal_227 = nm->mkNode(EQUAL, t, const_rational_14);
  Node mult_226 = nm->mkNode(MULT, s, const_rational_15);
  Node equal_45 = nm->mkNode(EQUAL, s, const_rational_11);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_224 = nm->mkNode(ITE, equal_26, const_rational_3, const_rational_2);
  Node ite_223 = nm->mkNode(ITE, equal_45, const_rational_5, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_53, const_rational_4, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_62, const_rational_7, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_73, const_rational_6, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_83, const_rational_9, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_95, const_rational_8, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_107, const_rational_11, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_123, const_rational_10, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_139, const_rational_13, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_162, mult_225, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_179, mult_226, ite_214);
  Node mult_212 = nm->mkNode(MULT, s, const_rational_14);
  Node ite_209 = nm->mkNode(ITE, equal_26, const_rational_2, const_rational_1);
  Node ite_208 = nm->mkNode(ITE, equal_38, const_rational_3, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_45, const_rational_4, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_53, const_rational_5, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_62, const_rational_6, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_73, const_rational_7, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_83, const_rational_8, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_95, const_rational_9, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_107, mult_210, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_123, const_rational_11, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_139, mult_211, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_162, const_rational_13, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_179, mult_212, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_227, ite_213, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_22, ite_228, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_29, ite_240, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_39, ite_253, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_46, ite_263, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_54, ite_273, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_63, ite_281, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_74, ite_288, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_84, ite_293, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_96, ite_297, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_108, ite_300, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_124, ite_302, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_140, mult_271, ite_185);
  Node ite_183 = nm->mkNode(ITE, geq_303, const_rational_0, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_304, t, ite_183);
  Node equal_180 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_27 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_177 = nm->mkNode(ITE, equal_27, s, s);
  Node ite_176 = nm->mkNode(ITE, equal_26, s, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_38, s, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_45, s, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_53, s, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_62, s, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_73, s, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_83, s, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_95, s, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_107, s, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_123, s, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_139, s, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_162, s, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_179, mult_178, ite_165);
  Node equal_163 = nm->mkNode(EQUAL, t, const_rational_1);
  Node mult_94 = nm->mkNode(MULT, t, const_rational_3);
  Node mult_72 = nm->mkNode(MULT, t, const_rational_2);
  Node mult_121 = nm->mkNode(MULT, t, const_rational_5);
  Node mult_120 = nm->mkNode(MULT, t, const_rational_4);
  Node mult_138 = nm->mkNode(MULT, t, const_rational_7);
  Node mult_137 = nm->mkNode(MULT, t, const_rational_6);
  Node mult_161 = nm->mkNode(MULT, t, const_rational_9);
  Node mult_160 = nm->mkNode(MULT, t, const_rational_8);
  Node mult_159 = nm->mkNode(MULT, t, const_rational_11);
  Node mult_158 = nm->mkNode(MULT, t, const_rational_10);
  Node mult_157 = nm->mkNode(MULT, t, const_rational_13);
  Node mult_156 = nm->mkNode(MULT, t, const_rational_12);
  Node mult_155 = nm->mkNode(MULT, t, const_rational_14);
  Node mult_154 = nm->mkNode(MULT, t, const_rational_15);
  Node ite_153 = nm->mkNode(ITE, equal_27, mult_155, mult_154);
  Node ite_152 = nm->mkNode(ITE, equal_26, mult_156, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_38, mult_157, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_45, mult_158, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_53, mult_159, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_62, mult_160, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_73, mult_161, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_83, mult_137, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_95, mult_138, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_107, mult_120, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_123, mult_121, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_139, mult_72, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_162, mult_94, ite_142);
  Node mult_122 = nm->mkNode(MULT, t, t);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_136 = nm->mkNode(ITE, equal_20, mult_137, const_rational_13);
  Node ite_135 = nm->mkNode(ITE, equal_26, const_rational_15, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_38, mult_138, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_45, const_rational_9, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_53, mult_120, ite_133);
  Node ite_131 = nm->mkNode(ITE, equal_62, const_rational_11, ite_132);
  Node ite_130 = nm->mkNode(ITE, equal_73, mult_121, ite_131);
  Node ite_129 = nm->mkNode(ITE, equal_83, const_rational_5, ite_130);
  Node ite_128 = nm->mkNode(ITE, equal_95, mult_122, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_107, const_rational_7, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_123, mult_94, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_139, const_rational_1, ite_126);
  Node ite_119 =
      nm->mkNode(ITE, equal_26, const_rational_14, const_rational_13);
  Node ite_118 = nm->mkNode(ITE, equal_27, mult_120, ite_119);
  Node ite_117 = nm->mkNode(ITE, equal_38, mult_121, ite_118);
  Node ite_116 = nm->mkNode(ITE, equal_45, const_rational_8, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_53, mult_122, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_62, const_rational_10, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_73, const_rational_11, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_83, const_rational_4, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_95, const_rational_5, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_107, mult_72, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_123, const_rational_7, ite_110);
  Node ite_106 =
      nm->mkNode(ITE, equal_20, const_rational_10, const_rational_11);
  Node ite_105 = nm->mkNode(ITE, equal_26, const_rational_9, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_38, mult_72, ite_105);
  Node ite_103 = nm->mkNode(ITE, equal_45, const_rational_15, ite_104);
  Node ite_102 = nm->mkNode(ITE, equal_53, const_rational_14, ite_103);
  Node ite_101 = nm->mkNode(ITE, equal_62, const_rational_13, ite_102);
  Node ite_100 = nm->mkNode(ITE, equal_73, mult_94, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_83, const_rational_3, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_95, const_rational_2, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_107, const_rational_1, ite_98);
  Node ite_93 = nm->mkNode(ITE, equal_20, const_rational_11, const_rational_8);
  Node ite_92 = nm->mkNode(ITE, equal_27, mult_72, ite_93);
  Node ite_91 = nm->mkNode(ITE, equal_38, const_rational_9, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_45, const_rational_14, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_53, mult_94, ite_90);
  Node ite_88 = nm->mkNode(ITE, equal_62, const_rational_12, ite_89);
  Node ite_87 = nm->mkNode(ITE, equal_73, const_rational_13, ite_88);
  Node ite_86 = nm->mkNode(ITE, equal_83, const_rational_2, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_95, const_rational_3, ite_86);
  Node ite_82 = nm->mkNode(ITE, equal_45, const_rational_13, const_rational_10);
  Node ite_81 = nm->mkNode(ITE, equal_26, const_rational_11, ite_82);
  Node ite_80 = nm->mkNode(ITE, equal_53, mult_72, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_20, const_rational_8, ite_80);
  Node ite_78 = nm->mkNode(ITE, equal_62, const_rational_15, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_73, const_rational_14, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_83, const_rational_1, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_27, const_rational_9, ite_76);
  Node ite_71 = nm->mkNode(ITE, equal_26, const_rational_10, const_rational_9);
  Node ite_70 = nm->mkNode(ITE, equal_38, const_rational_11, ite_71);
  Node ite_69 = nm->mkNode(ITE, equal_45, const_rational_12, ite_70);
  Node ite_68 = nm->mkNode(ITE, equal_27, const_rational_8, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_53, const_rational_13, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_62, mult_72, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_73, const_rational_15, ite_66);
  Node ite_61 = nm->mkNode(ITE, equal_38, const_rational_4, const_rational_5);
  Node ite_60 = nm->mkNode(ITE, equal_45, const_rational_3, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_53, const_rational_2, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_20, const_rational_6, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_62, const_rational_1, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_27, const_rational_7, ite_57);
  Node ite_52 = nm->mkNode(ITE, equal_20, const_rational_7, const_rational_6);
  Node ite_51 = nm->mkNode(ITE, equal_26, const_rational_4, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_38, const_rational_5, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_45, const_rational_2, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_53, const_rational_3, ite_49);
  Node ite_44 = nm->mkNode(ITE, equal_27, const_rational_5, const_rational_4);
  Node ite_43 = nm->mkNode(ITE, equal_26, const_rational_7, ite_44);
  Node ite_42 = nm->mkNode(ITE, equal_38, const_rational_6, ite_43);
  Node ite_41 = nm->mkNode(ITE, equal_45, const_rational_1, ite_42);
  Node ite_33 = nm->mkNode(ITE, equal_27, const_rational_4, const_rational_5);
  Node ite_32 = nm->mkNode(ITE, equal_26, const_rational_6, ite_33);
  Node ite_31 = nm->mkNode(ITE, equal_38, const_rational_7, ite_32);
  Node ite_25 = nm->mkNode(ITE, equal_26, const_rational_1, const_rational_2);
  Node ite_24 = nm->mkNode(ITE, equal_27, const_rational_3, ite_25);
  Node ite_17 = nm->mkNode(ITE, equal_20, const_rational_3, const_rational_2);
  Node ite_15 = nm->mkNode(ITE, equal_22, ite_17, const_rational_1);
  Node ite_14 = nm->mkNode(ITE, equal_29, ite_24, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_39, ite_31, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_46, ite_41, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_54, ite_48, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_63, ite_56, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_74, ite_65, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_84, ite_75, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_96, ite_85, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_108, ite_97, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_124, ite_109, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_140, ite_125, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_163, ite_141, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_180, ite_164, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_305, ite_182, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_4_nia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (+ s t) (ite (>= s t) 0 (ite (= t 2) (+ s t) (ite (= t 3) (ite (= s 1) (+ s
// s) 1) (ite (= s 14) 1 (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 1) (* s 4)
// (ite (= s 4) 1 (ite (= s 2) (+ s t) (+ s s)))) (ite (= t 6) (ite (= s 1) (+ s
// t) (ite (= s 2) (* s s) (ite (= s 3) (+ s 2) (ite (= s 4) 2 3)))) (ite (= t
// 7) (ite (= s 1) (* s 6) (ite (= s 2) (+ s 3) (ite (= s 3) (+ s 1) (ite (= s
// 4) 3 (ite (= s 5) 2 1))))) (ite (= t 8) (+ s t) (ite (= t 9) (ite (= s 1) (*
// s 8) (ite (= s 2) (+ s t) (ite (= s 3) (+ s 7) (ite (= s 4) (+ s t) (ite (= s
// 5) (+ s 7) (ite (= s 6) (+ s t) (ite (= s 7) (+ s s) 1))))))) (ite (= t 10)
// (ite (= s 1) (+ s t) (ite (= s 2) (* s 4) (ite (= s 3) (* s s) (ite (= s 4)
// (+ s t) (ite (= s 5) (+ s t) (ite (= s 6) (+ s s) (ite (= s 7) (+ s 6) (ite
// (= s 8) 2 3)))))))) (ite (= t 11) (ite (= s 1) (* s 10) (ite (= s 2) (+ s 7)
// (ite (= s 3) (+ s 5) (ite (= s 4) (+ s t) (ite (= s 5) (+ s 9) (ite (= s 6)
// (+ s 7) (ite (= s 7) (+ s 5) (ite (= s 8) 3 (ite (= s 9) 2 1))))))))) (ite (=
// t 12) (ite (= s 1) (+ s t) (ite (= s 2) (+ s t) (ite (= s 3) (+ s t) (ite (=
// s 4) (+ s s) (ite (= s 5) (+ s 4) (ite (= s 6) (+ s 4) (ite (= s 7) (+ s 4)
// (ite (= s 8) 4 (ite (= s 9) 5 (ite (= s 11) 7 6)))))))))) (ite (= t 13) (ite
// (= s 1) (* s 12) (ite (= s 2) (+ s t) (ite (= s 3) (+ s 11) (ite (= s 4) (+ s
// 5) (ite (= s 12) 1 (ite (= s 5) (+ s 3) (ite (= s 6) (+ s 5) (ite (= s 7) (+
// s 3) (ite (= s 8) 5 (ite (= s 11) 6 (ite (= s 10) 7 4))))))))))) (ite (= t
// 14) (ite (= s 1) (+ s t) (ite (= s 2) (* s 6) (ite (= s 3) (+ s 10) (ite (= s
// 4) (+ s 6) (ite (= s 5) (+ s 6) (ite (= s 6) (+ s 2) (ite (= s 7) (+ s 2)
// (ite (= s 8) 6 (ite (= s 9) 7 (ite (= s 10) 4 (ite (= s 11) 5 (ite (= s 12) 2
// 3)))))))))))) (ite (= s 1) (* s 14) (ite (= s 2) (+ s 11) (ite (= s 3) (* s
// 4) (ite (= s 4) (+ s 7) (ite (= s 5) (+ s s) (ite (= s 6) (+ s 3) (ite (= s
// 7) (+ s 1) (ite (= s 8) 7 (ite (= s 9) 6 (ite (= s 10) 5 (ite (= s 11) 4 (ite
// (= s 12) 3 2)))))))))))))))))))))))))))) (ite (= t 0) (+ s t) (ite (= t 1)
// (ite (= s 2) (+ s t) (ite (= s 3) (+ t t) (ite (= s 4) (+ s t) (ite (= s 5)
// (* t 4) (ite (= s 6) (+ s t) (ite (= s 7) (+ t 5) (ite (= s 8) (+ s t) (ite
// (= s 9) 8 (ite (= s 10) (+ s t) (ite (= s 11) 10 (ite (= s 12) (+ s t) (ite
// (= s 13) 12 (ite (= s 14) (+ s t) 14))))))))))))) (ite (= t 2) (ite (= s 3) 1
// (ite (= s 4) (+ s t) (ite (= s 5) (+ s t) (ite (= s 6) (* t t) (ite (= s 7)
// (+ t 3) (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) (* t 4) (ite
// (= s 11) 9 (ite (= s 12) (+ s t) (ite (= s 13) (+ s t) (ite (= s 14) 12
// 13)))))))))))) (ite (= t 3) (ite (= s 4) (+ s t) (ite (= s 5) (+ t t) (ite (=
// s 6) (+ t 2) (ite (= s 7) (+ t 1) (ite (= s 8) (+ s t) (ite (= s 9) (+ s 1)
// (ite (= s 10) (* t t) (ite (= s 11) (+ t 5) (ite (= s 12) (+ s t) (ite (= s
// 13) (+ s 1) (ite (= s 14) 13 (* t 4)))))))))))) (ite (= t 4) (ite (= s 5) 1
// (ite (= s 6) 2 (ite (= s 7) 3 (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite
// (= s 15) 11 (ite (= s 10) (+ s t) (ite (= s 11) (+ s t) (ite (= s 12) (+ t t)
// (ite (= s 13) (+ t 5) 10)))))))))) (ite (= t 5) (ite (= s 6) 3 (ite (= s 7) 2
// (ite (= s 8) (+ s t) (ite (= s 9) (+ s 3) (ite (= s 10) (+ s t) (ite (= s 11)
// (+ s 3) (ite (= s 12) (+ t 4) (ite (= s 13) (+ t 3) (ite (= s 14) 11 (+ t
// t)))))))))) (ite (= t 6) (ite (= s 7) 1 (ite (= s 8) (+ s t) (ite (= s 9) (+
// s t) (ite (= s 10) (+ t t) (ite (= s 11) (+ s 2) (ite (= s 12) (+ t 4) (ite
// (= s 13) (+ t 5) (ite (= s 14) (+ t 2) (+ t 3))))))))) (ite (= t 7) (ite (= s
// 8) (+ s t) (ite (= s 9) (+ t t) (ite (= s 10) (+ s 3) (ite (= s 11) (+ s 1)
// (ite (= s 12) (+ t 4) (ite (= s 13) (+ t 3) (ite (= s 14) (+ t 2) (+ t
// 1)))))))) (ite (= t 8) (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 11) 3 (ite (=
// s 12) 4 (ite (= s 13) 5 (ite (= s 15) 7 6)))))) (ite (= t 9) (ite (= s 10) 3
// (ite (= s 11) 2 (ite (= s 12) 5 (ite (= s 13) 4 (ite (= s 15) 6 7))))) (ite
// (= t 10) (ite (= s 11) 1 (ite (= s 12) 6 (ite (= s 13) 7 (ite (= s 14) 4
// 5)))) (ite (= t 11) (ite (= s 12) 7 (ite (= s 13) 6 (ite (= s 14) 5 4))) (ite
// (= t 12) (ite (= s 13) 1 (ite (= s 15) 3 2)) (ite (= t 13) (ite (= s 14) 3 2)
// 1))))))))))))))))
Node int_bvxor_4_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_280 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_279 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_79 = nm->mkNode(PLUS, s, t);
  Node geq_278 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_145 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_131 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_196 = nm->mkNode(EQUAL, s, const_rational_1);
  Node plus_191 = nm->mkNode(PLUS, s, s);
  Node ite_277 = nm->mkNode(ITE, equal_196, plus_191, const_rational_1);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_14);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_116 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_104 = nm->mkNode(EQUAL, t, const_rational_5);
  Node mult_193 = nm->mkNode(MULT, s, const_rational_4);
  Node equal_130 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_159 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_276 = nm->mkNode(ITE, equal_159, plus_79, plus_191);
  Node ite_275 = nm->mkNode(ITE, equal_130, const_rational_1, ite_276);
  Node ite_274 = nm->mkNode(ITE, equal_196, mult_193, ite_275);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_93 = nm->mkNode(EQUAL, t, const_rational_6);
  Node mult_256 = nm->mkNode(MULT, s, s);
  Node equal_144 = nm->mkNode(EQUAL, s, const_rational_3);
  Node plus_91 = nm->mkNode(PLUS, s, const_rational_2);
  Node ite_273 = nm->mkNode(ITE, equal_130, const_rational_2, const_rational_3);
  Node ite_272 = nm->mkNode(ITE, equal_144, plus_91, ite_273);
  Node ite_271 = nm->mkNode(ITE, equal_159, mult_256, ite_272);
  Node ite_270 = nm->mkNode(ITE, equal_196, plus_79, ite_271);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_81 = nm->mkNode(EQUAL, t, const_rational_7);
  Node mult_211 = nm->mkNode(MULT, s, const_rational_6);
  Node plus_77 = nm->mkNode(PLUS, s, const_rational_3);
  Node plus_76 = nm->mkNode(PLUS, s, const_rational_1);
  Node equal_115 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_269 = nm->mkNode(ITE, equal_115, const_rational_2, const_rational_1);
  Node ite_268 = nm->mkNode(ITE, equal_130, const_rational_3, ite_269);
  Node ite_267 = nm->mkNode(ITE, equal_144, plus_76, ite_268);
  Node ite_266 = nm->mkNode(ITE, equal_159, plus_77, ite_267);
  Node ite_265 = nm->mkNode(ITE, equal_196, mult_211, ite_266);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_63 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_54 = nm->mkNode(EQUAL, t, const_rational_9);
  Node mult_264 = nm->mkNode(MULT, s, const_rational_8);
  Node plus_192 = nm->mkNode(PLUS, s, const_rational_7);
  Node equal_103 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_92 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_263 = nm->mkNode(ITE, equal_92, plus_191, const_rational_1);
  Node ite_262 = nm->mkNode(ITE, equal_103, plus_79, ite_263);
  Node ite_261 = nm->mkNode(ITE, equal_115, plus_192, ite_262);
  Node ite_260 = nm->mkNode(ITE, equal_130, plus_79, ite_261);
  Node ite_259 = nm->mkNode(ITE, equal_144, plus_192, ite_260);
  Node ite_258 = nm->mkNode(ITE, equal_159, plus_79, ite_259);
  Node ite_257 = nm->mkNode(ITE, equal_196, mult_264, ite_258);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_46 = nm->mkNode(EQUAL, t, const_rational_10);
  Node plus_209 = nm->mkNode(PLUS, s, const_rational_6);
  Node equal_80 = nm->mkNode(EQUAL, s, const_rational_8);
  Node ite_255 = nm->mkNode(ITE, equal_80, const_rational_2, const_rational_3);
  Node ite_254 = nm->mkNode(ITE, equal_92, plus_209, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_103, plus_191, ite_254);
  Node ite_252 = nm->mkNode(ITE, equal_115, plus_79, ite_253);
  Node ite_251 = nm->mkNode(ITE, equal_130, plus_79, ite_252);
  Node ite_250 = nm->mkNode(ITE, equal_144, mult_256, ite_251);
  Node ite_249 = nm->mkNode(ITE, equal_159, mult_193, ite_250);
  Node ite_248 = nm->mkNode(ITE, equal_196, plus_79, ite_249);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_39 = nm->mkNode(EQUAL, t, const_rational_11);
  Node mult_247 = nm->mkNode(MULT, s, const_rational_10);
  Node plus_224 = nm->mkNode(PLUS, s, const_rational_5);
  Node plus_246 = nm->mkNode(PLUS, s, const_rational_9);
  Node equal_62 = nm->mkNode(EQUAL, s, const_rational_9);
  Node ite_245 = nm->mkNode(ITE, equal_62, const_rational_2, const_rational_1);
  Node ite_244 = nm->mkNode(ITE, equal_80, const_rational_3, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_92, plus_224, ite_244);
  Node ite_242 = nm->mkNode(ITE, equal_103, plus_192, ite_243);
  Node ite_241 = nm->mkNode(ITE, equal_115, plus_246, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_130, plus_79, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_144, plus_224, ite_240);
  Node ite_238 = nm->mkNode(ITE, equal_159, plus_192, ite_239);
  Node ite_237 = nm->mkNode(ITE, equal_196, mult_247, ite_238);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_29 = nm->mkNode(EQUAL, t, const_rational_12);
  Node plus_236 = nm->mkNode(PLUS, s, const_rational_4);
  Node equal_45 = nm->mkNode(EQUAL, s, const_rational_11);
  Node ite_235 = nm->mkNode(ITE, equal_45, const_rational_7, const_rational_6);
  Node ite_234 = nm->mkNode(ITE, equal_62, const_rational_5, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_80, const_rational_4, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_92, plus_236, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_103, plus_236, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_115, plus_236, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_130, plus_191, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_144, plus_79, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_159, plus_79, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_196, plus_79, ite_227);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_22 = nm->mkNode(EQUAL, t, const_rational_13);
  Node mult_225 = nm->mkNode(MULT, s, const_rational_12);
  Node plus_194 = nm->mkNode(PLUS, s, const_rational_11);
  Node equal_38 = nm->mkNode(EQUAL, s, const_rational_12);
  Node equal_53 = nm->mkNode(EQUAL, s, const_rational_10);
  Node ite_223 = nm->mkNode(ITE, equal_53, const_rational_7, const_rational_4);
  Node ite_222 = nm->mkNode(ITE, equal_45, const_rational_6, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_80, const_rational_5, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_92, plus_77, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_103, plus_224, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_115, plus_77, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_38, const_rational_1, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_130, plus_224, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_144, plus_194, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_159, plus_79, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_196, mult_225, ite_214);
  Node equal_212 = nm->mkNode(EQUAL, t, const_rational_14);
  Node plus_210 = nm->mkNode(PLUS, s, const_rational_10);
  Node ite_208 = nm->mkNode(ITE, equal_38, const_rational_2, const_rational_3);
  Node ite_207 = nm->mkNode(ITE, equal_45, const_rational_5, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_53, const_rational_4, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_62, const_rational_7, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_80, const_rational_6, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_92, plus_91, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_103, plus_91, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_115, plus_209, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_130, plus_209, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_144, plus_210, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_159, mult_211, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_196, plus_79, ite_198);
  Node mult_195 = nm->mkNode(MULT, s, const_rational_14);
  Node ite_190 = nm->mkNode(ITE, equal_38, const_rational_3, const_rational_2);
  Node ite_189 = nm->mkNode(ITE, equal_45, const_rational_4, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_53, const_rational_5, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_62, const_rational_6, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_80, const_rational_7, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_92, plus_76, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_103, plus_77, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_115, plus_191, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_130, plus_192, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_144, mult_193, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_159, plus_194, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_196, mult_195, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_212, ite_197, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_22, ite_213, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_29, ite_226, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_39, ite_237, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_46, ite_248, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_54, ite_257, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_63, plus_79, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_81, ite_265, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_93, ite_270, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_104, ite_274, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_116, plus_79, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_20, const_rational_1, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_131, ite_277, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_145, plus_79, ite_166);
  Node ite_164 = nm->mkNode(ITE, geq_278, const_rational_0, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_279, plus_79, ite_164);
  Node equal_161 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_160 = nm->mkNode(EQUAL, t, const_rational_1);
  Node plus_78 = nm->mkNode(PLUS, t, t);
  Node mult_128 = nm->mkNode(MULT, t, const_rational_4);
  Node plus_90 = nm->mkNode(PLUS, t, const_rational_5);
  Node equal_28 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_158 = nm->mkNode(ITE, equal_20, plus_79, const_rational_14);
  Node ite_157 = nm->mkNode(ITE, equal_28, const_rational_12, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_38, plus_79, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_45, const_rational_10, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_53, plus_79, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_62, const_rational_8, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_80, plus_79, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_92, plus_90, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_103, plus_79, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_115, mult_128, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_130, plus_79, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_144, plus_78, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_159, plus_79, ite_147);
  Node mult_129 = nm->mkNode(MULT, t, t);
  Node plus_74 = nm->mkNode(PLUS, t, const_rational_3);
  Node ite_143 =
      nm->mkNode(ITE, equal_20, const_rational_12, const_rational_13);
  Node ite_142 = nm->mkNode(ITE, equal_28, plus_79, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_38, plus_79, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_45, const_rational_9, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_53, mult_128, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_62, plus_79, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_80, plus_79, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_92, plus_74, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_103, mult_129, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_115, plus_79, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_130, plus_79, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_144, const_rational_1, ite_133);
  Node plus_73 = nm->mkNode(PLUS, t, const_rational_2);
  Node plus_72 = nm->mkNode(PLUS, t, const_rational_1);
  Node ite_127 = nm->mkNode(ITE, equal_20, const_rational_13, mult_128);
  Node ite_126 = nm->mkNode(ITE, equal_28, plus_76, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_38, plus_79, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_45, plus_90, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_53, mult_129, ite_124);
  Node ite_122 = nm->mkNode(ITE, equal_62, plus_76, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_80, plus_79, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_92, plus_72, ite_121);
  Node ite_119 = nm->mkNode(ITE, equal_103, plus_73, ite_120);
  Node ite_118 = nm->mkNode(ITE, equal_115, plus_78, ite_119);
  Node ite_117 = nm->mkNode(ITE, equal_130, plus_79, ite_118);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_114 = nm->mkNode(ITE, equal_28, plus_90, const_rational_10);
  Node ite_113 = nm->mkNode(ITE, equal_38, plus_78, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_45, plus_79, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_53, plus_79, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_26, const_rational_11, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_62, plus_79, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_80, plus_79, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_92, const_rational_3, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_103, const_rational_2, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_115, const_rational_1, ite_106);
  Node plus_75 = nm->mkNode(PLUS, t, const_rational_4);
  Node ite_102 = nm->mkNode(ITE, equal_20, const_rational_11, plus_78);
  Node ite_101 = nm->mkNode(ITE, equal_28, plus_74, ite_102);
  Node ite_100 = nm->mkNode(ITE, equal_38, plus_75, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_45, plus_77, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_53, plus_79, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_62, plus_77, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_80, plus_79, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_92, const_rational_2, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_103, const_rational_3, ite_95);
  Node ite_89 = nm->mkNode(ITE, equal_20, plus_73, plus_74);
  Node ite_88 = nm->mkNode(ITE, equal_28, plus_90, ite_89);
  Node ite_87 = nm->mkNode(ITE, equal_38, plus_75, ite_88);
  Node ite_86 = nm->mkNode(ITE, equal_45, plus_91, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_53, plus_78, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_62, plus_79, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_80, plus_79, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_92, const_rational_1, ite_83);
  Node ite_71 = nm->mkNode(ITE, equal_20, plus_73, plus_72);
  Node ite_70 = nm->mkNode(ITE, equal_28, plus_74, ite_71);
  Node ite_69 = nm->mkNode(ITE, equal_38, plus_75, ite_70);
  Node ite_68 = nm->mkNode(ITE, equal_45, plus_76, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_53, plus_77, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_62, plus_78, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_80, plus_79, ite_66);
  Node ite_61 = nm->mkNode(ITE, equal_26, const_rational_7, const_rational_6);
  Node ite_60 = nm->mkNode(ITE, equal_28, const_rational_5, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_38, const_rational_4, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_45, const_rational_3, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_53, const_rational_2, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_62, const_rational_1, ite_57);
  Node ite_52 = nm->mkNode(ITE, equal_26, const_rational_6, const_rational_7);
  Node ite_51 = nm->mkNode(ITE, equal_28, const_rational_4, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_38, const_rational_5, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_45, const_rational_2, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_53, const_rational_3, ite_49);
  Node ite_44 = nm->mkNode(ITE, equal_20, const_rational_4, const_rational_5);
  Node ite_43 = nm->mkNode(ITE, equal_28, const_rational_7, ite_44);
  Node ite_42 = nm->mkNode(ITE, equal_38, const_rational_6, ite_43);
  Node ite_41 = nm->mkNode(ITE, equal_45, const_rational_1, ite_42);
  Node ite_33 = nm->mkNode(ITE, equal_20, const_rational_5, const_rational_4);
  Node ite_32 = nm->mkNode(ITE, equal_28, const_rational_6, ite_33);
  Node ite_31 = nm->mkNode(ITE, equal_38, const_rational_7, ite_32);
  Node ite_25 = nm->mkNode(ITE, equal_26, const_rational_3, const_rational_2);
  Node ite_24 = nm->mkNode(ITE, equal_28, const_rational_1, ite_25);
  Node ite_17 = nm->mkNode(ITE, equal_20, const_rational_3, const_rational_2);
  Node ite_15 = nm->mkNode(ITE, equal_22, ite_17, const_rational_1);
  Node ite_14 = nm->mkNode(ITE, equal_29, ite_24, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_39, ite_31, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_46, ite_41, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_54, ite_48, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_63, ite_56, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_81, ite_65, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_93, ite_82, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_104, ite_94, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_116, ite_105, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_131, ite_117, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_145, ite_132, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_160, ite_146, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_161, plus_79, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_280, ite_163, ite_2);
  return ite_1;
}
