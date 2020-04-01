#include "bw_functions.h"
#include <math.h>
#include "theory/bv/theory_bv_utils.h"
using namespace CVC4::kind;
using namespace CVC4;
// (define-fun int_bvand_1_min ((s Int) (t Int)) Int (* s t))
Node int_bvand_1_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_1 = nm->mkNode(MULT, s, t);
  return mult_1;
}

// (define-fun int_bvand_1_trivial ((s Int) (t Int)) Int (ite (= s t) s 0))
Node int_bvand_1_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_3 = nm->mkNode(EQUAL, s, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node ite_1 = nm->mkNode(ITE, equal_3, s, const_rational_0);
  return ite_1;
}

// (define-fun int_bvand_2_min ((s Int) (t Int)) Int (ite (= 2 (* s t)) 0 (ite
// (>= s t) t s)))
Node int_bvand_2_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node mult_6 = nm->mkNode(MULT, s, t);
  Node equal_5 = nm->mkNode(EQUAL, const_rational_2, mult_6);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node geq_3 = nm->mkNode(GEQ, s, t);
  Node ite_2 = nm->mkNode(ITE, geq_3, t, s);
  Node ite_1 = nm->mkNode(ITE, equal_5, const_rational_0, ite_2);
  return ite_1;
}

// (define-fun int_bvand_2_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) s 0) (ite (= s 3) (ite (= t 0) (ite (= s 1) 0 (ite (= s 3) 0 0)) (ite (= s
// t) s (ite (= t 1) t t))) (ite (= t 0) (ite (= s 1) 0 (ite (= s 3) 0 0)) (ite
// (= s t) s (ite (= t 1) 0 (ite (= t 2) 0 (ite (= s 2) s s))))))))
Node int_bvand_2_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_14 = nm->mkNode(EQUAL, s, t);
  Node ite_24 = nm->mkNode(ITE, equal_14, s, const_rational_0);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_17 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_20 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_19 = nm->mkNode(EQUAL, s, const_rational_1);
  Node ite_16 = nm->mkNode(ITE, equal_17, const_rational_0, const_rational_0);
  Node ite_15 = nm->mkNode(ITE, equal_19, const_rational_0, ite_16);
  Node equal_12 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_23 = nm->mkNode(ITE, equal_12, t, t);
  Node ite_22 = nm->mkNode(ITE, equal_14, s, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_20, ite_15, ite_22);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_11 = nm->mkNode(EQUAL, t, const_rational_2);
  Node equal_8 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_7 = nm->mkNode(ITE, equal_8, s, s);
  Node ite_6 = nm->mkNode(ITE, equal_11, const_rational_0, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_12, const_rational_0, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_14, s, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_20, ite_15, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_17, ite_21, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_25, ite_24, ite_2);
  return ite_1;
}

// (define-fun int_bvand_3_min ((s Int) (t Int)) Int (ite (= s 0) (ite (= s t) s
// 0) (ite (= t 0) 0 (ite (= s t) s (ite (= t 1) (ite (= s 2) 0 (ite (= s 3) t
// (ite (= s 4) 0 (ite (= s 5) t (ite (= s 7) t 0))))) (ite (= t 2) (ite (= s 7)
// t (ite (= s 1) 0 (ite (= s 3) t (ite (= s 4) 0 (ite (= s 5) 0 t))))) (ite (=
// t 3) (ite (= s 1) s (ite (= s 2) s (ite (= s 4) 0 (ite (= s 5) 1 (ite (= s 6)
// 2 t))))) (ite (= t 4) (ite (= s 7) (ite (= t 4) t t) (ite (= s 1) 0 (ite (= s
// 2) 0 (ite (= s 3) 0 (ite (= s 5) t t))))) (ite (= t 5) (ite (= s 1) s (ite (=
// s 2) 0 (ite (= s 3) 1 (ite (= s 4) s (ite (= s 6) 4 (ite (= t 4) t t))))))
// (ite (= s 7) (ite (= t 4) t t) (ite (= t 6) (ite (= s 1) 0 (ite (= s 2) s
// (ite (= s 3) 2 (ite (= s 4) s 4)))) (ite (= s 1) s (ite (= s 6) s (ite (= s
// 2) s (ite (= s 5) s (ite (= s 3) s s))))))))))))))))
Node int_bvand_3_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_70 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_67 = nm->mkNode(EQUAL, s, t);
  Node ite_69 = nm->mkNode(ITE, equal_67, s, const_rational_0);
  Node equal_68 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_66 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_16 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_31 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_36 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_65 = nm->mkNode(ITE, equal_36, t, const_rational_0);
  Node ite_64 = nm->mkNode(ITE, equal_18, t, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_31, const_rational_0, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_16, t, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_20, const_rational_0, ite_62);
  Node equal_60 = nm->mkNode(EQUAL, t, const_rational_2);
  Node equal_24 = nm->mkNode(EQUAL, s, const_rational_1);
  Node ite_59 = nm->mkNode(ITE, equal_18, const_rational_0, t);
  Node ite_58 = nm->mkNode(ITE, equal_31, const_rational_0, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_16, t, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_24, const_rational_0, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_36, t, ite_56);
  Node equal_54 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_53 = nm->mkNode(ITE, equal_22, const_rational_2, t);
  Node ite_52 = nm->mkNode(ITE, equal_18, const_rational_1, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_31, const_rational_0, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_20, s, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_24, s, ite_50);
  Node equal_35 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_34 = nm->mkNode(ITE, equal_35, t, t);
  Node ite_48 = nm->mkNode(ITE, equal_18, t, t);
  Node ite_47 = nm->mkNode(ITE, equal_16, const_rational_0, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_20, const_rational_0, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_24, const_rational_0, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_36, ite_34, ite_45);
  Node equal_43 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_42 = nm->mkNode(ITE, equal_22, const_rational_4, ite_34);
  Node ite_41 = nm->mkNode(ITE, equal_31, s, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_16, const_rational_1, ite_41);
  Node ite_39 = nm->mkNode(ITE, equal_20, const_rational_0, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_24, s, ite_39);
  Node equal_33 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_29 = nm->mkNode(ITE, equal_31, s, const_rational_4);
  Node ite_28 = nm->mkNode(ITE, equal_16, const_rational_2, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_20, s, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_24, const_rational_0, ite_27);
  Node ite_15 = nm->mkNode(ITE, equal_16, s, s);
  Node ite_14 = nm->mkNode(ITE, equal_18, s, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_20, s, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_22, s, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_24, s, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_33, ite_26, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_36, ite_34, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_43, ite_38, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_35, ite_44, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_54, ite_49, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_60, ite_55, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_66, ite_61, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_67, s, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_68, const_rational_0, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_70, ite_69, ite_2);
  return ite_1;
}

// (define-fun int_bvand_3_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) s 0) (ite (= t 0) 0 (ite (= s t) s (ite (= t 1) (ite (= s 2) 0 (ite (= s
// 3) t (ite (= s 4) 0 (ite (= s 5) t (ite (= s 7) t 0))))) (ite (= t 2) (ite (=
// s 7) t (ite (= s 1) 0 (ite (= s 3) t (ite (= s 4) 0 (ite (= s 5) 0 t)))))
// (ite (= t 3) (ite (= s 1) s (ite (= s 2) s (ite (= s 4) 0 (ite (= s 5) 1 (ite
// (= s 6) 2 t))))) (ite (= t 4) (ite (= s 7) (ite (= t 4) t t) (ite (= s 1) 0
// (ite (= s 2) 0 (ite (= s 3) 0 (ite (= s 5) t t))))) (ite (= t 5) (ite (= s 1)
// s (ite (= s 2) 0 (ite (= s 3) 1 (ite (= s 4) s (ite (= s 6) 4 (ite (= t 4) t
// t)))))) (ite (= s 7) (ite (= t 4) t t) (ite (= t 6) (ite (= s 1) 0 (ite (= s
// 2) s (ite (= s 3) 2 (ite (= s 4) s 4)))) (ite (= s 1) s (ite (= s 6) s (ite
// (= s 2) s (ite (= s 5) s (ite (= s 3) s s))))))))))))))))
Node int_bvand_3_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_70 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_67 = nm->mkNode(EQUAL, s, t);
  Node ite_69 = nm->mkNode(ITE, equal_67, s, const_rational_0);
  Node equal_68 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_66 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_16 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_31 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_36 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_65 = nm->mkNode(ITE, equal_36, t, const_rational_0);
  Node ite_64 = nm->mkNode(ITE, equal_18, t, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_31, const_rational_0, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_16, t, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_20, const_rational_0, ite_62);
  Node equal_60 = nm->mkNode(EQUAL, t, const_rational_2);
  Node equal_24 = nm->mkNode(EQUAL, s, const_rational_1);
  Node ite_59 = nm->mkNode(ITE, equal_18, const_rational_0, t);
  Node ite_58 = nm->mkNode(ITE, equal_31, const_rational_0, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_16, t, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_24, const_rational_0, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_36, t, ite_56);
  Node equal_54 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_53 = nm->mkNode(ITE, equal_22, const_rational_2, t);
  Node ite_52 = nm->mkNode(ITE, equal_18, const_rational_1, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_31, const_rational_0, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_20, s, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_24, s, ite_50);
  Node equal_35 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_34 = nm->mkNode(ITE, equal_35, t, t);
  Node ite_48 = nm->mkNode(ITE, equal_18, t, t);
  Node ite_47 = nm->mkNode(ITE, equal_16, const_rational_0, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_20, const_rational_0, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_24, const_rational_0, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_36, ite_34, ite_45);
  Node equal_43 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_42 = nm->mkNode(ITE, equal_22, const_rational_4, ite_34);
  Node ite_41 = nm->mkNode(ITE, equal_31, s, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_16, const_rational_1, ite_41);
  Node ite_39 = nm->mkNode(ITE, equal_20, const_rational_0, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_24, s, ite_39);
  Node equal_33 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_29 = nm->mkNode(ITE, equal_31, s, const_rational_4);
  Node ite_28 = nm->mkNode(ITE, equal_16, const_rational_2, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_20, s, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_24, const_rational_0, ite_27);
  Node ite_15 = nm->mkNode(ITE, equal_16, s, s);
  Node ite_14 = nm->mkNode(ITE, equal_18, s, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_20, s, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_22, s, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_24, s, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_33, ite_26, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_36, ite_34, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_43, ite_38, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_35, ite_44, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_54, ite_49, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_60, ite_55, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_66, ite_61, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_67, s, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_68, const_rational_0, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_70, ite_69, ite_2);
  return ite_1;
}

// (define-fun int_bvand_4_min ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
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
Node int_bvand_4_min(Node s, Node t)
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

// (define-fun int_bvand_4_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) s 0) (ite (= t 0) (ite (= s 1) 0 (ite (= s 2) 0 (ite (= s 3) 0 (ite (= s
// 4) 0 (ite (= s 5) 0 (ite (= s 6) 0 (ite (= s 7) 0 (ite (= s 8) 0 (ite (= s 9)
// 0 (ite (= s 10) 0 (ite (= s 11) 0 (ite (= s 12) 0 (ite (= s 13) 0 (ite (= s
// 14) 0 0)))))))))))))) (ite (= s t) s (ite (= t 1) (ite (= s 2) 0 (ite (= s 3)
// t (ite (= s 4) 0 (ite (= s 5) t (ite (= s 6) 0 (ite (= s 7) t (ite (= s 15) t
// (ite (= s 8) 0 (ite (= s 14) 0 (ite (= s 13) t (ite (= s 9) t (ite (= s 10) 0
// (ite (= s 11) t 0))))))))))))) (ite (= t 2) (ite (= s 1) 0 (ite (= s 3) t
// (ite (= s 4) 0 (ite (= s 5) 0 (ite (= s 6) t (ite (= s 7) t (ite (= s 8) 0
// (ite (= s 9) 0 (ite (= s 10) t (ite (= s 11) t (ite (= s 12) 0 (ite (= s 13)
// 0 (ite (= s 15) t t))))))))))))) (ite (= t 3) (ite (= s 1) s (ite (= s 2) s
// (ite (= s 4) 0 (ite (= s 5) 1 (ite (= s 6) 2 (ite (= s 7) t (ite (= s 8) 0
// (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 11) t (ite (= s 12) 0 (ite (= s 13)
// 1 (ite (= s 15) t 2))))))))))))) (ite (= t 4) (ite (= s 1) 0 (ite (= s 2) 0
// (ite (= s 3) 0 (ite (= s 5) t (ite (= s 6) t (ite (= s 7) t (ite (= s 8) 0
// (ite (= s 9) 0 (ite (= s 10) 0 (ite (= s 11) 0 (ite (= s 12) t (ite (= s 13)
// t (ite (= s 14) t t))))))))))))) (ite (= t 5) (ite (= s 1) s (ite (= s 2) 0
// (ite (= s 3) 1 (ite (= s 4) s (ite (= s 6) 4 (ite (= s 7) t (ite (= s 8) 0
// (ite (= s 9) 1 (ite (= s 10) 0 (ite (= s 11) 1 (ite (= s 12) 4 (ite (= s 13)
// t (ite (= s 14) 4 t))))))))))))) (ite (= t 6) (ite (= s 1) 0 (ite (= s 2) s
// (ite (= s 3) 2 (ite (= s 4) s (ite (= s 15) t (ite (= s 5) 4 (ite (= s 7) t
// (ite (= s 8) 0 (ite (= s 9) 0 (ite (= s 10) 2 (ite (= s 11) 2 (ite (= s 12) 4
// (ite (= s 13) 4 t))))))))))))) (ite (= t 7) (ite (= s 1) (ite (= s 1) s (ite
// (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (=
// s 14) 6 (ite (= s 8) 0 (ite (= s 13) 5 (ite (= s 9) 1 (ite (= s 10) 2 (ite (=
// s 12) 4 3)))))))))))) (ite (= s 2) (ite (= s 1) s (ite (= s 2) s (ite (= s 3)
// s (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 14) 6 (ite (= s 8) 0
// (ite (= s 13) 5 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 12) 4 3))))))))))))
// (ite (= s 3) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite
// (= s 5) s (ite (= s 6) s (ite (= s 14) 6 (ite (= s 8) 0 (ite (= s 13) 5 (ite
// (= s 9) 1 (ite (= s 10) 2 (ite (= s 12) 4 3)))))))))))) (ite (= s 4) (ite (=
// s 1) s (ite (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s (ite (= s
// 6) s (ite (= s 14) 6 (ite (= s 8) 0 (ite (= s 13) 5 (ite (= s 9) 1 (ite (= s
// 10) 2 (ite (= s 12) 4 3)))))))))))) (ite (= s 5) (ite (= s 1) s (ite (= s 2)
// s (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 14) 6
// (ite (= s 8) 0 (ite (= s 13) 5 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 12) 4
// 3)))))))))))) (ite (= s 6) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s (ite
// (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 14) 6 (ite (= s 8) 0 (ite
// (= s 13) 5 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 12) 4 3)))))))))))) (ite
// (= s 8) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite (= s
// 5) s (ite (= s 6) s (ite (= s 14) 6 (ite (= s 8) 0 (ite (= s 13) 5 (ite (= s
// 9) 1 (ite (= s 10) 2 (ite (= s 12) 4 3)))))))))))) (ite (= s 9) (ite (= s 1)
// s (ite (= s 2) s (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s
// (ite (= s 14) 6 (ite (= s 8) 0 (ite (= s 13) 5 (ite (= s 9) 1 (ite (= s 10) 2
// (ite (= s 12) 4 3)))))))))))) (ite (= s 10) (ite (= s 1) s (ite (= s 2) s
// (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 14) 6
// (ite (= s 8) 0 (ite (= s 13) 5 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 12) 4
// 3)))))))))))) (ite (= s 15) (ite (= t 7) t t) (ite (= s 1) s (ite (= s 2) s
// (ite (= s 3) s (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 14) 6
// (ite (= s 8) 0 (ite (= s 13) 5 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 12) 4
// 3)))))))))))))))))))))) (ite (= t 8) (ite (= s 1) 0 (ite (= s 2) 0 (ite (= s
// 3) 0 (ite (= s 4) 0 (ite (= s 5) 0 (ite (= s 6) 0 (ite (= s 7) 0 (ite (= s 9)
// t (ite (= s 15) (ite (= t 7) t t) (ite (= s 10) t (ite (= s 11) t (ite (= s
// 12) t (ite (= s 14) t t))))))))))))) (ite (= s 15) (ite (= t 7) t t) (ite (=
// t 9) (ite (= s 1) s (ite (= s 2) 0 (ite (= s 3) 1 (ite (= s 4) 0 (ite (= s 5)
// 1 (ite (= s 6) 0 (ite (= s 7) 1 (ite (= s 8) s (ite (= s 10) 8 (ite (= s 15)
// (ite (= t 7) t t) (ite (= s 11) t (ite (= s 12) 8 (ite (= s 13) t
// 8))))))))))))) (ite (= t 10) (ite (= s 1) 0 (ite (= s 15) (ite (= t 7) t t)
// (ite (= s 2) s (ite (= s 3) 2 (ite (= s 4) 0 (ite (= s 14) t (ite (= s 5) 0
// (ite (= s 6) 2 (ite (= s 7) 2 (ite (= s 8) s (ite (= s 9) 8 (ite (= s 13) 8
// (ite (= s 11) t 8))))))))))))) (ite (= t 11) (ite (= s 1) s (ite (= s 2) s
// (ite (= s 3) s (ite (= s 4) 0 (ite (= s 5) 1 (ite (= s 6) 2 (ite (= s 7) 3
// (ite (= s 8) s (ite (= s 9) s (ite (= s 10) s (ite (= s 15) (ite (= t 7) t t)
// (ite (= s 12) 8 (ite (= s 14) 10 9))))))))))))) (ite (= t 12) (ite (= s 1) 0
// (ite (= s 2) 0 (ite (= s 3) 0 (ite (= s 4) s (ite (= s 5) 4 (ite (= s 6) 4
// (ite (= s 7) 4 (ite (= s 8) s (ite (= s 9) 8 (ite (= s 10) 8 (ite (= s 11) 8
// (ite (= s 13) t (ite (= s 14) t (ite (= t 7) t t)))))))))))))) (ite (= t 13)
// (ite (= s 1) s (ite (= s 2) 0 (ite (= s 3) 1 (ite (= s 4) s (ite (= s 5) s
// (ite (= s 6) 4 (ite (= s 7) 5 (ite (= s 8) s (ite (= s 9) s (ite (= s 10) 8
// (ite (= s 11) 9 (ite (= s 12) s (ite (= s 15) (ite (= t 7) t t)
// 12))))))))))))) (ite (= t 14) (ite (= s 1) 0 (ite (= s 2) s (ite (= s 3) 2
// (ite (= s 4) s (ite (= s 5) 4 (ite (= s 6) s (ite (= s 7) 6 (ite (= s 8) s
// (ite (= s 9) 8 (ite (= s 10) s (ite (= s 11) 10 (ite (= s 13) 12
// s)))))))))))) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s (ite (= s 14) s
// (ite (= s 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 7) s (ite (= s 8) s
// (ite (= s 9) s (ite (= s 10) s (ite (= s 13) s (ite (= s 12) s
// s))))))))))))))))))))))))))))))))
Node int_bvand_4_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_284 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_267 = nm->mkNode(EQUAL, s, t);
  Node ite_283 = nm->mkNode(ITE, equal_267, s, const_rational_0);
  Node equal_282 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_56 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_54 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_48 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_46 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_44 = nm->mkNode(EQUAL, s, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_40 = nm->mkNode(EQUAL, s, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_38 = nm->mkNode(EQUAL, s, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_36 = nm->mkNode(EQUAL, s, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_70 = nm->mkNode(EQUAL, s, const_rational_11);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_32 = nm->mkNode(EQUAL, s, const_rational_12);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_34 = nm->mkNode(EQUAL, s, const_rational_13);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_50 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_281 = nm->mkNode(ITE, equal_50, const_rational_0, const_rational_0);
  Node ite_280 = nm->mkNode(ITE, equal_34, const_rational_0, ite_281);
  Node ite_279 = nm->mkNode(ITE, equal_32, const_rational_0, ite_280);
  Node ite_278 = nm->mkNode(ITE, equal_70, const_rational_0, ite_279);
  Node ite_277 = nm->mkNode(ITE, equal_36, const_rational_0, ite_278);
  Node ite_276 = nm->mkNode(ITE, equal_38, const_rational_0, ite_277);
  Node ite_275 = nm->mkNode(ITE, equal_40, const_rational_0, ite_276);
  Node ite_274 = nm->mkNode(ITE, equal_42, const_rational_0, ite_275);
  Node ite_273 = nm->mkNode(ITE, equal_44, const_rational_0, ite_274);
  Node ite_272 = nm->mkNode(ITE, equal_46, const_rational_0, ite_273);
  Node ite_271 = nm->mkNode(ITE, equal_48, const_rational_0, ite_272);
  Node ite_270 = nm->mkNode(ITE, equal_52, const_rational_0, ite_271);
  Node ite_269 = nm->mkNode(ITE, equal_54, const_rational_0, ite_270);
  Node ite_268 = nm->mkNode(ITE, equal_56, const_rational_0, ite_269);
  Node equal_266 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_89 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_265 = nm->mkNode(ITE, equal_70, t, const_rational_0);
  Node ite_264 = nm->mkNode(ITE, equal_36, const_rational_0, ite_265);
  Node ite_263 = nm->mkNode(ITE, equal_38, t, ite_264);
  Node ite_262 = nm->mkNode(ITE, equal_34, t, ite_263);
  Node ite_261 = nm->mkNode(ITE, equal_50, const_rational_0, ite_262);
  Node ite_260 = nm->mkNode(ITE, equal_40, const_rational_0, ite_261);
  Node ite_259 = nm->mkNode(ITE, equal_89, t, ite_260);
  Node ite_258 = nm->mkNode(ITE, equal_42, t, ite_259);
  Node ite_257 = nm->mkNode(ITE, equal_44, const_rational_0, ite_258);
  Node ite_256 = nm->mkNode(ITE, equal_46, t, ite_257);
  Node ite_255 = nm->mkNode(ITE, equal_48, const_rational_0, ite_256);
  Node ite_254 = nm->mkNode(ITE, equal_52, t, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_54, const_rational_0, ite_254);
  Node equal_252 = nm->mkNode(EQUAL, t, const_rational_2);
  Node ite_251 = nm->mkNode(ITE, equal_89, t, t);
  Node ite_250 = nm->mkNode(ITE, equal_34, const_rational_0, ite_251);
  Node ite_249 = nm->mkNode(ITE, equal_32, const_rational_0, ite_250);
  Node ite_248 = nm->mkNode(ITE, equal_70, t, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_36, t, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_38, const_rational_0, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_40, const_rational_0, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_42, t, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_44, t, ite_244);
  Node ite_242 = nm->mkNode(ITE, equal_46, const_rational_0, ite_243);
  Node ite_241 = nm->mkNode(ITE, equal_48, const_rational_0, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_52, t, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_56, const_rational_0, ite_240);
  Node equal_238 = nm->mkNode(EQUAL, t, const_rational_3);
  Node ite_237 = nm->mkNode(ITE, equal_89, t, const_rational_2);
  Node ite_236 = nm->mkNode(ITE, equal_34, const_rational_1, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_32, const_rational_0, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_70, t, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_36, const_rational_2, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_38, const_rational_1, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_40, const_rational_0, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_42, t, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_44, const_rational_2, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_46, const_rational_1, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_48, const_rational_0, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_54, s, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_56, s, ite_226);
  Node equal_224 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_160 = nm->mkNode(ITE, equal_50, t, t);
  Node ite_223 = nm->mkNode(ITE, equal_34, t, ite_160);
  Node ite_222 = nm->mkNode(ITE, equal_32, t, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_70, const_rational_0, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_36, const_rational_0, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_38, const_rational_0, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_40, const_rational_0, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_42, t, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_44, t, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_46, t, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_52, const_rational_0, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_54, const_rational_0, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_56, const_rational_0, ite_213);
  Node equal_211 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_210 = nm->mkNode(ITE, equal_50, const_rational_4, t);
  Node ite_209 = nm->mkNode(ITE, equal_34, t, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_32, const_rational_4, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_70, const_rational_1, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_36, const_rational_0, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_38, const_rational_1, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_40, const_rational_0, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_42, t, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_44, const_rational_4, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_48, s, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_52, const_rational_1, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_54, const_rational_0, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_56, s, ite_199);
  Node equal_197 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_196 = nm->mkNode(ITE, equal_34, const_rational_4, t);
  Node ite_195 = nm->mkNode(ITE, equal_32, const_rational_4, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_70, const_rational_2, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_36, const_rational_2, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_38, const_rational_0, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_40, const_rational_0, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_42, t, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_46, const_rational_4, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_89, t, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_48, s, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_52, const_rational_2, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_54, s, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_56, const_rational_0, ite_185);
  Node equal_88 = nm->mkNode(EQUAL, t, const_rational_7);
  Node ite_183 = nm->mkNode(ITE, equal_32, const_rational_4, const_rational_3);
  Node ite_182 = nm->mkNode(ITE, equal_36, const_rational_2, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_38, const_rational_1, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_34, const_rational_5, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_40, const_rational_0, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_50, const_rational_6, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_44, s, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_46, s, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_48, s, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_52, s, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_54, s, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_56, s, ite_173);
  Node ite_87 = nm->mkNode(ITE, equal_88, t, t);
  Node ite_171 = nm->mkNode(ITE, equal_89, ite_87, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_36, ite_172, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_38, ite_172, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_40, ite_172, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_44, ite_172, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_46, ite_172, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_48, ite_172, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_52, ite_172, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_54, ite_172, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_56, ite_172, ite_163);
  Node equal_161 = nm->mkNode(EQUAL, t, const_rational_8);
  Node ite_159 = nm->mkNode(ITE, equal_32, t, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_70, t, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_36, t, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_89, ite_87, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_38, t, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_42, const_rational_0, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_44, const_rational_0, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_46, const_rational_0, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_48, const_rational_0, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_52, const_rational_0, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_54, const_rational_0, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_56, const_rational_0, ite_149);
  Node equal_147 = nm->mkNode(EQUAL, t, const_rational_9);
  Node ite_146 = nm->mkNode(ITE, equal_34, t, const_rational_8);
  Node ite_145 = nm->mkNode(ITE, equal_32, const_rational_8, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_70, t, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_89, ite_87, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_36, const_rational_8, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_40, s, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_42, const_rational_1, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_44, const_rational_0, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_46, const_rational_1, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_48, const_rational_0, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_52, const_rational_1, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_54, const_rational_0, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_56, s, ite_135);
  Node equal_133 = nm->mkNode(EQUAL, t, const_rational_10);
  Node ite_132 = nm->mkNode(ITE, equal_70, t, const_rational_8);
  Node ite_131 = nm->mkNode(ITE, equal_34, const_rational_8, ite_132);
  Node ite_130 = nm->mkNode(ITE, equal_38, const_rational_8, ite_131);
  Node ite_129 = nm->mkNode(ITE, equal_40, s, ite_130);
  Node ite_128 = nm->mkNode(ITE, equal_42, const_rational_2, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_44, const_rational_2, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_46, const_rational_0, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_50, t, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_48, const_rational_0, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_52, const_rational_2, ite_124);
  Node ite_122 = nm->mkNode(ITE, equal_54, s, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_89, ite_87, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_56, const_rational_0, ite_121);
  Node equal_119 = nm->mkNode(EQUAL, t, const_rational_11);
  Node ite_118 = nm->mkNode(ITE, equal_50, const_rational_10, const_rational_9);
  Node ite_117 = nm->mkNode(ITE, equal_32, const_rational_8, ite_118);
  Node ite_116 = nm->mkNode(ITE, equal_89, ite_87, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_36, s, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_38, s, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_40, s, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_42, const_rational_3, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_44, const_rational_2, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_46, const_rational_1, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_48, const_rational_0, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_52, s, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_54, s, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_56, s, ite_107);
  Node equal_105 = nm->mkNode(EQUAL, t, const_rational_12);
  Node ite_104 = nm->mkNode(ITE, equal_50, t, ite_87);
  Node ite_103 = nm->mkNode(ITE, equal_34, t, ite_104);
  Node ite_102 = nm->mkNode(ITE, equal_70, const_rational_8, ite_103);
  Node ite_101 = nm->mkNode(ITE, equal_36, const_rational_8, ite_102);
  Node ite_100 = nm->mkNode(ITE, equal_38, const_rational_8, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_40, s, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_42, const_rational_4, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_44, const_rational_4, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_46, const_rational_4, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_48, s, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_52, const_rational_0, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_54, const_rational_0, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_56, const_rational_0, ite_93);
  Node equal_91 = nm->mkNode(EQUAL, t, const_rational_13);
  Node ite_86 = nm->mkNode(ITE, equal_89, ite_87, const_rational_12);
  Node ite_85 = nm->mkNode(ITE, equal_32, s, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_70, const_rational_9, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_36, const_rational_8, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_38, s, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_40, s, ite_82);
  Node ite_80 = nm->mkNode(ITE, equal_42, const_rational_5, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_44, const_rational_4, ite_80);
  Node ite_78 = nm->mkNode(ITE, equal_46, s, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_48, s, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_52, const_rational_1, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_54, const_rational_0, ite_76);
  Node ite_74 = nm->mkNode(ITE, equal_56, s, ite_75);
  Node equal_73 = nm->mkNode(EQUAL, t, const_rational_14);
  Node ite_69 = nm->mkNode(ITE, equal_34, const_rational_12, s);
  Node ite_68 = nm->mkNode(ITE, equal_70, const_rational_10, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_36, s, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_38, const_rational_8, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_40, s, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_42, const_rational_6, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_44, s, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_46, const_rational_4, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_48, s, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_52, const_rational_2, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_54, s, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_56, const_rational_0, ite_59);
  Node ite_31 = nm->mkNode(ITE, equal_32, s, s);
  Node ite_30 = nm->mkNode(ITE, equal_34, s, ite_31);
  Node ite_29 = nm->mkNode(ITE, equal_36, s, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_38, s, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_40, s, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_42, s, ite_27);
  Node ite_25 = nm->mkNode(ITE, equal_44, s, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_46, s, ite_25);
  Node ite_23 = nm->mkNode(ITE, equal_48, s, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_50, s, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_52, s, ite_22);
  Node ite_20 = nm->mkNode(ITE, equal_54, s, ite_21);
  Node ite_19 = nm->mkNode(ITE, equal_56, s, ite_20);
  Node ite_18 = nm->mkNode(ITE, equal_73, ite_58, ite_19);
  Node ite_17 = nm->mkNode(ITE, equal_91, ite_74, ite_18);
  Node ite_16 = nm->mkNode(ITE, equal_105, ite_92, ite_17);
  Node ite_15 = nm->mkNode(ITE, equal_119, ite_106, ite_16);
  Node ite_14 = nm->mkNode(ITE, equal_133, ite_120, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_147, ite_134, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_89, ite_87, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_161, ite_148, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_88, ite_162, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_197, ite_184, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_211, ite_198, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_224, ite_212, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_238, ite_225, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_252, ite_239, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_266, ite_253, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_267, s, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_282, ite_268, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_284, ite_283, ite_2);
  return ite_1;
}

// (define-fun int_bvor_1_min ((s Int) (t Int)) Int (ite (= 0 s) t s))
Node int_bvor_1_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_2 = nm->mkNode(EQUAL, const_rational_0, s);
  Node ite_1 = nm->mkNode(ITE, equal_2, t, s);
  return ite_1;
}

// (define-fun int_bvor_1_trivial ((s Int) (t Int)) Int (ite (= s t) t 1))
Node int_bvor_1_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_3 = nm->mkNode(EQUAL, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_1 = nm->mkNode(ITE, equal_3, t, const_rational_1);
  return ite_1;
}

// (define-fun int_bvor_2_min ((s Int) (t Int)) Int (ite (= 0 s) t (ite (= s t)
// t (ite (= 0 t) s 3))))
Node int_bvor_2_min(Node s, Node t)
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

// (define-fun int_bvor_2_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) t t) (ite (= t 0) (ite (= s 1) s (ite (= s 2) s s)) (ite (= s t) t (ite (=
// s 1) 3 (ite (= s 2) 3 s))))))
Node int_bvor_2_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_17 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_11 = nm->mkNode(EQUAL, s, t);
  Node ite_16 = nm->mkNode(ITE, equal_11, t, t);
  Node equal_14 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_9 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_7 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_13 = nm->mkNode(ITE, equal_7, s, s);
  Node ite_12 = nm->mkNode(ITE, equal_9, s, ite_13);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node ite_5 = nm->mkNode(ITE, equal_7, const_rational_3, s);
  Node ite_4 = nm->mkNode(ITE, equal_9, const_rational_3, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_11, t, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_14, ite_12, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_17, ite_16, ite_2);
  return ite_1;
}

// (define-fun int_bvor_3_min ((s Int) (t Int)) Int (ite (= s 0) t (ite (= t 0)
// s (ite (= s t) t (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5
// (ite (= s 5) s (ite (= s 7) (ite (= s t) t s) 7))))) (ite (= t 2) (ite (= s
// 7) (ite (= s t) t s) (ite (= s 1) 3 (ite (= s 6) s (ite (= s 5) 7 (ite (= s
// 4) 6 s))))) (ite (= t 3) (ite (= s 1) t (ite (= s 2) t (ite (= s 4) 7 (ite (=
// s 7) (ite (= s t) t s) (ite (= s 5) 7 7))))) (ite (= s 7) (ite (= s t) t s)
// (ite (= t 4) (ite (= s 1) (ite (= s 1) 5 (ite (= s 2) 6 (ite (= s 3) 7 s)))
// (ite (= s 2) (ite (= s 1) 5 (ite (= s 2) 6 (ite (= s 3) 7 s))) (ite (= s 3)
// (ite (= s 1) 5 (ite (= s 2) 6 (ite (= s 3) 7 s))) s))) (ite (= t 5) (ite (= s
// 1) t (ite (= s 2) 7 (ite (= s 3) 7 (ite (= s 4) t (ite (= t 4) s 7))))) (ite
// (= s 1) 7 (ite (= s 2) t (ite (= s 3) 7 (ite (= s 4) t (ite (= s 5) 7 (ite (=
// t 4) s 7))))))))))))))))
Node int_bvor_3_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_64 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_62 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_41 = nm->mkNode(EQUAL, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_61 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_24 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_21 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_19 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_40 = nm->mkNode(ITE, equal_41, t, s);
  Node ite_60 = nm->mkNode(ITE, equal_42, ite_40, const_rational_7);
  Node ite_59 = nm->mkNode(ITE, equal_19, s, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_21, const_rational_5, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_22, s, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_24, const_rational_3, ite_57);
  Node equal_55 = nm->mkNode(EQUAL, t, const_rational_2);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_54 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_53 = nm->mkNode(ITE, equal_21, const_rational_6, s);
  Node ite_52 = nm->mkNode(ITE, equal_19, const_rational_7, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_54, s, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_26, const_rational_3, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_42, ite_40, ite_50);
  Node equal_48 = nm->mkNode(EQUAL, t, const_rational_3);
  Node ite_47 = nm->mkNode(ITE, equal_19, const_rational_7, const_rational_7);
  Node ite_46 = nm->mkNode(ITE, equal_42, ite_40, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_21, const_rational_7, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_24, t, ite_45);
  Node ite_43 = nm->mkNode(ITE, equal_26, t, ite_44);
  Node equal_17 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_38 = nm->mkNode(ITE, equal_22, const_rational_7, s);
  Node ite_37 = nm->mkNode(ITE, equal_24, const_rational_6, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_26, const_rational_5, ite_37);
  Node ite_35 = nm->mkNode(ITE, equal_22, ite_36, s);
  Node ite_34 = nm->mkNode(ITE, equal_24, ite_36, ite_35);
  Node ite_33 = nm->mkNode(ITE, equal_26, ite_36, ite_34);
  Node equal_32 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_15 = nm->mkNode(ITE, equal_17, s, const_rational_7);
  Node ite_31 = nm->mkNode(ITE, equal_21, t, ite_15);
  Node ite_30 = nm->mkNode(ITE, equal_22, const_rational_7, ite_31);
  Node ite_29 = nm->mkNode(ITE, equal_24, const_rational_7, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_26, t, ite_29);
  Node ite_14 = nm->mkNode(ITE, equal_19, const_rational_7, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_21, t, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_22, const_rational_7, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_24, t, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_26, const_rational_7, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_32, ite_28, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_17, ite_33, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_42, ite_40, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_48, ite_43, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_55, ite_49, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_61, ite_56, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_41, t, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_62, s, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_64, t, ite_2);
  return ite_1;
}

// (define-fun int_bvor_3_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) t t) (ite (= t 0) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s (ite (= s
// 7) (ite (= s t) t s) (ite (= s 4) s (ite (= s 5) s s)))))) (ite (= s t) t
// (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s 5) s (ite
// (= s 7) (ite (= s t) t s) 7))))) (ite (= t 2) (ite (= s 7) (ite (= s t) t s)
// (ite (= s 1) 3 (ite (= s 6) s (ite (= s 5) 7 (ite (= s 4) 6 s))))) (ite (= t
// 3) (ite (= s 1) t (ite (= s 2) t (ite (= s 4) 7 (ite (= s 7) (ite (= s t) t
// s) (ite (= s 5) 7 7))))) (ite (= s 7) (ite (= s t) t s) (ite (= t 4) (ite (=
// s 1) (ite (= s 1) 5 (ite (= s 2) 6 (ite (= s 3) 7 s))) (ite (= s 2) (ite (= s
// 1) 5 (ite (= s 2) 6 (ite (= s 3) 7 s))) (ite (= s 3) (ite (= s 1) 5 (ite (= s
// 2) 6 (ite (= s 3) 7 s))) s))) (ite (= t 5) (ite (= s 1) t (ite (= s 2) 7 (ite
// (= s 3) 7 (ite (= s 4) t (ite (= t 4) s 7))))) (ite (= s 1) 7 (ite (= s 2) t
// (ite (= s 3) 7 (ite (= s 4) t (ite (= s 5) 7 (ite (= t 4) s 7))))))))))))))))
Node int_bvor_3_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_71 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_41 = nm->mkNode(EQUAL, s, t);
  Node ite_70 = nm->mkNode(ITE, equal_41, t, t);
  Node equal_68 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_24 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_40 = nm->mkNode(ITE, equal_41, t, s);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_21 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_19 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_67 = nm->mkNode(ITE, equal_19, s, s);
  Node ite_66 = nm->mkNode(ITE, equal_21, s, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_42, ite_40, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_22, s, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_24, s, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_26, s, ite_63);
  Node equal_61 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_60 = nm->mkNode(ITE, equal_42, ite_40, const_rational_7);
  Node ite_59 = nm->mkNode(ITE, equal_19, s, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_21, const_rational_5, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_22, s, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_24, const_rational_3, ite_57);
  Node equal_55 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_54 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_53 = nm->mkNode(ITE, equal_21, const_rational_6, s);
  Node ite_52 = nm->mkNode(ITE, equal_19, const_rational_7, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_54, s, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_26, const_rational_3, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_42, ite_40, ite_50);
  Node equal_48 = nm->mkNode(EQUAL, t, const_rational_3);
  Node ite_47 = nm->mkNode(ITE, equal_19, const_rational_7, const_rational_7);
  Node ite_46 = nm->mkNode(ITE, equal_42, ite_40, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_21, const_rational_7, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_24, t, ite_45);
  Node ite_43 = nm->mkNode(ITE, equal_26, t, ite_44);
  Node equal_17 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_38 = nm->mkNode(ITE, equal_22, const_rational_7, s);
  Node ite_37 = nm->mkNode(ITE, equal_24, const_rational_6, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_26, const_rational_5, ite_37);
  Node ite_35 = nm->mkNode(ITE, equal_22, ite_36, s);
  Node ite_34 = nm->mkNode(ITE, equal_24, ite_36, ite_35);
  Node ite_33 = nm->mkNode(ITE, equal_26, ite_36, ite_34);
  Node equal_32 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_15 = nm->mkNode(ITE, equal_17, s, const_rational_7);
  Node ite_31 = nm->mkNode(ITE, equal_21, t, ite_15);
  Node ite_30 = nm->mkNode(ITE, equal_22, const_rational_7, ite_31);
  Node ite_29 = nm->mkNode(ITE, equal_24, const_rational_7, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_26, t, ite_29);
  Node ite_14 = nm->mkNode(ITE, equal_19, const_rational_7, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_21, t, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_22, const_rational_7, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_24, t, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_26, const_rational_7, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_32, ite_28, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_17, ite_33, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_42, ite_40, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_48, ite_43, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_55, ite_49, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_61, ite_56, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_41, t, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_68, ite_62, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_71, ite_70, ite_2);
  return ite_1;
}

// (define-fun int_bvor_4_min ((s Int) (t Int)) Int (ite (>= 3 s) (ite (not (= s
// 3)) (ite (>= t (* s t)) (ite (not (= s 2)) (ite (>= s (* s t)) (ite (not (>=
// t s)) (* s s) t) (ite (>= 3 t) (* s 3) (ite (= t 4) (+ s t) (ite (= t 5) (* s
// t) (ite (= t 6) (+ s t) (ite (= t 7) (* s t) (ite (= t 8) (+ s t) (ite (= t
// 13) (* s t) (ite (= t 12) (+ s t) (ite (= t 9) (* s t) (ite (= t 10) (+ s t)
// (ite (= t 11) (* s t) (* s 15))))))))))))) (+ s t)) (ite (>= s (* s t)) (* t
// 3) (ite (>= t (* s s)) (ite (>= (* s s) t) (+ s t) (ite (= t 5) (+ s t) (ite
// (= t 6) (* s 3) (ite (= t 7) t (ite (= t 8) (+ s t) (ite (= t 9) (+ s t) (ite
// (= t 10) (* s 5) (ite (= t 13) (+ s t) (ite (= t 11) t (ite (= t 12) (+ s t)
// t)))))))))) t))) (ite (>= t (* s t)) (+ s t) (ite (>= s (* s t)) (* s t) (ite
// (>= t s) (ite (>= t (* s s)) (ite (>= (* s s) t) 11 (ite (= t 10) 11 (ite (=
// t 11) t (* s 5)))) (ite (= t 8) (+ s t) (ite (>= 3 t) t (ite (= t 4) (+ s t)
// (ite (= t 5) 7 (ite (= t 6) 7 t)))))) s)))) (ite (>= t (* s t)) (+ s t) (ite
// (>= s (* s t)) (ite (= s 4) (* t 5) (ite (= s 5) (* s t) (ite (= s 6) (+ s t)
// (ite (= s 7) (* s t) (ite (= s 8) (+ s t) (ite (= s 9) (* s t) (ite (= s 10)
// (+ s t) (ite (= s 11) (* s t) (ite (= s 12) (+ s t) (ite (= s 15) (* s t)
// (ite (= s 13) (* s t) (+ s t)))))))))))) (ite (>= (* t t) s) (ite (>= t s)
// (ite (>= s t) t (ite (= t 5) t (ite (= t 6) (ite (= s 5) 7 t) (ite (= t 7)
// (ite (= s 4) t (ite (= s 5) t t)) (ite (= t 8) (+ s t) (ite (= t 9) (ite (= s
// 4) (+ s t) (ite (= s 5) 13 (ite (= s 6) (+ s t) (ite (= s 8) t 15)))) (ite (=
// t 10) (ite (= s 9) 11 (ite (= s 4) (+ s t) (ite (= s 5) (+ s t) (ite (= s 6)
// 14 (ite (= s 7) 15 t))))) (ite (= t 11) (ite (= s 4) (+ s t) (ite (= s 10) t
// (ite (= s 5) (* s 3) (ite (= s 6) 15 (ite (= s 7) 15 (ite (= s 8) t t))))))
// (ite (= t 12) (ite (= s 4) (* s 3) (ite (= s 5) 13 (ite (= s 6) 14 (ite (= s
// 7) 15 (ite (= s 8) t (ite (= s 9) 13 (ite (= s 10) 14 15))))))) (ite (= t 13)
// (ite (= s 4) t (ite (= s 5) t (ite (= s 12) t (ite (= s 6) 15 (ite (= s 7) 15
// (ite (= s 8) t (ite (= s 9) t (ite (= s 10) 15 15)))))))) (ite (= s 4) t (ite
// (= s 5) (* s 3) (ite (= s 6) t (ite (= s 14) t (ite (= s 7) 15 (ite (= s 8) t
// (ite (= s 9) 15 (ite (= s 10) t (ite (= s 11) 15 (ite (= s 12) t
// 15)))))))))))))))))))) (ite (= s 15) (ite (>= s (* s t)) (* s t) (ite (>= (*
// t t) s) (ite (>= t s) t (ite (>= s (* t 2)) (ite (>= s (* t 3)) (ite (= s (*
// t 3)) (* t 3) s) s) s)) (ite (= t 3) (* t 5) s))) (ite (>= 3 t) (ite (not (=
// t 3)) (+ s t) (ite (>= s (* t t)) 11 (ite (>= s (* t 2)) (ite (= s (* t 2)) 7
// (ite (= s 7) s (+ s t))) (ite (= s 4) (+ s t) 7)))) (ite (>= s (* t 2)) (ite
// (>= s (* t 3)) (ite (= s (* t 3)) (* t 3) (ite (= s 13) s s)) (ite (= s 14)
// (ite (= t 7) 15 (ite (= t 5) (* t 3) s)) (ite (= s (* t 2)) (ite (= t 4) (+ s
// t) (ite (= t 5) (+ s t) 14)) (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 11)
// (* t 3) (ite (= s 12) 13 s)) 15))))) (ite (= t 4) (ite (= s 5) s (ite (= s 6)
// s s)) (ite (= t 5) (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) (+ s t) 13)))
// (ite (= t 6) (ite (= s 7) s (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (=
// s 10) 14 15)))) (ite (= t 7) (ite (= s 8) (+ s t) (ite (= s 9) 15 (ite (= s
// 10) 15 (ite (= s 11) 15 (ite (= s 12) 15 15))))) (ite (= t 8) (ite (= s 9) s
// (ite (= s 10) s (ite (= s 11) s (ite (= s 12) s (ite (= s 14) s s))))) (ite
// (= t 9) (ite (= s 10) 11 (ite (= s 11) s (ite (= s 14) 15 (ite (= s 12) 13
// s)))) (ite (= t 10) (ite (= s 11) s (ite (= s 12) 14 (ite (= s 14) s 15)))
// (ite (= t 11) (ite (= s 12) 15 (ite (= s 13) 15 15)) (ite (= t 12) (ite (= s
// 13) s s) 15))))))))))))) (ite (not (= t 3)) (ite (>= s (* t (* t t))) (ite (=
// s (* t (* t t))) (* t 5) (ite (= s 9) (+ s t) (ite (= s 10) (* t 5) (ite (= s
// 11) s (ite (= s 12) (+ s t) (ite (= s 13) (+ s t) (ite (= s 14) (* t 7) (ite
// (>= t (* s t)) (+ s t) (ite (>= s (* s t)) (* s t) (ite (>= (* t t) s) (ite
// (>= t s) t (ite (>= s (* t 2)) (ite (>= s (* t 3)) (ite (= s (* t 3)) (* t 3)
// s) s) s)) (ite (= t 3) (* t 5) s))))))))))) (ite (>= s (* t 3)) (ite (= s (*
// t 3)) (* t 3) s) (+ s t))) (ite (= s 10) 11 (ite (= s 11) s (* t 5)))))))))
Node int_bvor_4_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node geq_257 = nm->mkNode(GEQ, const_rational_3, s);
  Node equal_256 = nm->mkNode(EQUAL, s, const_rational_3);
  Node not_255 = nm->mkNode(NOT, equal_256);
  Node mult_43 = nm->mkNode(MULT, s, t);
  Node geq_45 = nm->mkNode(GEQ, t, mult_43);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_254 = nm->mkNode(EQUAL, s, const_rational_2);
  Node not_253 = nm->mkNode(NOT, equal_254);
  Node geq_44 = nm->mkNode(GEQ, s, mult_43);
  Node geq_40 = nm->mkNode(GEQ, t, s);
  Node not_252 = nm->mkNode(NOT, geq_40);
  Node mult_222 = nm->mkNode(MULT, s, s);
  Node ite_251 = nm->mkNode(ITE, not_252, mult_222, t);
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
  Node mult_250 = nm->mkNode(MULT, s, const_rational_15);
  Node ite_249 = nm->mkNode(ITE, equal_78, mult_43, mult_250);
  Node ite_248 = nm->mkNode(ITE, equal_82, plus_16, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_87, mult_43, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_75, plus_16, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_170, mult_43, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_93, plus_16, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_101, mult_43, ite_244);
  Node ite_242 = nm->mkNode(ITE, equal_107, plus_16, ite_243);
  Node ite_241 = nm->mkNode(ITE, equal_113, mult_43, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_117, plus_16, ite_241);
  Node ite_239 = nm->mkNode(ITE, geq_139, mult_161, ite_240);
  Node ite_238 = nm->mkNode(ITE, geq_44, ite_251, ite_239);
  Node ite_237 = nm->mkNode(ITE, not_253, ite_238, plus_16);
  Node mult_18 = nm->mkNode(MULT, t, const_rational_3);
  Node geq_223 = nm->mkNode(GEQ, t, mult_222);
  Node geq_221 = nm->mkNode(GEQ, mult_222, t);
  Node mult_220 = nm->mkNode(MULT, s, const_rational_5);
  Node ite_236 = nm->mkNode(ITE, equal_75, plus_16, t);
  Node ite_235 = nm->mkNode(ITE, equal_78, t, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_170, plus_16, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_82, mult_220, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_87, plus_16, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_93, plus_16, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_101, t, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_107, mult_161, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_113, plus_16, ite_229);
  Node ite_227 = nm->mkNode(ITE, geq_221, plus_16, ite_228);
  Node ite_226 = nm->mkNode(ITE, geq_223, ite_227, t);
  Node ite_225 = nm->mkNode(ITE, geq_44, mult_18, ite_226);
  Node ite_224 = nm->mkNode(ITE, geq_45, ite_237, ite_225);
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
  Node ite_207 = nm->mkNode(ITE, not_255, ite_224, ite_208);
  Node equal_135 = nm->mkNode(EQUAL, s, const_rational_4);
  Node mult_8 = nm->mkNode(MULT, t, const_rational_5);
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
  Node ite_196 = nm->mkNode(ITE, equal_135, mult_8, ite_197);
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
  Node geq_21 = nm->mkNode(GEQ, s, mult_18);
  Node equal_20 = nm->mkNode(EQUAL, s, mult_18);
  Node ite_17 = nm->mkNode(ITE, equal_20, mult_18, s);
  Node ite_36 = nm->mkNode(ITE, geq_21, ite_17, s);
  Node ite_35 = nm->mkNode(ITE, geq_37, ite_36, s);
  Node ite_34 = nm->mkNode(ITE, geq_40, t, ite_35);
  Node equal_33 = nm->mkNode(EQUAL, t, const_rational_3);
  Node ite_32 = nm->mkNode(ITE, equal_33, mult_8, s);
  Node ite_31 = nm->mkNode(ITE, geq_41, ite_34, ite_32);
  Node ite_30 = nm->mkNode(ITE, geq_44, mult_43, ite_31);
  Node not_59 = nm->mkNode(NOT, equal_33);
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
  Node ite_22 = nm->mkNode(ITE, equal_56, mult_8, ite_23);
  Node ite_15 = nm->mkNode(ITE, geq_21, ite_17, plus_16);
  Node ite_14 = nm->mkNode(ITE, geq_58, ite_22, ite_15);
  Node ite_7 = nm->mkNode(ITE, equal_10, s, mult_8);
  Node ite_6 = nm->mkNode(ITE, equal_12, const_rational_11, ite_7);
  Node ite_5 = nm->mkNode(ITE, not_59, ite_14, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_41, ite_60, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_44, ite_196, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_45, plus_16, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_257, ite_207, ite_2);
  return ite_1;
}

// (define-fun int_bvor_4_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) t t) (ite (= t 0) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s (ite (= s
// 4) s (ite (= s 5) s (ite (= s 15) s (ite (= s 6) s (ite (= s 7) s (ite (= s
// 8) s (ite (= s 9) s (ite (= s 10) s (ite (= s 11) s (ite (= s 12) s (ite (= s
// 14) s s)))))))))))))) (ite (= s t) t (ite (= t 1) (ite (= s 2) 3 (ite (= s 3)
// s (ite (= s 4) 5 (ite (= s 5) s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9
// (ite (= s 9) s (ite (= s 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s
// 13) s (ite (= s 14) 15 s))))))))))))) (ite (= t 2) (ite (= s 1) (ite (= s 1)
// 3 (ite (= s 3) s (ite (= s 4) 6 (ite (= s 5) 7 (ite (= s 6) s (ite (= s 7) s
// (ite (= s 8) 10 (ite (= s 9) 11 (ite (= s 10) s (ite (= s 11) s (ite (= s 12)
// 14 (ite (= s 14) s 15)))))))))))) (ite (= s 3) (ite (= s 3) s (ite (= s 4) 6
// (ite (= s 5) 7 (ite (= s 6) s (ite (= s 7) s (ite (= s 8) 10 (ite (= s 9) 11
// (ite (= s 10) s (ite (= s 11) s (ite (= s 12) 14 (ite (= s 14) s
// 15))))))))))) (ite (= s 4) (ite (= s 1) 3 (ite (= s 3) s (ite (= s 4) 6 (ite
// (= s 5) 7 (ite (= s 6) s (ite (= s 7) s (ite (= s 8) 10 (ite (= s 9) 11 (ite
// (= s 10) s (ite (= s 11) s (ite (= s 12) 14 (ite (= s 14) s 15))))))))))))
// (ite (= s 5) (ite (= s 1) 3 (ite (= s 3) s (ite (= s 4) 6 (ite (= s 5) 7 (ite
// (= s 6) s (ite (= s 7) s (ite (= s 8) 10 (ite (= s 9) 11 (ite (= s 10) s (ite
// (= s 11) s (ite (= s 12) 14 (ite (= s 14) s 15)))))))))))) (ite (= s 6) (ite
// (= s 1) 3 (ite (= s 3) s (ite (= s 4) 6 (ite (= s 5) 7 (ite (= s 6) s (ite (=
// s 7) s (ite (= s 8) 10 (ite (= s 9) 11 (ite (= s 10) s (ite (= s 11) s (ite
// (= s 12) 14 (ite (= s 14) s 15)))))))))))) (ite (= s 7) (ite (= s 1) 3 (ite
// (= s 3) s (ite (= s 4) 6 (ite (= s 5) 7 (ite (= s 6) s (ite (= s 7) s (ite (=
// s 8) 10 (ite (= s 9) 11 (ite (= s 10) s (ite (= s 11) s (ite (= s 12) 14 (ite
// (= s 14) s 15)))))))))))) (ite (= s 8) (ite (= s 1) 3 (ite (= s 3) s (ite (=
// s 4) 6 (ite (= s 5) 7 (ite (= s 6) s (ite (= s 7) s (ite (= s 8) 10 (ite (= s
// 9) 11 (ite (= s 10) s (ite (= s 11) s (ite (= s 12) 14 (ite (= s 14) s
// 15)))))))))))) (ite (= s 9) (ite (= s 1) 3 (ite (= s 3) s (ite (= s 4) 6 (ite
// (= s 5) 7 (ite (= s 6) s (ite (= s 7) s (ite (= s 8) 10 (ite (= s 9) 11 (ite
// (= s 10) s (ite (= s 11) s (ite (= s 12) 14 (ite (= s 14) s 15))))))))))))
// (ite (= s 10) (ite (= s 1) 3 (ite (= s 3) s (ite (= s 4) 6 (ite (= s 5) 7
// (ite (= s 6) s (ite (= s 7) s (ite (= s 8) 10 (ite (= s 9) 11 (ite (= s 10) s
// (ite (= s 11) s (ite (= s 12) 14 (ite (= s 14) s 15)))))))))))) (ite (= s 11)
// (ite (= s 1) 3 (ite (= s 3) s (ite (= s 4) 6 (ite (= s 5) 7 (ite (= s 6) s
// (ite (= s 7) s (ite (= s 8) 10 (ite (= s 9) 11 (ite (= s 10) s (ite (= s 11)
// s (ite (= s 12) 14 (ite (= s 14) s 15)))))))))))) (ite (= s 12) (ite (= s 1)
// 3 (ite (= s 3) s (ite (= s 4) 6 (ite (= s 5) 7 (ite (= s 6) s (ite (= s 7) s
// (ite (= s 8) 10 (ite (= s 9) 11 (ite (= s 10) s (ite (= s 11) s (ite (= s 12)
// 14 (ite (= s 14) s 15)))))))))))) (ite (= s 13) (ite (= s 1) 3 (ite (= s 3) s
// (ite (= s 4) 6 (ite (= s 5) 7 (ite (= s 6) s (ite (= s 7) s (ite (= s 8) 10
// (ite (= s 9) 11 (ite (= s 10) s (ite (= s 11) s (ite (= s 12) 14 (ite (= s
// 14) s 15)))))))))))) s)))))))))))) (ite (= t 3) (ite (= s 1) t (ite (= s 2) t
// (ite (= s 4) 7 (ite (= s 5) 7 (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 11
// (ite (= s 9) 11 (ite (= s 15) (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite
// (= s 4) 5 (ite (= s 5) s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9 (ite (=
// s 9) s (ite (= s 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite
// (= s 14) 15 s))))))))))))) (ite (= t 2) s s)) (ite (= s 10) 11 (ite (= s 11)
// s (ite (= s 12) 15 (ite (= s 13) 15 15))))))))))))) (ite (= t 4) (ite (= s 1)
// 5 (ite (= s 2) 6 (ite (= s 3) 7 (ite (= s 5) s (ite (= s 15) (ite (= t 1)
// (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s 5) s (ite (= s 6) 7
// (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s 10) 11 (ite (= s 11) s
// (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15 s))))))))))))) (ite (= t 2)
// s s)) (ite (= s 6) s (ite (= s 7) s (ite (= s 8) 12 (ite (= s 14) s (ite (= s
// 9) 13 (ite (= s 10) 14 (ite (= s 11) 15 (ite (= s 12) s s))))))))))))) (ite
// (= t 5) (ite (= s 1) t (ite (= s 2) 7 (ite (= s 3) 7 (ite (= s 4) t (ite (= s
// 6) 7 (ite (= s 7) s (ite (= s 8) 13 (ite (= s 9) 13 (ite (= s 10) 15 (ite (=
// s 11) 15 (ite (= s 12) 13 (ite (= s 15) (ite (= t 1) (ite (= s 2) 3 (ite (= s
// 3) s (ite (= s 4) 5 (ite (= s 5) s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8)
// 9 (ite (= s 9) s (ite (= s 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s
// 13) s (ite (= s 14) 15 s))))))))))))) (ite (= t 2) s s)) (ite (= s 13) s
// 15))))))))))))) (ite (= t 6) (ite (= s 1) 7 (ite (= s 2) t (ite (= s 3) 7
// (ite (= s 4) t (ite (= s 5) 7 (ite (= s 7) s (ite (= s 8) 14 (ite (= s 15)
// (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s 5) s (ite
// (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s 10) 11 (ite
// (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15 s)))))))))))))
// (ite (= t 2) s s)) (ite (= s 9) 15 (ite (= s 10) 14 (ite (= s 11) 15 (ite (=
// s 12) 14 (ite (= s 13) 15 s))))))))))))) (ite (= t 7) (ite (= s 1) t (ite (=
// s 2) t (ite (= s 3) t (ite (= s 4) t (ite (= s 5) t (ite (= s 15) (ite (= t
// 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s 5) s (ite (= s 6) 7
// (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s 10) 11 (ite (= s 11) s
// (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15 s))))))))))))) (ite (= t 2)
// s s)) (ite (= s 6) t (ite (= s 8) 15 (ite (= s 9) 15 (ite (= s 10) 15 (ite (=
// s 11) 15 (ite (= s 12) 15 (ite (= s 13) 15 15))))))))))))) (ite (= t 8) (ite
// (= s 15) (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s
// 5) s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s
// 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15
// s))))))))))))) (ite (= t 2) s s)) (ite (= s 1) 9 (ite (= s 2) 10 (ite (= s 3)
// 11 (ite (= s 4) 12 (ite (= s 5) 13 (ite (= s 14) s (ite (= s 6) 14 (ite (= s
// 7) 15 (ite (= s 9) s (ite (= s 10) s (ite (= s 11) s (ite (= s 12) s
// s))))))))))))) (ite (= t 9) (ite (= s 1) t (ite (= s 2) 11 (ite (= s 3) 11
// (ite (= s 4) 13 (ite (= s 5) 13 (ite (= s 6) 15 (ite (= s 7) 15 (ite (= s 8)
// t (ite (= s 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite (= s
// 14) 15 (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s 5)
// s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s 10)
// 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15
// s))))))))))))) (ite (= t 2) s s))))))))))))))) (ite (= t 10) (ite (= s 1) 11
// (ite (= s 2) t (ite (= s 3) 11 (ite (= s 4) 14 (ite (= s 5) 15 (ite (= s 6)
// 14 (ite (= s 15) (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5
// (ite (= s 5) s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s
// (ite (= s 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite (= s
// 14) 15 s))))))))))))) (ite (= t 2) s s)) (ite (= s 7) 15 (ite (= s 8) t (ite
// (= s 9) 11 (ite (= s 11) s (ite (= s 12) 14 (ite (= s 13) 15 s)))))))))))))
// (ite (= t 11) (ite (= s 1) t (ite (= s 2) t (ite (= s 3) t (ite (= s 4) 15
// (ite (= s 5) 15 (ite (= s 6) 15 (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) t
// (ite (= s 10) t (ite (= s 12) 15 (ite (= s 13) 15 (ite (= s 15) (ite (= t 1)
// (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s 5) s (ite (= s 6) 7
// (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s 10) 11 (ite (= s 11) s
// (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15 s))))))))))))) (ite (= t 2)
// s s)) 15))))))))))))) (ite (= t 12) (ite (= s 1) 13 (ite (= s 2) 14 (ite (= s
// 3) 15 (ite (= s 4) t (ite (= s 5) 13 (ite (= s 6) 14 (ite (= s 7) 15 (ite (=
// s 8) t (ite (= s 9) 13 (ite (= s 10) 14 (ite (= s 11) 15 (ite (= s 13) s (ite
// (= s 14) s (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (=
// s 5) s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s
// 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15
// s))))))))))))) (ite (= t 2) s s))))))))))))))) (ite (= t 13) (ite (= s 1) t
// (ite (= s 2) 15 (ite (= s 3) 15 (ite (= s 4) t (ite (= s 5) t (ite (= s 6) 15
// (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) t (ite (= s 10) 15 (ite (= s 11)
// 15 (ite (= s 12) t (ite (= s 14) 15 (ite (= t 1) (ite (= s 2) 3 (ite (= s 3)
// s (ite (= s 4) 5 (ite (= s 5) s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9
// (ite (= s 9) s (ite (= s 10) 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s
// 13) s (ite (= s 14) 15 s))))))))))))) (ite (= t 2) s s))))))))))))))) (ite (=
// s 1) 15 (ite (= s 2) t (ite (= s 3) 15 (ite (= s 4) t (ite (= s 5) 15 (ite (=
// s 6) t (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) 15 (ite (= s 10) t (ite (=
// s 15) (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) s (ite (= s 4) 5 (ite (= s 5)
// s (ite (= s 6) 7 (ite (= s 7) s (ite (= s 8) 9 (ite (= s 9) s (ite (= s 10)
// 11 (ite (= s 11) s (ite (= s 12) 13 (ite (= s 13) s (ite (= s 14) 15
// s))))))))))))) (ite (= t 2) s s)) (ite (= s 11) 15 (ite (= s 12) t (ite (= s
// 13) 15 t)))))))))))))))))))))))))))))))
Node int_bvor_4_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_268 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_250 = nm->mkNode(EQUAL, s, t);
  Node ite_267 = nm->mkNode(ITE, equal_250, t, t);
  Node equal_265 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_77 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_73 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_71 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_69 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_67 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_76 = nm->mkNode(EQUAL, s, const_rational_15);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_65 = nm->mkNode(EQUAL, s, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_63 = nm->mkNode(EQUAL, s, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_61 = nm->mkNode(EQUAL, s, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_59 = nm->mkNode(EQUAL, s, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_36 = nm->mkNode(EQUAL, s, const_rational_11);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_34 = nm->mkNode(EQUAL, s, const_rational_12);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_55 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_264 = nm->mkNode(ITE, equal_55, s, s);
  Node ite_263 = nm->mkNode(ITE, equal_34, s, ite_264);
  Node ite_262 = nm->mkNode(ITE, equal_36, s, ite_263);
  Node ite_261 = nm->mkNode(ITE, equal_57, s, ite_262);
  Node ite_260 = nm->mkNode(ITE, equal_59, s, ite_261);
  Node ite_259 = nm->mkNode(ITE, equal_61, s, ite_260);
  Node ite_258 = nm->mkNode(ITE, equal_63, s, ite_259);
  Node ite_257 = nm->mkNode(ITE, equal_65, s, ite_258);
  Node ite_256 = nm->mkNode(ITE, equal_76, s, ite_257);
  Node ite_255 = nm->mkNode(ITE, equal_67, s, ite_256);
  Node ite_254 = nm->mkNode(ITE, equal_69, s, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_71, s, ite_254);
  Node ite_252 = nm->mkNode(ITE, equal_73, s, ite_253);
  Node ite_251 = nm->mkNode(ITE, equal_77, s, ite_252);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_32 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_54 = nm->mkNode(ITE, equal_55, const_rational_15, s);
  Node ite_53 = nm->mkNode(ITE, equal_32, s, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_34, const_rational_13, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_36, s, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_57, const_rational_11, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_59, s, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_61, const_rational_9, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_63, s, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_65, const_rational_7, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_67, s, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_69, const_rational_5, ite_45);
  Node ite_43 = nm->mkNode(ITE, equal_71, s, ite_44);
  Node ite_42 = nm->mkNode(ITE, equal_73, const_rational_3, ite_43);
  Node equal_40 = nm->mkNode(EQUAL, t, const_rational_2);
  Node ite_249 = nm->mkNode(ITE, equal_55, s, const_rational_15);
  Node ite_248 = nm->mkNode(ITE, equal_34, const_rational_14, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_36, s, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_57, s, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_59, const_rational_11, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_61, const_rational_10, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_63, s, ite_244);
  Node ite_242 = nm->mkNode(ITE, equal_65, s, ite_243);
  Node ite_241 = nm->mkNode(ITE, equal_67, const_rational_7, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_69, const_rational_6, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_71, s, ite_240);
  Node ite_238 = nm->mkNode(ITE, equal_77, const_rational_3, ite_239);
  Node ite_237 = nm->mkNode(ITE, equal_32, ite_238, s);
  Node ite_236 = nm->mkNode(ITE, equal_34, ite_238, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_36, ite_238, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_57, ite_238, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_59, ite_238, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_61, ite_238, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_63, ite_238, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_65, ite_238, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_67, ite_238, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_69, ite_238, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_71, ite_239, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_77, ite_238, ite_227);
  Node equal_225 = nm->mkNode(EQUAL, t, const_rational_3);
  Node ite_39 = nm->mkNode(ITE, equal_40, s, s);
  Node ite_38 = nm->mkNode(ITE, equal_74, ite_42, ite_39);
  Node ite_173 =
      nm->mkNode(ITE, equal_32, const_rational_15, const_rational_15);
  Node ite_172 = nm->mkNode(ITE, equal_34, const_rational_15, ite_173);
  Node ite_224 = nm->mkNode(ITE, equal_36, s, ite_172);
  Node ite_223 = nm->mkNode(ITE, equal_57, const_rational_11, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_76, ite_38, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_59, const_rational_11, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_61, const_rational_11, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_63, s, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_65, const_rational_7, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_67, const_rational_7, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_69, const_rational_7, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_73, t, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_77, t, ite_215);
  Node equal_213 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_159 = nm->mkNode(ITE, equal_34, s, s);
  Node ite_212 = nm->mkNode(ITE, equal_36, const_rational_15, ite_159);
  Node ite_211 = nm->mkNode(ITE, equal_57, const_rational_14, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_59, const_rational_13, ite_211);
  Node ite_209 = nm->mkNode(ITE, equal_55, s, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_61, const_rational_12, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_63, s, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_65, s, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_76, ite_38, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_67, s, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_71, const_rational_7, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_73, const_rational_6, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_77, const_rational_5, ite_202);
  Node equal_200 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_199 = nm->mkNode(ITE, equal_32, s, const_rational_15);
  Node ite_198 = nm->mkNode(ITE, equal_76, ite_38, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_34, const_rational_13, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_36, const_rational_15, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_57, const_rational_15, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_59, const_rational_13, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_61, const_rational_13, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_63, s, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_65, const_rational_7, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_69, t, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_71, const_rational_7, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_73, const_rational_7, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_77, t, ite_188);
  Node equal_186 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_132 = nm->mkNode(ITE, equal_32, const_rational_15, s);
  Node ite_131 = nm->mkNode(ITE, equal_34, const_rational_14, ite_132);
  Node ite_185 = nm->mkNode(ITE, equal_36, const_rational_15, ite_131);
  Node ite_184 = nm->mkNode(ITE, equal_57, const_rational_14, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_59, const_rational_15, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_76, ite_38, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_61, const_rational_14, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_63, s, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_67, const_rational_7, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_69, t, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_71, const_rational_7, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_73, t, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_77, const_rational_7, ite_176);
  Node equal_174 = nm->mkNode(EQUAL, t, const_rational_7);
  Node ite_171 = nm->mkNode(ITE, equal_36, const_rational_15, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_57, const_rational_15, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_59, const_rational_15, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_61, const_rational_15, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_65, t, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_76, ite_38, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_67, t, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_69, t, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_71, t, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_73, t, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_77, t, ite_162);
  Node equal_160 = nm->mkNode(EQUAL, t, const_rational_8);
  Node ite_158 = nm->mkNode(ITE, equal_36, s, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_57, s, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_59, s, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_63, const_rational_15, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_65, const_rational_14, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_55, s, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_67, const_rational_13, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_69, const_rational_12, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_71, const_rational_11, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_73, const_rational_10, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_77, const_rational_9, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_76, ite_38, ite_148);
  Node equal_146 = nm->mkNode(EQUAL, t, const_rational_9);
  Node ite_90 = nm->mkNode(ITE, equal_55, const_rational_15, ite_38);
  Node ite_145 = nm->mkNode(ITE, equal_32, s, ite_90);
  Node ite_144 = nm->mkNode(ITE, equal_34, const_rational_13, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_36, s, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_57, const_rational_11, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_61, t, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_63, const_rational_15, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_65, const_rational_15, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_67, const_rational_13, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_69, const_rational_13, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_71, const_rational_11, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_73, const_rational_11, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_77, t, ite_135);
  Node equal_133 = nm->mkNode(EQUAL, t, const_rational_10);
  Node ite_130 = nm->mkNode(ITE, equal_36, s, ite_131);
  Node ite_129 = nm->mkNode(ITE, equal_59, const_rational_11, ite_130);
  Node ite_128 = nm->mkNode(ITE, equal_61, t, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_63, const_rational_15, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_76, ite_38, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_65, const_rational_14, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_67, const_rational_15, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_69, const_rational_14, ite_124);
  Node ite_122 = nm->mkNode(ITE, equal_71, const_rational_11, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_73, t, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_77, const_rational_11, ite_121);
  Node equal_119 = nm->mkNode(EQUAL, t, const_rational_11);
  Node ite_118 = nm->mkNode(ITE, equal_76, ite_38, const_rational_15);
  Node ite_117 = nm->mkNode(ITE, equal_32, const_rational_15, ite_118);
  Node ite_116 = nm->mkNode(ITE, equal_34, const_rational_15, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_57, t, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_59, t, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_61, t, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_63, const_rational_15, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_65, const_rational_15, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_67, const_rational_15, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_69, const_rational_15, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_71, t, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_73, t, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_77, t, ite_107);
  Node equal_105 = nm->mkNode(EQUAL, t, const_rational_12);
  Node ite_104 = nm->mkNode(ITE, equal_55, s, ite_38);
  Node ite_103 = nm->mkNode(ITE, equal_32, s, ite_104);
  Node ite_102 = nm->mkNode(ITE, equal_36, const_rational_15, ite_103);
  Node ite_101 = nm->mkNode(ITE, equal_57, const_rational_14, ite_102);
  Node ite_100 = nm->mkNode(ITE, equal_59, const_rational_13, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_61, t, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_63, const_rational_15, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_65, const_rational_14, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_67, const_rational_13, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_69, t, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_71, const_rational_15, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_73, const_rational_14, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_77, const_rational_13, ite_93);
  Node equal_91 = nm->mkNode(EQUAL, t, const_rational_13);
  Node ite_89 = nm->mkNode(ITE, equal_34, t, ite_90);
  Node ite_88 = nm->mkNode(ITE, equal_36, const_rational_15, ite_89);
  Node ite_87 = nm->mkNode(ITE, equal_57, const_rational_15, ite_88);
  Node ite_86 = nm->mkNode(ITE, equal_59, t, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_61, t, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_63, const_rational_15, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_65, const_rational_15, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_67, t, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_69, t, ite_82);
  Node ite_80 = nm->mkNode(ITE, equal_71, const_rational_15, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_73, const_rational_15, ite_80);
  Node ite_78 = nm->mkNode(ITE, equal_77, t, ite_79);
  Node ite_30 = nm->mkNode(ITE, equal_32, const_rational_15, t);
  Node ite_29 = nm->mkNode(ITE, equal_34, t, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_36, const_rational_15, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_76, ite_38, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_57, t, ite_27);
  Node ite_25 = nm->mkNode(ITE, equal_59, const_rational_15, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_61, t, ite_25);
  Node ite_23 = nm->mkNode(ITE, equal_63, const_rational_15, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_65, t, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_67, const_rational_15, ite_22);
  Node ite_20 = nm->mkNode(ITE, equal_69, t, ite_21);
  Node ite_19 = nm->mkNode(ITE, equal_71, const_rational_15, ite_20);
  Node ite_18 = nm->mkNode(ITE, equal_73, t, ite_19);
  Node ite_17 = nm->mkNode(ITE, equal_77, const_rational_15, ite_18);
  Node ite_16 = nm->mkNode(ITE, equal_91, ite_78, ite_17);
  Node ite_15 = nm->mkNode(ITE, equal_105, ite_92, ite_16);
  Node ite_14 = nm->mkNode(ITE, equal_119, ite_106, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_133, ite_120, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_146, ite_134, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_160, ite_147, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_174, ite_161, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_186, ite_175, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_200, ite_187, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_213, ite_201, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_225, ite_214, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_40, ite_226, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_74, ite_42, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_250, t, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_265, ite_251, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_268, ite_267, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_1_min ((s Int) (t Int)) Int (ite (= s t) 0 1))
Node int_bvxor_1_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_4 = nm->mkNode(EQUAL, s, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_1 = nm->mkNode(ITE, equal_4, const_rational_0, const_rational_1);
  return ite_1;
}

// (define-fun int_bvxor_1_trivial ((s Int) (t Int)) Int (ite (= s t) 0 1))
Node int_bvxor_1_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_4 = nm->mkNode(EQUAL, s, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_1 = nm->mkNode(ITE, equal_4, const_rational_0, const_rational_1);
  return ite_1;
}

// (define-fun int_bvxor_2_min ((s Int) (t Int)) Int (ite (= s t) (ite (= 0 s)
// (* s s) 0) (ite (= 3 (* s t)) 2 (ite (>= 3 (* s t)) (+ s t) 1))))
Node int_bvxor_2_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_15 = nm->mkNode(EQUAL, s, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_14 = nm->mkNode(EQUAL, const_rational_0, s);
  Node mult_13 = nm->mkNode(MULT, s, s);
  Node ite_11 = nm->mkNode(ITE, equal_14, mult_13, const_rational_0);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node mult_7 = nm->mkNode(MULT, s, t);
  Node equal_10 = nm->mkNode(EQUAL, const_rational_3, mult_7);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node geq_6 = nm->mkNode(GEQ, const_rational_3, mult_7);
  Node plus_5 = nm->mkNode(PLUS, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_3 = nm->mkNode(ITE, geq_6, plus_5, const_rational_1);
  Node ite_2 = nm->mkNode(ITE, equal_10, const_rational_2, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_15, ite_11, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_2_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) 0 t) (ite (= s 3) (ite (= t 0) (ite (= s 1) s (ite (= s 3) s s)) (ite (= s
// t) 0 (ite (= t 1) 2 1))) (ite (= t 0) (ite (= s 1) s (ite (= s 3) s s)) (ite
// (= s t) 0 (ite (= t 1) 3 (ite (= t 2) 3 (ite (= s 2) 1 2))))))))
Node int_bvxor_2_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_15 = nm->mkNode(EQUAL, s, t);
  Node ite_24 = nm->mkNode(ITE, equal_15, const_rational_0, t);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_20 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_19 = nm->mkNode(EQUAL, s, const_rational_1);
  Node ite_17 = nm->mkNode(ITE, equal_18, s, s);
  Node ite_16 = nm->mkNode(ITE, equal_19, s, ite_17);
  Node equal_13 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node ite_23 = nm->mkNode(ITE, equal_13, const_rational_2, const_rational_1);
  Node ite_22 = nm->mkNode(ITE, equal_15, const_rational_0, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_20, ite_16, ite_22);
  Node equal_12 = nm->mkNode(EQUAL, t, const_rational_2);
  Node equal_10 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_7 = nm->mkNode(ITE, equal_10, const_rational_1, const_rational_2);
  Node ite_6 = nm->mkNode(ITE, equal_12, const_rational_3, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_13, const_rational_3, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_15, const_rational_0, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_20, ite_16, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_18, ite_21, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_25, ite_24, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_3_min ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
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
Node int_bvxor_3_min(Node s, Node t)
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

// (define-fun int_bvxor_3_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) 0 t) (ite (= t 0) (ite (= s 1) s (ite (= s 2) s (ite (= s 7) s (ite (= s
// 3) s (ite (= s 4) s (ite (= s 5) s s)))))) (ite (= s t) 0 (ite (= t 1) (ite
// (= s 2) 3 (ite (= s 3) 2 (ite (= s 4) 5 (ite (= s 5) 4 (ite (= s 7) 6 7)))))
// (ite (= t 2) (ite (= s 7) 5 (ite (= s 1) 3 (ite (= s 3) 1 (ite (= s 4) 6 (ite
// (= s 5) 7 4))))) (ite (= t 3) (ite (= s 1) 2 (ite (= s 2) 1 (ite (= s 4) 7
// (ite (= s 5) 6 (ite (= s 6) 5 4))))) (ite (= t 4) (ite (= s 1) (ite (= s 1) 5
// (ite (= s 6) 2 (ite (= s 2) 6 (ite (= s 3) 7 1)))) (ite (= s 2) (ite (= s 1)
// 5 (ite (= s 6) 2 (ite (= s 2) 6 (ite (= s 3) 7 1)))) (ite (= s 7) (ite (= t
// 3) (ite (= s 1) 2 (ite (= s 2) 1 (ite (= s 4) 7 (ite (= s 5) 6 (ite (= s 6) 5
// 4))))) (ite (= t 4) 3 (ite (= t 5) 2 1))) (ite (= s 1) 5 (ite (= s 6) 2 (ite
// (= s 2) 6 (ite (= s 3) 7 1))))))) (ite (= t 5) (ite (= s 1) (ite (= s 1) 4
// (ite (= s 2) 7 (ite (= s 3) 6 (ite (= s 4) 1 3)))) (ite (= s 2) (ite (= s 1)
// 4 (ite (= s 2) 7 (ite (= s 3) 6 (ite (= s 4) 1 3)))) (ite (= s 3) (ite (= s
// 1) 4 (ite (= s 2) 7 (ite (= s 3) 6 (ite (= s 4) 1 3)))) (ite (= s 4) (ite (=
// s 1) 4 (ite (= s 2) 7 (ite (= s 3) 6 (ite (= s 4) 1 3)))) (ite (= s 6) (ite
// (= s 1) 4 (ite (= s 2) 7 (ite (= s 3) 6 (ite (= s 4) 1 3)))) (ite (= t 3)
// (ite (= s 1) 2 (ite (= s 2) 1 (ite (= s 4) 7 (ite (= s 5) 6 (ite (= s 6) 5
// 4))))) (ite (= t 4) 3 (ite (= t 5) 2 1)))))))) (ite (= t 6) (ite (= s 1) 7
// (ite (= s 2) 4 (ite (= s 3) 5 (ite (= s 4) 2 (ite (= s 5) 3 (ite (= t 3) (ite
// (= s 1) 2 (ite (= s 2) 1 (ite (= s 4) 7 (ite (= s 5) 6 (ite (= s 6) 5 4)))))
// (ite (= t 4) 3 (ite (= t 5) 2 1)))))))) (ite (= s 1) 6 (ite (= s 2) 5 (ite (=
// s 3) 4 (ite (= s 4) 3 (ite (= s 6) 1 2)))))))))))))))
Node int_bvxor_3_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_84 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_75 = nm->mkNode(EQUAL, s, t);
  Node ite_83 = nm->mkNode(ITE, equal_75, const_rational_0, t);
  Node equal_82 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_24 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_61 = nm->mkNode(EQUAL, s, const_rational_7);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_41 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_81 = nm->mkNode(ITE, equal_41, s, s);
  Node ite_80 = nm->mkNode(ITE, equal_20, s, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_22, s, ite_80);
  Node ite_78 = nm->mkNode(ITE, equal_61, s, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_24, s, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_25, s, ite_77);
  Node equal_73 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node ite_72 = nm->mkNode(ITE, equal_61, const_rational_6, const_rational_7);
  Node ite_71 = nm->mkNode(ITE, equal_41, const_rational_4, ite_72);
  Node ite_70 = nm->mkNode(ITE, equal_20, const_rational_5, ite_71);
  Node ite_69 = nm->mkNode(ITE, equal_22, const_rational_2, ite_70);
  Node ite_68 = nm->mkNode(ITE, equal_24, const_rational_3, ite_69);
  Node equal_67 = nm->mkNode(EQUAL, t, const_rational_2);
  Node ite_66 = nm->mkNode(ITE, equal_41, const_rational_7, const_rational_4);
  Node ite_65 = nm->mkNode(ITE, equal_20, const_rational_6, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_22, const_rational_1, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_25, const_rational_3, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_61, const_rational_5, ite_63);
  Node equal_43 = nm->mkNode(EQUAL, t, const_rational_3);
  Node equal_17 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_40 = nm->mkNode(ITE, equal_17, const_rational_5, const_rational_4);
  Node ite_39 = nm->mkNode(ITE, equal_41, const_rational_6, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_20, const_rational_7, ite_39);
  Node ite_37 = nm->mkNode(ITE, equal_24, const_rational_1, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_25, const_rational_2, ite_37);
  Node equal_35 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_60 = nm->mkNode(ITE, equal_22, const_rational_7, const_rational_1);
  Node ite_59 = nm->mkNode(ITE, equal_24, const_rational_6, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_17, const_rational_2, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_25, const_rational_5, ite_58);
  Node equal_34 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_33 = nm->mkNode(ITE, equal_34, const_rational_2, const_rational_1);
  Node ite_32 = nm->mkNode(ITE, equal_35, const_rational_3, ite_33);
  Node ite_31 = nm->mkNode(ITE, equal_43, ite_36, ite_32);
  Node ite_56 = nm->mkNode(ITE, equal_61, ite_31, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_24, ite_57, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_25, ite_57, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_20, const_rational_1, const_rational_3);
  Node ite_52 = nm->mkNode(ITE, equal_22, const_rational_6, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_24, const_rational_7, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_25, const_rational_4, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_17, ite_50, ite_31);
  Node ite_48 = nm->mkNode(ITE, equal_20, ite_50, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_22, ite_50, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_24, ite_50, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_25, ite_50, ite_46);
  Node equal_44 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_30 = nm->mkNode(ITE, equal_41, const_rational_3, ite_31);
  Node ite_29 = nm->mkNode(ITE, equal_20, const_rational_2, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_22, const_rational_5, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_24, const_rational_4, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_25, const_rational_7, ite_27);
  Node ite_14 = nm->mkNode(ITE, equal_17, const_rational_1, const_rational_2);
  Node ite_13 = nm->mkNode(ITE, equal_20, const_rational_3, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_22, const_rational_4, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_24, const_rational_5, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_25, const_rational_6, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_44, ite_26, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_34, ite_45, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_35, ite_54, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_43, ite_36, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_67, ite_62, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_73, ite_68, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_75, const_rational_0, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_82, ite_76, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_84, ite_83, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_4_min ((s Int) (t Int)) Int (ite (= s 0) t (ite (= t 0)
// s (ite (= s t) 0 (ite (= t 1) (ite (= s 2) 3 (ite (= s 3) 2 (ite (= s 4) 5
// (ite (= s 5) 4 (ite (= s 6) 7 (ite (= s 7) 6 (ite (= s 15) 14 (ite (= s 8) 9
// (ite (= s 14) 15 (ite (= s 13) 12 (ite (= s 9) 8 (ite (= s 10) 11 (ite (= s
// 11) 10 13))))))))))))) (ite (= t 2) (ite (= s 1) 3 (ite (= s 3) 1 (ite (= s
// 4) 6 (ite (= s 5) 7 (ite (= s 6) 4 (ite (= s 7) 5 (ite (= s 8) 10 (ite (= s
// 9) 11 (ite (= s 10) 8 (ite (= s 11) 9 (ite (= s 12) 14 (ite (= s 13) 15 (ite
// (= s 15) 13 12))))))))))))) (ite (= t 3) (ite (= s 1) 2 (ite (= s 2) 1 (ite
// (= s 4) 7 (ite (= s 5) 6 (ite (= s 6) 5 (ite (= s 7) 4 (ite (= s 8) 11 (ite
// (= s 9) 10 (ite (= s 10) 9 (ite (= s 11) 8 (ite (= s 12) 15 (ite (= s 13) 14
// (ite (= s 15) 12 13))))))))))))) (ite (= t 4) (ite (= s 1) 5 (ite (= s 2) 6
// (ite (= s 3) 7 (ite (= s 5) 1 (ite (= s 6) 2 (ite (= s 7) 3 (ite (= s 8) 12
// (ite (= s 9) 13 (ite (= s 10) 14 (ite (= s 11) 15 (ite (= s 12) 8 (ite (= s
// 13) 9 (ite (= s 14) 10 11))))))))))))) (ite (= t 5) (ite (= s 1) 4 (ite (= s
// 2) 7 (ite (= s 3) 6 (ite (= s 4) 1 (ite (= s 6) 3 (ite (= s 7) 2 (ite (= s 8)
// 13 (ite (= s 9) 12 (ite (= s 10) 15 (ite (= s 11) 14 (ite (= s 12) 9 (ite (=
// s 13) 8 (ite (= s 14) 11 10))))))))))))) (ite (= t 6) (ite (= s 1) 7 (ite (=
// s 2) 4 (ite (= s 3) 5 (ite (= s 4) 2 (ite (= s 15) 9 (ite (= s 5) 3 (ite (= s
// 7) 1 (ite (= s 8) 14 (ite (= s 9) 15 (ite (= s 10) 12 (ite (= s 11) 13 (ite
// (= s 12) 10 (ite (= s 13) 11 8))))))))))))) (ite (= t 7) (ite (= s 15) 8 (ite
// (= s 1) 6 (ite (= s 2) 5 (ite (= s 3) 4 (ite (= s 14) 9 (ite (= s 4) 3 (ite
// (= s 5) 2 (ite (= s 6) 1 (ite (= s 8) 15 (ite (= s 9) 14 (ite (= s 10) 13
// (ite (= s 11) 12 (ite (= s 12) 11 10))))))))))))) (ite (= t 8) (ite (= s 1) 9
// (ite (= s 2) 10 (ite (= s 3) 11 (ite (= s 4) 12 (ite (= s 5) 13 (ite (= s 6)
// 14 (ite (= s 7) 15 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 15) 7 (ite (= s
// 11) 3 (ite (= s 12) 4 (ite (= s 14) 6 5))))))))))))) (ite (= t 9) (ite (= s
// 1) 8 (ite (= s 2) 11 (ite (= s 3) 10 (ite (= s 4) 13 (ite (= s 5) 12 (ite (=
// s 6) 15 (ite (= s 7) 14 (ite (= s 8) 1 (ite (= s 10) 3 (ite (= s 11) 2 (ite
// (= s 12) 5 (ite (= s 13) 4 (ite (= s 15) 6 7))))))))))))) (ite (= t 10) (ite
// (= s 1) 11 (ite (= s 2) 8 (ite (= s 3) 9 (ite (= s 4) 14 (ite (= s 5) 15 (ite
// (= s 6) 12 (ite (= s 7) 13 (ite (= s 8) 2 (ite (= s 9) 3 (ite (= s 15) 5 (ite
// (= s 11) 1 (ite (= s 14) 4 (ite (= s 12) 6 7))))))))))))) (ite (= t 11) (ite
// (= s 1) 10 (ite (= s 2) 9 (ite (= s 3) 8 (ite (= s 4) 15 (ite (= s 5) 14 (ite
// (= s 6) 13 (ite (= s 7) 12 (ite (= s 8) 3 (ite (= s 9) 2 (ite (= s 10) 1 (ite
// (= s 12) 7 (ite (= s 13) 6 (ite (= s 14) 5 4))))))))))))) (ite (= t 12) (ite
// (= s 1) 13 (ite (= s 2) 14 (ite (= s 3) 15 (ite (= s 4) 8 (ite (= s 5) 9 (ite
// (= s 6) 10 (ite (= s 7) 11 (ite (= s 8) 4 (ite (= s 9) 5 (ite (= s 10) 6 (ite
// (= s 11) 7 (ite (= s 13) 1 (ite (= s 14) 2 3))))))))))))) (ite (= t 13) (ite
// (= s 1) 12 (ite (= s 2) 15 (ite (= s 3) 14 (ite (= s 4) 9 (ite (= s 5) 8 (ite
// (= s 6) 11 (ite (= s 7) 10 (ite (= s 8) 5 (ite (= s 15) 2 (ite (= s 14) 3
// (ite (= s 9) 4 (ite (= s 10) 7 (ite (= s 11) 6 1))))))))))))) (ite (= t 14)
// (ite (= s 1) 15 (ite (= s 2) 12 (ite (= s 15) 1 (ite (= s 3) 13 (ite (= s 4)
// 10 (ite (= s 5) 11 (ite (= s 6) 8 (ite (= s 7) 9 (ite (= s 8) 6 (ite (= s 9)
// 7 (ite (= s 10) 4 (ite (= s 11) 5 (ite (= s 12) 2 3))))))))))))) (ite (= s 1)
// 14 (ite (= s 2) 13 (ite (= s 3) 12 (ite (= s 4) 11 (ite (= s 5) 10 (ite (= s
// 6) 9 (ite (= s 7) 8 (ite (= s 8) 7 (ite (= s 9) 6 (ite (= s 14) 1 (ite (= s
// 10) 5 (ite (= s 13) 2 (ite (= s 11) 4 3)))))))))))))))))))))))))))))))
Node int_bvxor_4_min(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_260 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_259 = nm->mkNode(EQUAL, t, const_rational_0);
  Node equal_258 = nm->mkNode(EQUAL, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_256 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_56 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_55 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_53 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_51 = nm->mkNode(EQUAL, s, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_50 = nm->mkNode(EQUAL, s, const_rational_7);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_72 = nm->mkNode(EQUAL, s, const_rational_15);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_48 = nm->mkNode(EQUAL, s, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_14);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_36 = nm->mkNode(EQUAL, s, const_rational_13);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_45 = nm->mkNode(EQUAL, s, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_39 = nm->mkNode(EQUAL, s, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_33 = nm->mkNode(EQUAL, s, const_rational_11);
  Node ite_255 =
      nm->mkNode(ITE, equal_33, const_rational_10, const_rational_13);
  Node ite_254 = nm->mkNode(ITE, equal_39, const_rational_11, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_45, const_rational_8, ite_254);
  Node ite_252 = nm->mkNode(ITE, equal_36, const_rational_12, ite_253);
  Node ite_251 = nm->mkNode(ITE, equal_42, const_rational_15, ite_252);
  Node ite_250 = nm->mkNode(ITE, equal_48, const_rational_9, ite_251);
  Node ite_249 = nm->mkNode(ITE, equal_72, const_rational_14, ite_250);
  Node ite_248 = nm->mkNode(ITE, equal_50, const_rational_6, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_51, const_rational_7, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_52, const_rational_4, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_53, const_rational_5, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_55, const_rational_2, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_56, const_rational_3, ite_244);
  Node equal_242 = nm->mkNode(EQUAL, t, const_rational_2);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_1);
  Node equal_71 = nm->mkNode(EQUAL, s, const_rational_12);
  Node ite_241 =
      nm->mkNode(ITE, equal_72, const_rational_13, const_rational_12);
  Node ite_240 = nm->mkNode(ITE, equal_36, const_rational_15, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_71, const_rational_14, ite_240);
  Node ite_238 = nm->mkNode(ITE, equal_33, const_rational_9, ite_239);
  Node ite_237 = nm->mkNode(ITE, equal_39, const_rational_8, ite_238);
  Node ite_236 = nm->mkNode(ITE, equal_45, const_rational_11, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_48, const_rational_10, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_50, const_rational_5, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_51, const_rational_4, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_52, const_rational_7, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_53, const_rational_6, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_55, const_rational_1, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_57, const_rational_3, ite_230);
  Node equal_228 = nm->mkNode(EQUAL, t, const_rational_3);
  Node ite_227 =
      nm->mkNode(ITE, equal_72, const_rational_12, const_rational_13);
  Node ite_226 = nm->mkNode(ITE, equal_36, const_rational_14, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_71, const_rational_15, ite_226);
  Node ite_224 = nm->mkNode(ITE, equal_33, const_rational_8, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_39, const_rational_9, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_45, const_rational_10, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_48, const_rational_11, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_50, const_rational_4, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_51, const_rational_5, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_52, const_rational_6, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_53, const_rational_7, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_56, const_rational_1, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_57, const_rational_2, ite_216);
  Node equal_214 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_213 =
      nm->mkNode(ITE, equal_42, const_rational_10, const_rational_11);
  Node ite_212 = nm->mkNode(ITE, equal_36, const_rational_9, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_71, const_rational_8, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_33, const_rational_15, ite_211);
  Node ite_209 = nm->mkNode(ITE, equal_39, const_rational_14, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_45, const_rational_13, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_48, const_rational_12, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_50, const_rational_3, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_51, const_rational_2, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_52, const_rational_1, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_55, const_rational_7, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_56, const_rational_6, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_57, const_rational_5, ite_202);
  Node equal_200 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_199 =
      nm->mkNode(ITE, equal_42, const_rational_11, const_rational_10);
  Node ite_198 = nm->mkNode(ITE, equal_36, const_rational_8, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_71, const_rational_9, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_33, const_rational_14, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_39, const_rational_15, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_45, const_rational_12, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_48, const_rational_13, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_50, const_rational_2, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_51, const_rational_3, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_53, const_rational_1, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_55, const_rational_6, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_56, const_rational_7, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_57, const_rational_4, ite_188);
  Node equal_186 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_185 = nm->mkNode(ITE, equal_36, const_rational_11, const_rational_8);
  Node ite_184 = nm->mkNode(ITE, equal_71, const_rational_10, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_33, const_rational_13, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_39, const_rational_12, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_45, const_rational_15, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_48, const_rational_14, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_50, const_rational_1, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_52, const_rational_3, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_72, const_rational_9, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_53, const_rational_2, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_55, const_rational_5, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_56, const_rational_4, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_57, const_rational_7, ite_174);
  Node equal_172 = nm->mkNode(EQUAL, t, const_rational_7);
  Node ite_171 =
      nm->mkNode(ITE, equal_71, const_rational_11, const_rational_10);
  Node ite_170 = nm->mkNode(ITE, equal_33, const_rational_12, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_39, const_rational_13, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_45, const_rational_14, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_48, const_rational_15, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_51, const_rational_1, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_52, const_rational_2, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_53, const_rational_3, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_42, const_rational_9, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_55, const_rational_4, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_56, const_rational_5, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_57, const_rational_6, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_72, const_rational_8, ite_160);
  Node equal_158 = nm->mkNode(EQUAL, t, const_rational_8);
  Node ite_157 = nm->mkNode(ITE, equal_42, const_rational_6, const_rational_5);
  Node ite_156 = nm->mkNode(ITE, equal_71, const_rational_4, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_33, const_rational_3, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_72, const_rational_7, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_39, const_rational_2, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_45, const_rational_1, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_50, const_rational_15, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_51, const_rational_14, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_52, const_rational_13, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_53, const_rational_12, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_55, const_rational_11, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_56, const_rational_10, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_57, const_rational_9, ite_146);
  Node equal_144 = nm->mkNode(EQUAL, t, const_rational_9);
  Node ite_143 = nm->mkNode(ITE, equal_72, const_rational_6, const_rational_7);
  Node ite_142 = nm->mkNode(ITE, equal_36, const_rational_4, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_71, const_rational_5, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_33, const_rational_2, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_39, const_rational_3, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_48, const_rational_1, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_50, const_rational_14, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_51, const_rational_15, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_52, const_rational_12, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_53, const_rational_13, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_55, const_rational_10, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_56, const_rational_11, ite_133);
  Node ite_131 = nm->mkNode(ITE, equal_57, const_rational_8, ite_132);
  Node equal_130 = nm->mkNode(EQUAL, t, const_rational_10);
  Node ite_129 = nm->mkNode(ITE, equal_71, const_rational_6, const_rational_7);
  Node ite_128 = nm->mkNode(ITE, equal_42, const_rational_4, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_33, const_rational_1, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_72, const_rational_5, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_45, const_rational_3, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_48, const_rational_2, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_50, const_rational_13, ite_124);
  Node ite_122 = nm->mkNode(ITE, equal_51, const_rational_12, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_52, const_rational_15, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_53, const_rational_14, ite_121);
  Node ite_119 = nm->mkNode(ITE, equal_55, const_rational_9, ite_120);
  Node ite_118 = nm->mkNode(ITE, equal_56, const_rational_8, ite_119);
  Node ite_117 = nm->mkNode(ITE, equal_57, const_rational_11, ite_118);
  Node equal_116 = nm->mkNode(EQUAL, t, const_rational_11);
  Node ite_115 = nm->mkNode(ITE, equal_42, const_rational_5, const_rational_4);
  Node ite_114 = nm->mkNode(ITE, equal_36, const_rational_6, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_71, const_rational_7, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_39, const_rational_1, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_45, const_rational_2, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_48, const_rational_3, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_50, const_rational_12, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_51, const_rational_13, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_52, const_rational_14, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_53, const_rational_15, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_55, const_rational_8, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_56, const_rational_9, ite_105);
  Node ite_103 = nm->mkNode(ITE, equal_57, const_rational_10, ite_104);
  Node equal_102 = nm->mkNode(EQUAL, t, const_rational_12);
  Node ite_101 = nm->mkNode(ITE, equal_42, const_rational_2, const_rational_3);
  Node ite_100 = nm->mkNode(ITE, equal_36, const_rational_1, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_33, const_rational_7, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_39, const_rational_6, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_45, const_rational_5, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_48, const_rational_4, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_50, const_rational_11, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_51, const_rational_10, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_52, const_rational_9, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_53, const_rational_8, ite_93);
  Node ite_91 = nm->mkNode(ITE, equal_55, const_rational_15, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_56, const_rational_14, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_57, const_rational_13, ite_90);
  Node equal_88 = nm->mkNode(EQUAL, t, const_rational_13);
  Node ite_87 = nm->mkNode(ITE, equal_33, const_rational_6, const_rational_1);
  Node ite_86 = nm->mkNode(ITE, equal_39, const_rational_7, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_45, const_rational_4, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_42, const_rational_3, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_72, const_rational_2, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_48, const_rational_5, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_50, const_rational_10, ite_82);
  Node ite_80 = nm->mkNode(ITE, equal_51, const_rational_11, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_52, const_rational_8, ite_80);
  Node ite_78 = nm->mkNode(ITE, equal_53, const_rational_9, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_55, const_rational_14, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_56, const_rational_15, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_57, const_rational_12, ite_76);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_14);
  Node ite_70 = nm->mkNode(ITE, equal_71, const_rational_2, const_rational_3);
  Node ite_69 = nm->mkNode(ITE, equal_33, const_rational_5, ite_70);
  Node ite_68 = nm->mkNode(ITE, equal_39, const_rational_4, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_45, const_rational_7, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_48, const_rational_6, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_50, const_rational_9, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_51, const_rational_8, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_52, const_rational_11, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_53, const_rational_10, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_55, const_rational_13, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_72, const_rational_1, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_56, const_rational_12, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_57, const_rational_15, ite_59);
  Node ite_30 = nm->mkNode(ITE, equal_33, const_rational_4, const_rational_3);
  Node ite_29 = nm->mkNode(ITE, equal_36, const_rational_2, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_39, const_rational_5, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_42, const_rational_1, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_45, const_rational_6, ite_27);
  Node ite_25 = nm->mkNode(ITE, equal_48, const_rational_7, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_50, const_rational_8, ite_25);
  Node ite_23 = nm->mkNode(ITE, equal_51, const_rational_9, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_52, const_rational_10, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_53, const_rational_11, ite_22);
  Node ite_20 = nm->mkNode(ITE, equal_55, const_rational_12, ite_21);
  Node ite_19 = nm->mkNode(ITE, equal_56, const_rational_13, ite_20);
  Node ite_18 = nm->mkNode(ITE, equal_57, const_rational_14, ite_19);
  Node ite_17 = nm->mkNode(ITE, equal_74, ite_58, ite_18);
  Node ite_16 = nm->mkNode(ITE, equal_88, ite_75, ite_17);
  Node ite_15 = nm->mkNode(ITE, equal_102, ite_89, ite_16);
  Node ite_14 = nm->mkNode(ITE, equal_116, ite_103, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_130, ite_117, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_144, ite_131, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_158, ite_145, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_172, ite_159, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_186, ite_173, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_200, ite_187, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_214, ite_201, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_228, ite_215, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_242, ite_229, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_256, ite_243, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_258, const_rational_0, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_259, s, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_260, t, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_4_trivial ((s Int) (t Int)) Int (ite (= s 0) (ite (= s
// t) 0 t) (ite (= t 0) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s (ite (= s
// 4) s (ite (= s 5) s (ite (= s 6) s (ite (= s 7) s (ite (= s 8) s (ite (= s 9)
// s (ite (= s 10) s (ite (= s 11) s (ite (= s 12) s (ite (= s 13) s (ite (= s
// 14) s s)))))))))))))) (ite (= s t) 0 (ite (= t 1) (ite (= s 2) 3 (ite (= s 3)
// 2 (ite (= s 4) 5 (ite (= s 5) 4 (ite (= s 6) 7 (ite (= s 7) 6 (ite (= s 15)
// 14 (ite (= s 8) 9 (ite (= s 14) 15 (ite (= s 13) 12 (ite (= s 9) 8 (ite (= s
// 10) 11 (ite (= s 11) 10 13))))))))))))) (ite (= t 2) (ite (= s 1) 3 (ite (= s
// 3) 1 (ite (= s 4) 6 (ite (= s 5) 7 (ite (= s 6) 4 (ite (= s 7) 5 (ite (= s 8)
// 10 (ite (= s 9) 11 (ite (= s 10) 8 (ite (= s 11) 9 (ite (= s 12) 14 (ite (= s
// 13) 15 (ite (= s 15) 13 12))))))))))))) (ite (= t 3) (ite (= s 1) 2 (ite (= s
// 2) 1 (ite (= s 4) 7 (ite (= s 5) 6 (ite (= s 6) 5 (ite (= s 7) 4 (ite (= s 8)
// 11 (ite (= s 9) 10 (ite (= s 10) 9 (ite (= s 11) 8 (ite (= s 12) 15 (ite (= s
// 13) 14 (ite (= s 15) 12 13))))))))))))) (ite (= t 4) (ite (= s 1) 5 (ite (= s
// 2) 6 (ite (= s 3) 7 (ite (= s 5) 1 (ite (= s 6) 2 (ite (= s 7) 3 (ite (= s 8)
// 12 (ite (= s 9) 13 (ite (= s 10) 14 (ite (= s 11) 15 (ite (= s 12) 8 (ite (=
// s 13) 9 (ite (= s 14) 10 11))))))))))))) (ite (= t 5) (ite (= s 1) 4 (ite (=
// s 2) 7 (ite (= s 3) 6 (ite (= s 4) 1 (ite (= s 6) 3 (ite (= s 7) 2 (ite (= s
// 8) 13 (ite (= s 9) 12 (ite (= s 10) 15 (ite (= s 11) 14 (ite (= s 12) 9 (ite
// (= s 13) 8 (ite (= s 14) 11 10))))))))))))) (ite (= t 6) (ite (= s 1) 7 (ite
// (= s 2) 4 (ite (= s 3) 5 (ite (= s 4) 2 (ite (= s 15) 9 (ite (= s 5) 3 (ite
// (= s 7) 1 (ite (= s 8) 14 (ite (= s 9) 15 (ite (= s 10) 12 (ite (= s 11) 13
// (ite (= s 12) 10 (ite (= s 13) 11 8))))))))))))) (ite (= t 7) (ite (= s 15) 8
// (ite (= s 1) 6 (ite (= s 2) 5 (ite (= s 3) 4 (ite (= s 14) 9 (ite (= s 4) 3
// (ite (= s 5) 2 (ite (= s 6) 1 (ite (= s 8) 15 (ite (= s 9) 14 (ite (= s 10)
// 13 (ite (= s 11) 12 (ite (= s 12) 11 10))))))))))))) (ite (= t 8) (ite (= s
// 1) 9 (ite (= s 2) 10 (ite (= s 3) 11 (ite (= s 4) 12 (ite (= s 5) 13 (ite (=
// s 6) 14 (ite (= s 7) 15 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 15) 7 (ite
// (= s 11) 3 (ite (= s 12) 4 (ite (= s 14) 6 5))))))))))))) (ite (= t 9) (ite
// (= s 1) 8 (ite (= s 2) 11 (ite (= s 3) 10 (ite (= s 4) 13 (ite (= s 5) 12
// (ite (= s 6) 15 (ite (= s 7) 14 (ite (= s 8) 1 (ite (= s 10) 3 (ite (= s 11)
// 2 (ite (= s 12) 5 (ite (= s 13) 4 (ite (= s 15) 6 7))))))))))))) (ite (= t
// 10) (ite (= s 1) 11 (ite (= s 2) 8 (ite (= s 3) 9 (ite (= s 4) 14 (ite (= s
// 5) 15 (ite (= s 6) 12 (ite (= s 7) 13 (ite (= s 8) 2 (ite (= s 9) 3 (ite (= s
// 15) 5 (ite (= s 11) 1 (ite (= s 14) 4 (ite (= s 12) 6 7))))))))))))) (ite (=
// t 11) (ite (= s 1) 10 (ite (= s 2) 9 (ite (= s 3) 8 (ite (= s 4) 15 (ite (= s
// 5) 14 (ite (= s 6) 13 (ite (= s 7) 12 (ite (= s 8) 3 (ite (= s 9) 2 (ite (= s
// 10) 1 (ite (= s 12) 7 (ite (= s 13) 6 (ite (= s 14) 5 4))))))))))))) (ite (=
// t 12) (ite (= s 1) 13 (ite (= s 2) 14 (ite (= s 3) 15 (ite (= s 4) 8 (ite (=
// s 5) 9 (ite (= s 6) 10 (ite (= s 7) 11 (ite (= s 8) 4 (ite (= s 9) 5 (ite (=
// s 10) 6 (ite (= s 11) 7 (ite (= s 13) 1 (ite (= s 14) 2 3))))))))))))) (ite
// (= t 13) (ite (= s 1) 12 (ite (= s 2) 15 (ite (= s 3) 14 (ite (= s 4) 9 (ite
// (= s 5) 8 (ite (= s 6) 11 (ite (= s 7) 10 (ite (= s 8) 5 (ite (= s 15) 2 (ite
// (= s 14) 3 (ite (= s 9) 4 (ite (= s 10) 7 (ite (= s 11) 6 1))))))))))))) (ite
// (= t 14) (ite (= s 1) 15 (ite (= s 2) 12 (ite (= s 15) 1 (ite (= s 3) 13 (ite
// (= s 4) 10 (ite (= s 5) 11 (ite (= s 6) 8 (ite (= s 7) 9 (ite (= s 8) 6 (ite
// (= s 9) 7 (ite (= s 10) 4 (ite (= s 11) 5 (ite (= s 12) 2 3))))))))))))) (ite
// (= s 1) 14 (ite (= s 2) 13 (ite (= s 3) 12 (ite (= s 4) 11 (ite (= s 5) 10
// (ite (= s 6) 9 (ite (= s 7) 8 (ite (= s 8) 7 (ite (= s 9) 6 (ite (= s 14) 1
// (ite (= s 10) 5 (ite (= s 13) 2 (ite (= s 11) 4
// 3)))))))))))))))))))))))))))))))
Node int_bvxor_4_trivial(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_275 = nm->mkNode(EQUAL, s, const_rational_0);
  Node equal_258 = nm->mkNode(EQUAL, s, t);
  Node ite_274 = nm->mkNode(ITE, equal_258, const_rational_0, t);
  Node equal_273 = nm->mkNode(EQUAL, t, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_1);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_56 = nm->mkNode(EQUAL, s, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_55 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_53 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_51 = nm->mkNode(EQUAL, s, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_50 = nm->mkNode(EQUAL, s, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_48 = nm->mkNode(EQUAL, s, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_45 = nm->mkNode(EQUAL, s, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_39 = nm->mkNode(EQUAL, s, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_33 = nm->mkNode(EQUAL, s, const_rational_11);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_71 = nm->mkNode(EQUAL, s, const_rational_12);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_36 = nm->mkNode(EQUAL, s, const_rational_13);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_272 = nm->mkNode(ITE, equal_42, s, s);
  Node ite_271 = nm->mkNode(ITE, equal_36, s, ite_272);
  Node ite_270 = nm->mkNode(ITE, equal_71, s, ite_271);
  Node ite_269 = nm->mkNode(ITE, equal_33, s, ite_270);
  Node ite_268 = nm->mkNode(ITE, equal_39, s, ite_269);
  Node ite_267 = nm->mkNode(ITE, equal_45, s, ite_268);
  Node ite_266 = nm->mkNode(ITE, equal_48, s, ite_267);
  Node ite_265 = nm->mkNode(ITE, equal_50, s, ite_266);
  Node ite_264 = nm->mkNode(ITE, equal_51, s, ite_265);
  Node ite_263 = nm->mkNode(ITE, equal_52, s, ite_264);
  Node ite_262 = nm->mkNode(ITE, equal_53, s, ite_263);
  Node ite_261 = nm->mkNode(ITE, equal_55, s, ite_262);
  Node ite_260 = nm->mkNode(ITE, equal_56, s, ite_261);
  Node ite_259 = nm->mkNode(ITE, equal_57, s, ite_260);
  Node equal_256 = nm->mkNode(EQUAL, t, const_rational_1);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_72 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_255 =
      nm->mkNode(ITE, equal_33, const_rational_10, const_rational_13);
  Node ite_254 = nm->mkNode(ITE, equal_39, const_rational_11, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_45, const_rational_8, ite_254);
  Node ite_252 = nm->mkNode(ITE, equal_36, const_rational_12, ite_253);
  Node ite_251 = nm->mkNode(ITE, equal_42, const_rational_15, ite_252);
  Node ite_250 = nm->mkNode(ITE, equal_48, const_rational_9, ite_251);
  Node ite_249 = nm->mkNode(ITE, equal_72, const_rational_14, ite_250);
  Node ite_248 = nm->mkNode(ITE, equal_50, const_rational_6, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_51, const_rational_7, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_52, const_rational_4, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_53, const_rational_5, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_55, const_rational_2, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_56, const_rational_3, ite_244);
  Node equal_242 = nm->mkNode(EQUAL, t, const_rational_2);
  Node ite_241 =
      nm->mkNode(ITE, equal_72, const_rational_13, const_rational_12);
  Node ite_240 = nm->mkNode(ITE, equal_36, const_rational_15, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_71, const_rational_14, ite_240);
  Node ite_238 = nm->mkNode(ITE, equal_33, const_rational_9, ite_239);
  Node ite_237 = nm->mkNode(ITE, equal_39, const_rational_8, ite_238);
  Node ite_236 = nm->mkNode(ITE, equal_45, const_rational_11, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_48, const_rational_10, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_50, const_rational_5, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_51, const_rational_4, ite_234);
  Node ite_232 = nm->mkNode(ITE, equal_52, const_rational_7, ite_233);
  Node ite_231 = nm->mkNode(ITE, equal_53, const_rational_6, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_55, const_rational_1, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_57, const_rational_3, ite_230);
  Node equal_228 = nm->mkNode(EQUAL, t, const_rational_3);
  Node ite_227 =
      nm->mkNode(ITE, equal_72, const_rational_12, const_rational_13);
  Node ite_226 = nm->mkNode(ITE, equal_36, const_rational_14, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_71, const_rational_15, ite_226);
  Node ite_224 = nm->mkNode(ITE, equal_33, const_rational_8, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_39, const_rational_9, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_45, const_rational_10, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_48, const_rational_11, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_50, const_rational_4, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_51, const_rational_5, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_52, const_rational_6, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_53, const_rational_7, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_56, const_rational_1, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_57, const_rational_2, ite_216);
  Node equal_214 = nm->mkNode(EQUAL, t, const_rational_4);
  Node ite_213 =
      nm->mkNode(ITE, equal_42, const_rational_10, const_rational_11);
  Node ite_212 = nm->mkNode(ITE, equal_36, const_rational_9, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_71, const_rational_8, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_33, const_rational_15, ite_211);
  Node ite_209 = nm->mkNode(ITE, equal_39, const_rational_14, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_45, const_rational_13, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_48, const_rational_12, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_50, const_rational_3, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_51, const_rational_2, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_52, const_rational_1, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_55, const_rational_7, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_56, const_rational_6, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_57, const_rational_5, ite_202);
  Node equal_200 = nm->mkNode(EQUAL, t, const_rational_5);
  Node ite_199 =
      nm->mkNode(ITE, equal_42, const_rational_11, const_rational_10);
  Node ite_198 = nm->mkNode(ITE, equal_36, const_rational_8, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_71, const_rational_9, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_33, const_rational_14, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_39, const_rational_15, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_45, const_rational_12, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_48, const_rational_13, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_50, const_rational_2, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_51, const_rational_3, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_53, const_rational_1, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_55, const_rational_6, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_56, const_rational_7, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_57, const_rational_4, ite_188);
  Node equal_186 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_185 = nm->mkNode(ITE, equal_36, const_rational_11, const_rational_8);
  Node ite_184 = nm->mkNode(ITE, equal_71, const_rational_10, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_33, const_rational_13, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_39, const_rational_12, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_45, const_rational_15, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_48, const_rational_14, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_50, const_rational_1, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_52, const_rational_3, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_72, const_rational_9, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_53, const_rational_2, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_55, const_rational_5, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_56, const_rational_4, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_57, const_rational_7, ite_174);
  Node equal_172 = nm->mkNode(EQUAL, t, const_rational_7);
  Node ite_171 =
      nm->mkNode(ITE, equal_71, const_rational_11, const_rational_10);
  Node ite_170 = nm->mkNode(ITE, equal_33, const_rational_12, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_39, const_rational_13, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_45, const_rational_14, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_48, const_rational_15, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_51, const_rational_1, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_52, const_rational_2, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_53, const_rational_3, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_42, const_rational_9, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_55, const_rational_4, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_56, const_rational_5, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_57, const_rational_6, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_72, const_rational_8, ite_160);
  Node equal_158 = nm->mkNode(EQUAL, t, const_rational_8);
  Node ite_157 = nm->mkNode(ITE, equal_42, const_rational_6, const_rational_5);
  Node ite_156 = nm->mkNode(ITE, equal_71, const_rational_4, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_33, const_rational_3, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_72, const_rational_7, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_39, const_rational_2, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_45, const_rational_1, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_50, const_rational_15, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_51, const_rational_14, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_52, const_rational_13, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_53, const_rational_12, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_55, const_rational_11, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_56, const_rational_10, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_57, const_rational_9, ite_146);
  Node equal_144 = nm->mkNode(EQUAL, t, const_rational_9);
  Node ite_143 = nm->mkNode(ITE, equal_72, const_rational_6, const_rational_7);
  Node ite_142 = nm->mkNode(ITE, equal_36, const_rational_4, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_71, const_rational_5, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_33, const_rational_2, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_39, const_rational_3, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_48, const_rational_1, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_50, const_rational_14, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_51, const_rational_15, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_52, const_rational_12, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_53, const_rational_13, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_55, const_rational_10, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_56, const_rational_11, ite_133);
  Node ite_131 = nm->mkNode(ITE, equal_57, const_rational_8, ite_132);
  Node equal_130 = nm->mkNode(EQUAL, t, const_rational_10);
  Node ite_129 = nm->mkNode(ITE, equal_71, const_rational_6, const_rational_7);
  Node ite_128 = nm->mkNode(ITE, equal_42, const_rational_4, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_33, const_rational_1, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_72, const_rational_5, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_45, const_rational_3, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_48, const_rational_2, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_50, const_rational_13, ite_124);
  Node ite_122 = nm->mkNode(ITE, equal_51, const_rational_12, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_52, const_rational_15, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_53, const_rational_14, ite_121);
  Node ite_119 = nm->mkNode(ITE, equal_55, const_rational_9, ite_120);
  Node ite_118 = nm->mkNode(ITE, equal_56, const_rational_8, ite_119);
  Node ite_117 = nm->mkNode(ITE, equal_57, const_rational_11, ite_118);
  Node equal_116 = nm->mkNode(EQUAL, t, const_rational_11);
  Node ite_115 = nm->mkNode(ITE, equal_42, const_rational_5, const_rational_4);
  Node ite_114 = nm->mkNode(ITE, equal_36, const_rational_6, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_71, const_rational_7, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_39, const_rational_1, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_45, const_rational_2, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_48, const_rational_3, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_50, const_rational_12, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_51, const_rational_13, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_52, const_rational_14, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_53, const_rational_15, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_55, const_rational_8, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_56, const_rational_9, ite_105);
  Node ite_103 = nm->mkNode(ITE, equal_57, const_rational_10, ite_104);
  Node equal_102 = nm->mkNode(EQUAL, t, const_rational_12);
  Node ite_101 = nm->mkNode(ITE, equal_42, const_rational_2, const_rational_3);
  Node ite_100 = nm->mkNode(ITE, equal_36, const_rational_1, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_33, const_rational_7, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_39, const_rational_6, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_45, const_rational_5, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_48, const_rational_4, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_50, const_rational_11, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_51, const_rational_10, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_52, const_rational_9, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_53, const_rational_8, ite_93);
  Node ite_91 = nm->mkNode(ITE, equal_55, const_rational_15, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_56, const_rational_14, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_57, const_rational_13, ite_90);
  Node equal_88 = nm->mkNode(EQUAL, t, const_rational_13);
  Node ite_87 = nm->mkNode(ITE, equal_33, const_rational_6, const_rational_1);
  Node ite_86 = nm->mkNode(ITE, equal_39, const_rational_7, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_45, const_rational_4, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_42, const_rational_3, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_72, const_rational_2, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_48, const_rational_5, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_50, const_rational_10, ite_82);
  Node ite_80 = nm->mkNode(ITE, equal_51, const_rational_11, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_52, const_rational_8, ite_80);
  Node ite_78 = nm->mkNode(ITE, equal_53, const_rational_9, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_55, const_rational_14, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_56, const_rational_15, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_57, const_rational_12, ite_76);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_14);
  Node ite_70 = nm->mkNode(ITE, equal_71, const_rational_2, const_rational_3);
  Node ite_69 = nm->mkNode(ITE, equal_33, const_rational_5, ite_70);
  Node ite_68 = nm->mkNode(ITE, equal_39, const_rational_4, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_45, const_rational_7, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_48, const_rational_6, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_50, const_rational_9, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_51, const_rational_8, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_52, const_rational_11, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_53, const_rational_10, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_55, const_rational_13, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_72, const_rational_1, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_56, const_rational_12, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_57, const_rational_15, ite_59);
  Node ite_30 = nm->mkNode(ITE, equal_33, const_rational_4, const_rational_3);
  Node ite_29 = nm->mkNode(ITE, equal_36, const_rational_2, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_39, const_rational_5, ite_29);
  Node ite_27 = nm->mkNode(ITE, equal_42, const_rational_1, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_45, const_rational_6, ite_27);
  Node ite_25 = nm->mkNode(ITE, equal_48, const_rational_7, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_50, const_rational_8, ite_25);
  Node ite_23 = nm->mkNode(ITE, equal_51, const_rational_9, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_52, const_rational_10, ite_23);
  Node ite_21 = nm->mkNode(ITE, equal_53, const_rational_11, ite_22);
  Node ite_20 = nm->mkNode(ITE, equal_55, const_rational_12, ite_21);
  Node ite_19 = nm->mkNode(ITE, equal_56, const_rational_13, ite_20);
  Node ite_18 = nm->mkNode(ITE, equal_57, const_rational_14, ite_19);
  Node ite_17 = nm->mkNode(ITE, equal_74, ite_58, ite_18);
  Node ite_16 = nm->mkNode(ITE, equal_88, ite_75, ite_17);
  Node ite_15 = nm->mkNode(ITE, equal_102, ite_89, ite_16);
  Node ite_14 = nm->mkNode(ITE, equal_116, ite_103, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_130, ite_117, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_144, ite_131, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_158, ite_145, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_172, ite_159, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_186, ite_173, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_200, ite_187, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_214, ite_201, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_228, ite_215, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_242, ite_229, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_256, ite_243, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_258, const_rational_0, ite_4);
  Node ite_2 = nm->mkNode(ITE, equal_273, ite_259, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_275, ite_274, ite_2);
  return ite_1;
}
