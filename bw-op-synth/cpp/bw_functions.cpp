#include "bw_functions.h"
#include <math.h>
#include "theory/bv/theory_bv_utils.h"
using namespace CVC4::kind;
using namespace CVC4;
// (define-fun int_bvand_1_lia ((s Int) (t Int)) Int (ite (= s t) s 0))
Node int_bvand_1_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_3 = nm->mkNode(EQUAL, s, t);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node ite_1 = nm->mkNode(ITE, equal_3, s, const_rational_0);
  return ite_1;
}

// (define-fun int_bvand_1_nia ((s Int) (t Int)) Int (* s t))
Node int_bvand_1_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_1 = nm->mkNode(MULT, s, t);
  return mult_1;
}

// (define-fun int_bvand_2_lia ((s Int) (t Int)) Int (ite (= (+ s t) 3) 0 (ite
// (>= s t) t s)))
Node int_bvand_2_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node plus_7 = nm->mkNode(PLUS, s, t);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_5 = nm->mkNode(EQUAL, plus_7, const_rational_3);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node geq_3 = nm->mkNode(GEQ, s, t);
  Node ite_2 = nm->mkNode(ITE, geq_3, t, s);
  Node ite_1 = nm->mkNode(ITE, equal_5, const_rational_0, ite_2);
  return ite_1;
}

// (define-fun int_bvand_2_nia ((s Int) (t Int)) Int (ite (= 2 (* s t)) 0 (ite
// (>= s t) t s)))
Node int_bvand_2_nia(Node s, Node t)
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

// (define-fun int_bvand_3_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// s (ite (>= s t) s (ite (= t 2) 0 (ite (= t 3) s (ite (= t 4) (ite (= s 1) 0
// (ite (= s 2) 0 0)) (ite (= t 5) (ite (= s 1) s (ite (= s 2) 0 (ite (= s 3) 1
// s))) (ite (= t 6) (ite (= s 1) 0 (ite (= s 5) 4 (ite (= s 2) s (ite (= s 3) 2
// s)))) s))))))) (ite (>= s (* 2 t)) (ite (>= s (* 3 t)) (ite (>= s (* 4 t))
// (ite (>= s (* 5 t)) (ite (>= s (* 6 t)) (ite (>= s (* 7 t)) t 0) t) 0) t)
// (ite (= s (* 2 t)) (ite (= t 1) 0 (ite (= t 2) 0 2)) (ite (= t 2) 0 t))) (ite
// (= t 2) t (ite (= t 3) (ite (= s 4) 0 1) (ite (= t 4) t (ite (= t 5) (ite (=
// s 6) 4 t) t)))))))
Node int_bvand_3_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_69 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_68 = nm->mkNode(EQUAL, s, const_rational_0);
  Node geq_67 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_20 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_18 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_13 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_60 = nm->mkNode(EQUAL, s, const_rational_1);
  Node equal_58 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_66 = nm->mkNode(ITE, equal_58, const_rational_0, const_rational_0);
  Node ite_65 = nm->mkNode(ITE, equal_60, const_rational_0, ite_66);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_11 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_64 = nm->mkNode(ITE, equal_57, const_rational_1, s);
  Node ite_63 = nm->mkNode(ITE, equal_58, const_rational_0, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_60, s, ite_63);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_61 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_59 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_56 = nm->mkNode(ITE, equal_57, const_rational_2, s);
  Node ite_55 = nm->mkNode(ITE, equal_58, s, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_59, const_rational_4, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_60, const_rational_0, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_61, ite_53, s);
  Node ite_51 = nm->mkNode(ITE, equal_11, ite_62, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_13, ite_65, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_18, s, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_20, const_rational_0, ite_49);
  Node ite_47 = nm->mkNode(ITE, geq_67, s, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_68, s, ite_47);
  Node mult_29 = nm->mkNode(MULT, const_rational_2, t);
  Node geq_45 = nm->mkNode(GEQ, s, mult_29);
  Node mult_44 = nm->mkNode(MULT, const_rational_3, t);
  Node geq_43 = nm->mkNode(GEQ, s, mult_44);
  Node mult_42 = nm->mkNode(MULT, const_rational_4, t);
  Node geq_41 = nm->mkNode(GEQ, s, mult_42);
  Node mult_40 = nm->mkNode(MULT, const_rational_5, t);
  Node geq_39 = nm->mkNode(GEQ, s, mult_40);
  Node mult_38 = nm->mkNode(MULT, const_rational_6, t);
  Node geq_37 = nm->mkNode(GEQ, s, mult_38);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node mult_35 = nm->mkNode(MULT, const_rational_7, t);
  Node geq_34 = nm->mkNode(GEQ, s, mult_35);
  Node ite_33 = nm->mkNode(ITE, geq_34, t, const_rational_0);
  Node ite_32 = nm->mkNode(ITE, geq_37, ite_33, t);
  Node ite_31 = nm->mkNode(ITE, geq_39, ite_32, const_rational_0);
  Node ite_30 = nm->mkNode(ITE, geq_41, ite_31, t);
  Node equal_28 = nm->mkNode(EQUAL, s, mult_29);
  Node equal_27 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_26 = nm->mkNode(ITE, equal_20, const_rational_0, const_rational_2);
  Node ite_25 = nm->mkNode(ITE, equal_27, const_rational_0, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_20, const_rational_0, t);
  Node ite_23 = nm->mkNode(ITE, equal_28, ite_25, ite_24);
  Node ite_22 = nm->mkNode(ITE, geq_43, ite_30, ite_23);
  Node equal_17 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_14 = nm->mkNode(ITE, equal_17, const_rational_0, const_rational_1);
  Node equal_9 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_7 = nm->mkNode(ITE, equal_9, const_rational_4, t);
  Node ite_6 = nm->mkNode(ITE, equal_11, ite_7, t);
  Node ite_5 = nm->mkNode(ITE, equal_13, t, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_18, ite_14, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_20, t, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_45, ite_22, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_69, ite_46, ite_2);
  return ite_1;
}

// (define-fun int_bvand_3_nia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (* s t) (ite (= t 2) 0 (ite (= t 3) s (ite (= t 4) 0 (ite (= t 5)
// s (ite (= t 6) 0 s)))))) (ite (>= s (* s t)) (ite (= s (* s t)) (ite (= s (+
// t t)) 0 (ite (= s 3) t (ite (= s 4) 0 (ite (= s 5) t (ite (= s 7) t 0))))) (*
// s t)) (ite (>= t s) (ite (>= s t) s (ite (= t 3) s (ite (= t 4) (ite (= s 2)
// 0 0) (ite (= t 5) (ite (= s 2) 0 (ite (= s 3) 1 s)) (ite (= t 6) (ite (= s 2)
// s (ite (= s 3) 2 (ite (= s 4) s 4))) s))))) (ite (>= s (* t t)) (ite (= s (*
// t t)) 0 (ite (= s 7) t (ite (= s 5) 0 t))) (ite (>= s (+ t t)) (ite (= s (+ t
// t)) 2 t) (ite (= s 7) t (ite (= t 2) t (ite (= t 3) (ite (= s 4) 0 1) (ite (=
// t 4) t 4))))))))))
Node int_bvand_3_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_68 = nm->mkNode(MULT, s, s);
  Node equal_67 = nm->mkNode(EQUAL, s, mult_68);
  Node mult_53 = nm->mkNode(MULT, s, t);
  Node geq_60 = nm->mkNode(GEQ, s, mult_53);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_18 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_16 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_11 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_48 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_44 = nm->mkNode(EQUAL, t, const_rational_6);
  Node ite_66 = nm->mkNode(ITE, equal_44, const_rational_0, s);
  Node ite_65 = nm->mkNode(ITE, equal_48, s, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_11, const_rational_0, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_16, s, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_18, const_rational_0, ite_63);
  Node ite_61 = nm->mkNode(ITE, geq_60, mult_53, ite_62);
  Node equal_59 = nm->mkNode(EQUAL, s, mult_53);
  Node plus_24 = nm->mkNode(PLUS, t, t);
  Node equal_23 = nm->mkNode(EQUAL, s, plus_24);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_15 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_29 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_58 = nm->mkNode(ITE, equal_20, t, const_rational_0);
  Node ite_57 = nm->mkNode(ITE, equal_29, t, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_15, const_rational_0, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_42, t, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_23, const_rational_0, ite_55);
  Node ite_52 = nm->mkNode(ITE, equal_59, ite_54, mult_53);
  Node geq_51 = nm->mkNode(GEQ, t, s);
  Node geq_50 = nm->mkNode(GEQ, s, t);
  Node equal_43 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_49 = nm->mkNode(ITE, equal_43, const_rational_0, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_47 = nm->mkNode(ITE, equal_42, const_rational_1, s);
  Node ite_46 = nm->mkNode(ITE, equal_43, const_rational_0, ite_47);
  Node ite_41 = nm->mkNode(ITE, equal_15, s, const_rational_4);
  Node ite_40 = nm->mkNode(ITE, equal_42, const_rational_2, ite_41);
  Node ite_39 = nm->mkNode(ITE, equal_43, s, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_44, ite_39, s);
  Node ite_37 = nm->mkNode(ITE, equal_48, ite_46, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_11, ite_49, ite_37);
  Node ite_35 = nm->mkNode(ITE, equal_16, s, ite_36);
  Node ite_34 = nm->mkNode(ITE, geq_50, s, ite_35);
  Node mult_32 = nm->mkNode(MULT, t, t);
  Node geq_33 = nm->mkNode(GEQ, s, mult_32);
  Node equal_31 = nm->mkNode(EQUAL, s, mult_32);
  Node ite_28 = nm->mkNode(ITE, equal_29, const_rational_0, t);
  Node ite_27 = nm->mkNode(ITE, equal_20, t, ite_28);
  Node ite_26 = nm->mkNode(ITE, equal_31, const_rational_0, ite_27);
  Node geq_25 = nm->mkNode(GEQ, s, plus_24);
  Node ite_22 = nm->mkNode(ITE, equal_23, const_rational_2, t);
  Node ite_12 = nm->mkNode(ITE, equal_15, const_rational_0, const_rational_1);
  Node ite_9 = nm->mkNode(ITE, equal_11, t, const_rational_4);
  Node ite_8 = nm->mkNode(ITE, equal_16, ite_12, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_18, t, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_20, t, ite_7);
  Node ite_5 = nm->mkNode(ITE, geq_25, ite_22, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_33, ite_26, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_51, ite_34, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_60, ite_52, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_67, ite_61, ite_2);
  return ite_1;
}

// (define-fun int_bvand_4_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// s (ite (>= s t) s (ite (= t 2) 0 (ite (= t 3) s (ite (= t 4) (ite (= s 1) 0
// (ite (= s 2) 0 0)) (ite (= t 5) (ite (= s 1) s (ite (= s 2) 0 (ite (= s 3) 1
// s))) (ite (= t 6) (ite (= s 1) 0 (ite (= s 5) 4 (ite (= s 2) s (ite (= s 3) 2
// s)))) (ite (= t 7) s (ite (= t 8) (ite (= s 1) 0 (ite (= s 7) 0 (ite (= s 2)
// 0 (ite (= s 3) 0 (ite (= s 4) 0 (ite (= s 5) 0 0)))))) (ite (= t 9) (ite (= s
// 1) s (ite (= s 8) s (ite (= s 2) 0 (ite (= s 3) 1 (ite (= s 4) 0 (ite (= s 5)
// 1 (ite (= s 6) 0 1))))))) (ite (= t 10) (ite (= s 1) 0 (ite (= s 2) s (ite (=
// s 3) 2 (ite (= s 4) 0 (ite (= s 5) 0 (ite (= s 6) 2 (ite (= s 7) 2 (ite (= s
// 8) s 8)))))))) (ite (= t 11) (ite (= s 1) s (ite (= s 2) s (ite (= s 3) s
// (ite (= s 4) 0 (ite (= s 5) 1 (ite (= s 6) 2 (ite (= s 7) 3 s))))))) (ite (=
// t 12) (ite (= s 1) 0 (ite (= s 2) 0 (ite (= s 3) 0 (ite (= s 11) 8 (ite (= s
// 4) s (ite (= s 5) 4 (ite (= s 6) 4 (ite (= s 7) 4 (ite (= s 8) s (ite (= s 9)
// 8 8)))))))))) (ite (= t 13) (ite (= s 1) s (ite (= s 2) 0 (ite (= s 3) 1 (ite
// (= s 4) s (ite (= s 5) s (ite (= s 6) 4 (ite (= s 7) 5 (ite (= s 8) s (ite (=
// s 9) s (ite (= s 10) 8 (ite (= s 12) s 9))))))))))) (ite (= t 14) (ite (= s
// 1) 0 (ite (= s 2) s (ite (= s 3) 2 (ite (= s 4) s (ite (= s 5) 4 (ite (= s 6)
// s (ite (= s 7) 6 (ite (= s 8) s (ite (= s 9) 8 (ite (= s 10) s (ite (= s 11)
// 10 (ite (= s 12) s 12)))))))))))) s))))))))))))))) (ite (>= s (* 2 t)) (ite
// (>= s (* 3 t)) (ite (>= s (* 4 t)) (ite (>= s (* 5 t)) (ite (>= s (* 6 t))
// (ite (>= s (* 7 t)) (ite (>= s (* 8 t)) (ite (>= s (* 9 t)) (ite (>= s (* 10
// t)) (ite (>= s (* 11 t)) (ite (>= s (* 12 t)) (ite (>= s (* 13 t)) (ite (>= s
// (* 14 t)) (ite (>= s (* 15 t)) t 0) t) 0) t) 0) t) 0) t) (ite (= s (* 6 t))
// (ite (= t 1) 0 0) 0)) t) (ite (= s (* 4 t)) (ite (= t 1) 0 (ite (= t 2) 0 0))
// (ite (= s 14) 2 (ite (= t 2) 0 1)))) (ite (= s (* 3 t)) (ite (= t 1) t (ite
// (= t 2) t (ite (= t 3) 1 t))) (ite (= t 2) t (ite (= t 3) (ite (= s 10) 2 t)
// t)))) (ite (= s (* 2 t)) (ite (= t 1) 0 (ite (= t 2) 0 (ite (= t 3) 2 (ite (=
// s 14) 6 (ite (= t 4) 0 (ite (= t 5) 0 4)))))) (ite (= t 2) 0 (ite (= t 3)
// (ite (= s 8) 0 t) (ite (= t 4) (ite (= s 11) 0 (ite (= s 9) 0 0)) (ite (= t
// 5) (ite (= s 11) 1 (ite (= s 12) 4 (ite (= s 13) t 4))) (ite (= t 6) (ite (=
// s 13) 4 t) t))))))) (ite (= t 2) t (ite (= t 3) (ite (= s 4) 0 1) (ite (= t
// 4) t (ite (= t 5) (ite (= s 6) 4 (ite (= s 7) t (ite (= s 8) 0 1))) (ite (= t
// 6) (ite (= s 7) t (ite (= s 8) 0 (ite (= s 9) 0 (ite (= s 10) 2 2)))) (ite (=
// t 7) (ite (= s 8) 0 (ite (= s 9) 1 (ite (= s 10) 2 (ite (= s 13) 5 (ite (= s
// 11) 3 4))))) (ite (= t 8) t (ite (= t 9) (ite (= s 10) 8 (ite (= s 11) t (ite
// (= s 12) 8 (ite (= s 15) t (ite (= s 13) t 8))))) (ite (= t 10) (ite (= s 11)
// t (ite (= s 12) 8 (ite (= s 13) 8 t))) (ite (= t 11) (ite (= s 12) 8 (ite (=
// s 13) 9 (ite (= s 15) t 10))) (ite (= t 12) t (ite (= t 13) (ite (= s 14) 12
// t) t)))))))))))))))
Node int_bvand_4_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_250 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_249 = nm->mkNode(EQUAL, s, const_rational_0);
  Node geq_248 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_78 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_77 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_188 = nm->mkNode(EQUAL, s, const_rational_1);
  Node equal_187 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_247 = nm->mkNode(ITE, equal_187, const_rational_0, const_rational_0);
  Node ite_246 = nm->mkNode(ITE, equal_188, const_rational_0, ite_247);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_73 = nm->mkNode(EQUAL, t, const_rational_5);
  Node equal_186 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_245 = nm->mkNode(ITE, equal_186, const_rational_1, s);
  Node ite_244 = nm->mkNode(ITE, equal_187, const_rational_0, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_188, s, ite_244);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_67 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_185 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_242 = nm->mkNode(ITE, equal_186, const_rational_2, s);
  Node ite_241 = nm->mkNode(ITE, equal_187, s, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_185, const_rational_4, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_188, const_rational_0, ite_240);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_60 = nm->mkNode(EQUAL, t, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_46 = nm->mkNode(EQUAL, t, const_rational_8);
  Node equal_66 = nm->mkNode(EQUAL, s, const_rational_7);
  Node equal_76 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_238 = nm->mkNode(ITE, equal_185, const_rational_0, const_rational_0);
  Node ite_237 = nm->mkNode(ITE, equal_76, const_rational_0, ite_238);
  Node ite_236 = nm->mkNode(ITE, equal_186, const_rational_0, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_187, const_rational_0, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_66, const_rational_0, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_188, const_rational_0, ite_234);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_45 = nm->mkNode(EQUAL, t, const_rational_9);
  Node equal_59 = nm->mkNode(EQUAL, s, const_rational_8);
  Node equal_72 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_232 = nm->mkNode(ITE, equal_72, const_rational_0, const_rational_1);
  Node ite_231 = nm->mkNode(ITE, equal_185, const_rational_1, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_76, const_rational_0, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_186, const_rational_1, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_187, const_rational_0, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_59, s, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_188, s, ite_227);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_38 = nm->mkNode(EQUAL, t, const_rational_10);
  Node ite_225 = nm->mkNode(ITE, equal_59, s, const_rational_8);
  Node ite_224 = nm->mkNode(ITE, equal_66, const_rational_2, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_72, const_rational_2, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_185, const_rational_0, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_76, const_rational_0, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_186, const_rational_2, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_187, s, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_188, const_rational_0, ite_219);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_32 = nm->mkNode(EQUAL, t, const_rational_11);
  Node ite_217 = nm->mkNode(ITE, equal_66, const_rational_3, s);
  Node ite_216 = nm->mkNode(ITE, equal_72, const_rational_2, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_185, const_rational_1, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_76, const_rational_0, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_186, s, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_187, s, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_188, s, ite_212);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_21 = nm->mkNode(EQUAL, t, const_rational_12);
  Node equal_37 = nm->mkNode(EQUAL, s, const_rational_11);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_9);
  Node ite_210 = nm->mkNode(ITE, equal_57, const_rational_8, const_rational_8);
  Node ite_209 = nm->mkNode(ITE, equal_59, s, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_66, const_rational_4, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_72, const_rational_4, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_185, const_rational_4, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_76, s, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_37, const_rational_8, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_186, const_rational_0, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_187, const_rational_0, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_188, const_rational_0, ite_202);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_19 = nm->mkNode(EQUAL, t, const_rational_13);
  Node equal_44 = nm->mkNode(EQUAL, s, const_rational_10);
  Node equal_31 = nm->mkNode(EQUAL, s, const_rational_12);
  Node ite_200 = nm->mkNode(ITE, equal_31, s, const_rational_9);
  Node ite_199 = nm->mkNode(ITE, equal_44, const_rational_8, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_57, s, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_59, s, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_66, const_rational_5, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_72, const_rational_4, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_185, s, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_76, s, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_186, const_rational_1, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_187, const_rational_0, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_188, s, ite_191);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_189 = nm->mkNode(EQUAL, t, const_rational_14);
  Node ite_184 = nm->mkNode(ITE, equal_31, s, const_rational_12);
  Node ite_183 = nm->mkNode(ITE, equal_37, const_rational_10, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_44, s, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_57, const_rational_8, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_59, s, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_66, const_rational_6, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_72, s, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_185, const_rational_4, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_76, s, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_186, const_rational_2, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_187, s, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_188, const_rational_0, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_189, ite_173, s);
  Node ite_171 = nm->mkNode(ITE, equal_19, ite_190, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_21, ite_201, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_32, ite_211, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_38, ite_218, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_45, ite_226, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_46, ite_233, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_60, s, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_67, ite_239, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_73, ite_243, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_74, ite_246, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_77, s, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_78, const_rational_0, ite_161);
  Node ite_159 = nm->mkNode(ITE, geq_248, s, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_249, s, ite_159);
  Node mult_101 = nm->mkNode(MULT, const_rational_2, t);
  Node geq_157 = nm->mkNode(GEQ, s, mult_101);
  Node mult_111 = nm->mkNode(MULT, const_rational_3, t);
  Node geq_156 = nm->mkNode(GEQ, s, mult_111);
  Node mult_119 = nm->mkNode(MULT, const_rational_4, t);
  Node geq_155 = nm->mkNode(GEQ, s, mult_119);
  Node mult_154 = nm->mkNode(MULT, const_rational_5, t);
  Node geq_153 = nm->mkNode(GEQ, s, mult_154);
  Node mult_125 = nm->mkNode(MULT, const_rational_6, t);
  Node geq_152 = nm->mkNode(GEQ, s, mult_125);
  Node mult_151 = nm->mkNode(MULT, const_rational_7, t);
  Node geq_150 = nm->mkNode(GEQ, s, mult_151);
  Node mult_149 = nm->mkNode(MULT, const_rational_8, t);
  Node geq_148 = nm->mkNode(GEQ, s, mult_149);
  Node mult_147 = nm->mkNode(MULT, const_rational_9, t);
  Node geq_146 = nm->mkNode(GEQ, s, mult_147);
  Node mult_145 = nm->mkNode(MULT, const_rational_10, t);
  Node geq_144 = nm->mkNode(GEQ, s, mult_145);
  Node mult_143 = nm->mkNode(MULT, const_rational_11, t);
  Node geq_142 = nm->mkNode(GEQ, s, mult_143);
  Node mult_141 = nm->mkNode(MULT, const_rational_12, t);
  Node geq_140 = nm->mkNode(GEQ, s, mult_141);
  Node mult_139 = nm->mkNode(MULT, const_rational_13, t);
  Node geq_138 = nm->mkNode(GEQ, s, mult_139);
  Node mult_137 = nm->mkNode(MULT, const_rational_14, t);
  Node geq_136 = nm->mkNode(GEQ, s, mult_137);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node mult_135 = nm->mkNode(MULT, const_rational_15, t);
  Node geq_134 = nm->mkNode(GEQ, s, mult_135);
  Node ite_133 = nm->mkNode(ITE, geq_134, t, const_rational_0);
  Node ite_132 = nm->mkNode(ITE, geq_136, ite_133, t);
  Node ite_131 = nm->mkNode(ITE, geq_138, ite_132, const_rational_0);
  Node ite_130 = nm->mkNode(ITE, geq_140, ite_131, t);
  Node ite_129 = nm->mkNode(ITE, geq_142, ite_130, const_rational_0);
  Node ite_128 = nm->mkNode(ITE, geq_144, ite_129, t);
  Node ite_127 = nm->mkNode(ITE, geq_146, ite_128, const_rational_0);
  Node ite_126 = nm->mkNode(ITE, geq_148, ite_127, t);
  Node equal_124 = nm->mkNode(EQUAL, s, mult_125);
  Node equal_99 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_123 = nm->mkNode(ITE, equal_99, const_rational_0, const_rational_0);
  Node ite_122 = nm->mkNode(ITE, equal_124, ite_123, const_rational_0);
  Node ite_121 = nm->mkNode(ITE, geq_150, ite_126, ite_122);
  Node ite_120 = nm->mkNode(ITE, geq_152, ite_121, t);
  Node equal_118 = nm->mkNode(EQUAL, s, mult_119);
  Node ite_117 = nm->mkNode(ITE, equal_78, const_rational_0, const_rational_0);
  Node ite_116 = nm->mkNode(ITE, equal_99, const_rational_0, ite_117);
  Node equal_17 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_115 = nm->mkNode(ITE, equal_78, const_rational_0, const_rational_1);
  Node ite_114 = nm->mkNode(ITE, equal_17, const_rational_2, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_118, ite_116, ite_114);
  Node ite_112 = nm->mkNode(ITE, geq_153, ite_120, ite_113);
  Node equal_110 = nm->mkNode(EQUAL, s, mult_111);
  Node ite_109 = nm->mkNode(ITE, equal_77, const_rational_1, t);
  Node ite_108 = nm->mkNode(ITE, equal_78, t, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_99, t, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_44, const_rational_2, t);
  Node ite_105 = nm->mkNode(ITE, equal_77, ite_106, t);
  Node ite_104 = nm->mkNode(ITE, equal_78, t, ite_105);
  Node ite_103 = nm->mkNode(ITE, equal_110, ite_107, ite_104);
  Node ite_102 = nm->mkNode(ITE, geq_155, ite_112, ite_103);
  Node equal_100 = nm->mkNode(EQUAL, s, mult_101);
  Node ite_98 = nm->mkNode(ITE, equal_73, const_rational_0, const_rational_4);
  Node ite_97 = nm->mkNode(ITE, equal_74, const_rational_0, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_17, const_rational_6, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_77, const_rational_2, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_78, const_rational_0, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_99, const_rational_0, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_59, const_rational_0, t);
  Node ite_91 = nm->mkNode(ITE, equal_57, const_rational_0, const_rational_0);
  Node ite_90 = nm->mkNode(ITE, equal_37, const_rational_0, ite_91);
  Node equal_29 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_89 = nm->mkNode(ITE, equal_29, t, const_rational_4);
  Node ite_88 = nm->mkNode(ITE, equal_31, const_rational_4, ite_89);
  Node ite_87 = nm->mkNode(ITE, equal_37, const_rational_1, ite_88);
  Node ite_86 = nm->mkNode(ITE, equal_29, const_rational_4, t);
  Node ite_85 = nm->mkNode(ITE, equal_67, ite_86, t);
  Node ite_84 = nm->mkNode(ITE, equal_73, ite_87, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_74, ite_90, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_77, ite_92, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_78, const_rational_0, ite_82);
  Node ite_80 = nm->mkNode(ITE, equal_100, ite_93, ite_81);
  Node ite_79 = nm->mkNode(ITE, geq_156, ite_102, ite_80);
  Node ite_75 = nm->mkNode(ITE, equal_76, const_rational_0, const_rational_1);
  Node ite_71 = nm->mkNode(ITE, equal_59, const_rational_0, const_rational_1);
  Node ite_70 = nm->mkNode(ITE, equal_66, t, ite_71);
  Node ite_69 = nm->mkNode(ITE, equal_72, const_rational_4, ite_70);
  Node ite_65 = nm->mkNode(ITE, equal_44, const_rational_2, const_rational_2);
  Node ite_64 = nm->mkNode(ITE, equal_57, const_rational_0, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_59, const_rational_0, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_66, t, ite_63);
  Node ite_51 = nm->mkNode(ITE, equal_37, const_rational_3, const_rational_4);
  Node ite_50 = nm->mkNode(ITE, equal_29, const_rational_5, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_44, const_rational_2, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_57, const_rational_1, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_59, const_rational_0, ite_48);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_43 = nm->mkNode(ITE, equal_29, t, const_rational_8);
  Node ite_42 = nm->mkNode(ITE, equal_26, t, ite_43);
  Node ite_41 = nm->mkNode(ITE, equal_31, const_rational_8, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_37, t, ite_41);
  Node ite_39 = nm->mkNode(ITE, equal_44, const_rational_8, ite_40);
  Node ite_36 = nm->mkNode(ITE, equal_29, const_rational_8, t);
  Node ite_35 = nm->mkNode(ITE, equal_31, const_rational_8, ite_36);
  Node ite_34 = nm->mkNode(ITE, equal_37, t, ite_35);
  Node ite_24 = nm->mkNode(ITE, equal_26, t, const_rational_10);
  Node ite_23 = nm->mkNode(ITE, equal_29, const_rational_9, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_31, const_rational_8, ite_23);
  Node ite_15 = nm->mkNode(ITE, equal_17, const_rational_12, t);
  Node ite_14 = nm->mkNode(ITE, equal_19, ite_15, t);
  Node ite_13 = nm->mkNode(ITE, equal_21, t, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_32, ite_22, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_38, ite_34, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_45, ite_39, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_46, t, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_60, ite_47, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_67, ite_62, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_73, ite_69, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_74, t, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_77, ite_75, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_78, t, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_157, ite_79, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_250, ite_158, ite_2);
  return ite_1;
}

// (define-fun int_bvand_4_nia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (* s t) (ite (= t 14) 0 (ite (= t 2) 0 (ite (= t 3) s (ite (= t 4)
// 0 (ite (= t 5) s (ite (= t 6) 0 (ite (= t 7) s (ite (= t 8) 0 (ite (= t 9) s
// (ite (= t 10) 0 (ite (= t 13) s (ite (= t 11) s (ite (= t 12) 0
// s)))))))))))))) (ite (>= s (* s t)) (ite (= s (* s t)) (ite (= s (+ t t)) 0
// (ite (= s 3) t (ite (= s 4) 0 (ite (= s 5) t (ite (= s 6) 0 (ite (= s 7) t
// (ite (= s 8) 0 (ite (= s 9) t (ite (= s 10) 0 (ite (= s 11) t (ite (= s 12) 0
// (ite (= s 15) t (ite (= s 13) t 0))))))))))))) (* s t)) (ite (>= t s) (ite
// (>= s t) s (ite (= t 3) s (ite (= t 4) (ite (= s 2) 0 0) (ite (= t 5) (ite (=
// s 2) 0 (ite (= s 3) 1 s)) (ite (= t 6) (ite (= s 2) s (ite (= s 3) 2 (ite (=
// s 4) s 4))) (ite (= t 7) s (ite (= t 8) (ite (= s 2) 0 (ite (= s 3) 0 (ite (=
// s 4) 0 (ite (= s 5) 0 (ite (= s 6) 0 0))))) (ite (= t 9) (ite (= s 2) 0 (ite
// (= s 3) 1 (ite (= s 4) 0 (ite (= s 5) 1 (ite (= s 8) s (ite (= s 6) 0 1))))))
// (ite (= t 10) (ite (= s 9) 8 (ite (= s 8) s (ite (= s 2) s (ite (= s 3) 2
// (ite (= s 4) 0 (ite (= s 5) 0 (ite (= s 6) 2 2))))))) (ite (= t 11) (ite (= s
// 2) s (ite (= s 3) s (ite (= s 4) 0 (ite (= s 5) 1 (ite (= s 6) 2 (ite (= s 7)
// 3 s)))))) (ite (= t 12) (ite (= s 2) 0 (ite (= s 3) 0 (ite (= s 4) s (ite (=
// s 5) 4 (ite (= s 6) 4 (ite (= s 7) 4 (ite (= s 8) s (ite (= s 11) 8 (ite (= s
// 9) 8 8))))))))) (ite (= t 13) (ite (= s 2) 0 (ite (= s 3) 1 (ite (= s 4) s
// (ite (= s 5) s (ite (= s 6) 4 (ite (= s 7) 5 (ite (= s 8) s (ite (= s 9) s
// (ite (= s 10) 8 (ite (= s 12) s 9)))))))))) (ite (= t 14) (ite (= s 2) s (ite
// (= s 3) 2 (ite (= s 4) s (ite (= s 5) 4 (ite (= s 6) s (ite (= s 7) 6 (ite (=
// s 8) s (ite (= s 9) 8 (ite (= s 10) s (ite (= s 11) 10 (ite (= s 13) 12
// s))))))))))) s))))))))))))) (ite (>= s (* t t)) (ite (= s (* t t)) (ite (= s
// (+ t t)) 0 1) (ite (= t 2) (ite (= s 5) 0 (ite (= s 6) t (ite (= s 7) t (ite
// (= s 8) 0 (ite (= s 15) t (ite (= s 9) 0 (ite (= s 10) t (ite (= s 11) t (ite
// (= s 12) 0 (ite (= s 13) 0 t)))))))))) (ite (= s 10) 2 (ite (= s 11) t (ite
// (= s 12) 0 (ite (= s 15) t (ite (= s 13) 1 2))))))) (ite (>= s (+ t t)) (ite
// (= s (+ t t)) (ite (= t 3) 2 (ite (= t 4) 0 (ite (= t 5) 0 (ite (= t 6) 4
// 6)))) (ite (= s 15) t (ite (= t 3) (ite (= s 7) t 0) (ite (= t 4) (ite (= s
// 9) 0 (ite (= s 10) 0 (ite (= s 11) 0 t))) (ite (= t 5) (ite (= s 11) 1 (ite
// (= s 12) 4 (ite (= s 13) t 4))) (ite (= s 13) 4 t)))))) (ite (= t 2) t (ite
// (= t 3) (ite (= s 5) 1 0) (ite (= t 4) t (ite (= t 5) (ite (= s 9) 1 (ite (=
// s 6) 4 (ite (= s 7) t 0))) (ite (= t 6) (ite (= s 7) t (ite (= s 8) 0 (ite (=
// s 9) 0 (ite (= s 10) 2 2)))) (ite (= t 7) (ite (= s 8) 0 (ite (= s 9) 1 (ite
// (= s 10) 2 (ite (= s 11) 3 (ite (= s 12) 4 5))))) (ite (= t 8) t (ite (= t 9)
// (ite (= s 10) 8 (ite (= s 11) t (ite (= s 12) 8 (ite (= s 13) t (ite (= s 14)
// 8 t))))) (ite (= t 10) (ite (= s 11) t (ite (= s 12) 8 (ite (= s 15) t (ite
// (= s 13) 8 t)))) (ite (= t 11) (ite (= s 15) t (ite (= s 14) 10 (ite (= s 12)
// 8 9))) (ite (= t 12) t (ite (= t 13) (ite (= s 14) 12 t) t))))))))))))))))))
Node int_bvand_4_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_234 = nm->mkNode(MULT, s, s);
  Node equal_233 = nm->mkNode(EQUAL, s, mult_234);
  Node mult_203 = nm->mkNode(MULT, s, t);
  Node geq_218 = nm->mkNode(GEQ, s, mult_203);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_150 = nm->mkNode(EQUAL, t, const_rational_14);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_82 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_81 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_78 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_77 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_71 = nm->mkNode(EQUAL, t, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_64 = nm->mkNode(EQUAL, t, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_50 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_49 = nm->mkNode(EQUAL, t, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_42 = nm->mkNode(EQUAL, t, const_rational_10);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_22 = nm->mkNode(EQUAL, t, const_rational_13);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_34 = nm->mkNode(EQUAL, t, const_rational_11);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_24 = nm->mkNode(EQUAL, t, const_rational_12);
  Node ite_232 = nm->mkNode(ITE, equal_24, const_rational_0, s);
  Node ite_231 = nm->mkNode(ITE, equal_34, s, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_22, s, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_42, const_rational_0, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_49, s, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_50, const_rational_0, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_64, s, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_71, const_rational_0, ite_226);
  Node ite_224 = nm->mkNode(ITE, equal_77, s, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_78, const_rational_0, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_81, s, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_82, const_rational_0, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_150, const_rational_0, ite_221);
  Node ite_219 = nm->mkNode(ITE, geq_218, mult_203, ite_220);
  Node equal_217 = nm->mkNode(EQUAL, s, mult_203);
  Node plus_100 = nm->mkNode(PLUS, t, t);
  Node equal_99 = nm->mkNode(EQUAL, s, plus_100);
  Node equal_148 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_147 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_80 = nm->mkNode(EQUAL, s, const_rational_5);
  Node equal_76 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_70 = nm->mkNode(EQUAL, s, const_rational_7);
  Node equal_63 = nm->mkNode(EQUAL, s, const_rational_8);
  Node equal_61 = nm->mkNode(EQUAL, s, const_rational_9);
  Node equal_48 = nm->mkNode(EQUAL, s, const_rational_10);
  Node equal_41 = nm->mkNode(EQUAL, s, const_rational_11);
  Node equal_30 = nm->mkNode(EQUAL, s, const_rational_12);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_32 = nm->mkNode(EQUAL, s, const_rational_15);
  Node equal_40 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_216 = nm->mkNode(ITE, equal_40, t, const_rational_0);
  Node ite_215 = nm->mkNode(ITE, equal_32, t, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_30, const_rational_0, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_41, t, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_48, const_rational_0, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_61, t, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_63, const_rational_0, ite_211);
  Node ite_209 = nm->mkNode(ITE, equal_70, t, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_76, const_rational_0, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_80, t, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_147, const_rational_0, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_148, t, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_99, const_rational_0, ite_205);
  Node ite_202 = nm->mkNode(ITE, equal_217, ite_204, mult_203);
  Node geq_201 = nm->mkNode(GEQ, t, s);
  Node geq_200 = nm->mkNode(GEQ, s, t);
  Node equal_149 = nm->mkNode(EQUAL, s, const_rational_2);
  Node ite_199 = nm->mkNode(ITE, equal_149, const_rational_0, const_rational_0);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_198 = nm->mkNode(ITE, equal_148, const_rational_1, s);
  Node ite_197 = nm->mkNode(ITE, equal_149, const_rational_0, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_147, s, const_rational_4);
  Node ite_195 = nm->mkNode(ITE, equal_148, const_rational_2, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_149, s, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_76, const_rational_0, const_rational_0);
  Node ite_192 = nm->mkNode(ITE, equal_80, const_rational_0, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_147, const_rational_0, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_148, const_rational_0, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_149, const_rational_0, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_76, const_rational_0, const_rational_1);
  Node ite_187 = nm->mkNode(ITE, equal_63, s, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_80, const_rational_1, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_147, const_rational_0, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_148, const_rational_1, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_149, const_rational_0, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_76, const_rational_2, const_rational_2);
  Node ite_181 = nm->mkNode(ITE, equal_80, const_rational_0, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_147, const_rational_0, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_148, const_rational_2, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_149, s, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_63, s, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_61, const_rational_8, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_70, const_rational_3, s);
  Node ite_174 = nm->mkNode(ITE, equal_76, const_rational_2, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_80, const_rational_1, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_147, const_rational_0, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_148, s, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_149, s, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_61, const_rational_8, const_rational_8);
  Node ite_168 = nm->mkNode(ITE, equal_41, const_rational_8, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_63, s, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_70, const_rational_4, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_76, const_rational_4, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_80, const_rational_4, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_147, s, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_148, const_rational_0, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_149, const_rational_0, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_30, s, const_rational_9);
  Node ite_159 = nm->mkNode(ITE, equal_48, const_rational_8, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_61, s, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_63, s, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_70, const_rational_5, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_76, const_rational_4, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_80, s, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_147, s, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_148, const_rational_1, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_149, const_rational_0, ite_152);
  Node ite_146 = nm->mkNode(ITE, equal_40, const_rational_12, s);
  Node ite_145 = nm->mkNode(ITE, equal_41, const_rational_10, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_48, s, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_61, const_rational_8, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_63, s, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_70, const_rational_6, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_76, s, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_80, const_rational_4, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_147, s, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_148, const_rational_2, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_149, s, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_150, ite_136, s);
  Node ite_134 = nm->mkNode(ITE, equal_22, ite_151, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_24, ite_161, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_34, ite_170, ite_133);
  Node ite_131 = nm->mkNode(ITE, equal_42, ite_176, ite_132);
  Node ite_130 = nm->mkNode(ITE, equal_49, ite_183, ite_131);
  Node ite_129 = nm->mkNode(ITE, equal_50, ite_189, ite_130);
  Node ite_128 = nm->mkNode(ITE, equal_64, s, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_71, ite_194, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_77, ite_197, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_78, ite_199, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_81, s, ite_125);
  Node ite_123 = nm->mkNode(ITE, geq_200, s, ite_124);
  Node mult_121 = nm->mkNode(MULT, t, t);
  Node geq_122 = nm->mkNode(GEQ, s, mult_121);
  Node equal_120 = nm->mkNode(EQUAL, s, mult_121);
  Node ite_119 = nm->mkNode(ITE, equal_99, const_rational_0, const_rational_1);
  Node ite_118 = nm->mkNode(ITE, equal_40, const_rational_0, t);
  Node ite_117 = nm->mkNode(ITE, equal_30, const_rational_0, ite_118);
  Node ite_116 = nm->mkNode(ITE, equal_41, t, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_48, t, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_61, const_rational_0, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_32, t, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_63, const_rational_0, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_70, t, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_76, t, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_80, const_rational_0, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_40, const_rational_1, const_rational_2);
  Node ite_107 = nm->mkNode(ITE, equal_32, t, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_30, const_rational_0, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_41, t, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_48, const_rational_2, ite_105);
  Node ite_103 = nm->mkNode(ITE, equal_82, ite_109, ite_104);
  Node ite_102 = nm->mkNode(ITE, equal_120, ite_119, ite_103);
  Node geq_101 = nm->mkNode(GEQ, s, plus_100);
  Node ite_98 = nm->mkNode(ITE, equal_71, const_rational_4, const_rational_6);
  Node ite_97 = nm->mkNode(ITE, equal_77, const_rational_0, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_78, const_rational_0, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_81, const_rational_2, ite_96);
  Node ite_75 = nm->mkNode(ITE, equal_70, t, const_rational_0);
  Node ite_94 = nm->mkNode(ITE, equal_41, const_rational_0, t);
  Node ite_93 = nm->mkNode(ITE, equal_48, const_rational_0, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_61, const_rational_0, ite_93);
  Node ite_91 = nm->mkNode(ITE, equal_40, t, const_rational_4);
  Node ite_90 = nm->mkNode(ITE, equal_30, const_rational_4, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_41, const_rational_1, ite_90);
  Node ite_88 = nm->mkNode(ITE, equal_40, const_rational_4, t);
  Node ite_87 = nm->mkNode(ITE, equal_77, ite_89, ite_88);
  Node ite_86 = nm->mkNode(ITE, equal_78, ite_92, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_81, ite_75, ite_86);
  Node ite_84 = nm->mkNode(ITE, equal_32, t, ite_85);
  Node ite_83 = nm->mkNode(ITE, equal_99, ite_95, ite_84);
  Node ite_79 = nm->mkNode(ITE, equal_80, const_rational_1, const_rational_0);
  Node ite_74 = nm->mkNode(ITE, equal_76, const_rational_4, ite_75);
  Node ite_73 = nm->mkNode(ITE, equal_61, const_rational_1, ite_74);
  Node ite_69 = nm->mkNode(ITE, equal_48, const_rational_2, const_rational_2);
  Node ite_68 = nm->mkNode(ITE, equal_61, const_rational_0, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_63, const_rational_0, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_70, t, ite_67);
  Node ite_55 = nm->mkNode(ITE, equal_30, const_rational_4, const_rational_5);
  Node ite_54 = nm->mkNode(ITE, equal_41, const_rational_3, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_48, const_rational_2, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_61, const_rational_1, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_63, const_rational_0, ite_52);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_47 = nm->mkNode(ITE, equal_20, const_rational_8, t);
  Node ite_46 = nm->mkNode(ITE, equal_40, t, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_30, const_rational_8, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_41, t, ite_45);
  Node ite_43 = nm->mkNode(ITE, equal_48, const_rational_8, ite_44);
  Node ite_39 = nm->mkNode(ITE, equal_40, const_rational_8, t);
  Node ite_38 = nm->mkNode(ITE, equal_32, t, ite_39);
  Node ite_37 = nm->mkNode(ITE, equal_30, const_rational_8, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_41, t, ite_37);
  Node ite_27 = nm->mkNode(ITE, equal_30, const_rational_8, const_rational_9);
  Node ite_26 = nm->mkNode(ITE, equal_20, const_rational_10, ite_27);
  Node ite_25 = nm->mkNode(ITE, equal_32, t, ite_26);
  Node ite_18 = nm->mkNode(ITE, equal_20, const_rational_12, t);
  Node ite_17 = nm->mkNode(ITE, equal_22, ite_18, t);
  Node ite_16 = nm->mkNode(ITE, equal_24, t, ite_17);
  Node ite_15 = nm->mkNode(ITE, equal_34, ite_25, ite_16);
  Node ite_14 = nm->mkNode(ITE, equal_42, ite_36, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_49, ite_43, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_50, t, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_64, ite_51, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_71, ite_66, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_77, ite_73, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_78, t, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_81, ite_79, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_82, t, ite_7);
  Node ite_5 = nm->mkNode(ITE, geq_101, ite_83, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_122, ite_102, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_201, ite_123, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_218, ite_202, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_233, ite_219, ite_2);
  return ite_1;
}

// (define-fun int_bvor_1_lia ((s Int) (t Int)) Int (ite (= s t) t 1))
Node int_bvor_1_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_3 = nm->mkNode(EQUAL, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_1 = nm->mkNode(ITE, equal_3, t, const_rational_1);
  return ite_1;
}

// (define-fun int_bvor_1_nia ((s Int) (t Int)) Int (ite (= s t) t 1))
Node int_bvor_1_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node equal_3 = nm->mkNode(EQUAL, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_1 = nm->mkNode(ITE, equal_3, t, const_rational_1);
  return ite_1;
}

// (define-fun int_bvor_2_lia ((s Int) (t Int)) Int (ite (= 3 (+ s t)) 3 (ite
// (>= s t) s t)))
Node int_bvor_2_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node plus_6 = nm->mkNode(PLUS, s, t);
  Node equal_5 = nm->mkNode(EQUAL, const_rational_3, plus_6);
  Node geq_3 = nm->mkNode(GEQ, s, t);
  Node ite_2 = nm->mkNode(ITE, geq_3, s, t);
  Node ite_1 = nm->mkNode(ITE, equal_5, const_rational_3, ite_2);
  return ite_1;
}

// (define-fun int_bvor_2_nia ((s Int) (t Int)) Int (ite (= 2 (* s t)) 3 (ite
// (>= s t) s t)))
Node int_bvor_2_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node mult_6 = nm->mkNode(MULT, s, t);
  Node equal_5 = nm->mkNode(EQUAL, const_rational_2, mult_6);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node geq_3 = nm->mkNode(GEQ, s, t);
  Node ite_2 = nm->mkNode(ITE, geq_3, s, t);
  Node ite_1 = nm->mkNode(ITE, equal_5, const_rational_3, ite_2);
  return ite_1;
}

// (define-fun int_bvor_3_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (+ s t) (ite (>= s t) t (ite (= t 2) (+ s t) (ite (= t 3) t (ite (= t 4) (+ s
// t) (ite (= t 5) (ite (= s 1) t (ite (= s 2) (+ s t) (ite (= s 3) 7 t))) (ite
// (= s 1) (* 7 s) (ite (= s 2) t (ite (= s 3) 7 (ite (= s 4) t (ite (= s 6) t
// 7))))))))))) (ite (>= s (* 2 t)) (ite (>= s (* 3 t)) (ite (>= s (* 4 t)) (ite
// (>= s (* 5 t)) (ite (>= s (* 6 t)) (ite (>= s (* 7 t)) s (+ s t)) s) (+ s t))
// s) (ite (= s (* 2 t)) (ite (= t 1) (+ s t) (ite (= t 2) (+ s t) 7)) (ite (= t
// 2) (+ s t) s))) (ite (= t 2) s (ite (= t 3) (ite (= s 4) (+ s t) 7) (ite (= t
// 4) s (ite (= s 7) s 7)))))))
Node int_bvor_3_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_67 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_65 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_12 = nm->mkNode(PLUS, s, t);
  Node geq_64 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_16 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_14 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_9 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_63 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_59 = nm->mkNode(EQUAL, s, const_rational_1);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_2);
  Node equal_56 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node ite_62 = nm->mkNode(ITE, equal_56, const_rational_7, t);
  Node ite_61 = nm->mkNode(ITE, equal_57, plus_12, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_59, t, ite_61);
  Node mult_58 = nm->mkNode(MULT, const_rational_7, s);
  Node equal_13 = nm->mkNode(EQUAL, s, const_rational_4);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_55 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_54 = nm->mkNode(ITE, equal_55, t, const_rational_7);
  Node ite_53 = nm->mkNode(ITE, equal_13, t, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_56, const_rational_7, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_57, t, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_59, mult_58, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_63, ite_60, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_9, plus_12, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_14, t, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_16, plus_12, ite_47);
  Node ite_45 = nm->mkNode(ITE, geq_64, t, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_65, plus_12, ite_45);
  Node mult_26 = nm->mkNode(MULT, const_rational_2, t);
  Node geq_43 = nm->mkNode(GEQ, s, mult_26);
  Node mult_42 = nm->mkNode(MULT, const_rational_3, t);
  Node geq_41 = nm->mkNode(GEQ, s, mult_42);
  Node mult_40 = nm->mkNode(MULT, const_rational_4, t);
  Node geq_39 = nm->mkNode(GEQ, s, mult_40);
  Node mult_37 = nm->mkNode(MULT, const_rational_5, t);
  Node geq_36 = nm->mkNode(GEQ, s, mult_37);
  Node mult_34 = nm->mkNode(MULT, const_rational_6, t);
  Node geq_33 = nm->mkNode(GEQ, s, mult_34);
  Node mult_32 = nm->mkNode(MULT, const_rational_7, t);
  Node geq_31 = nm->mkNode(GEQ, s, mult_32);
  Node ite_30 = nm->mkNode(ITE, geq_31, s, plus_12);
  Node ite_29 = nm->mkNode(ITE, geq_33, ite_30, s);
  Node ite_28 = nm->mkNode(ITE, geq_36, ite_29, plus_12);
  Node ite_27 = nm->mkNode(ITE, geq_39, ite_28, s);
  Node equal_25 = nm->mkNode(EQUAL, s, mult_26);
  Node equal_23 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_22 = nm->mkNode(ITE, equal_16, plus_12, const_rational_7);
  Node ite_21 = nm->mkNode(ITE, equal_23, plus_12, ite_22);
  Node ite_20 = nm->mkNode(ITE, equal_16, plus_12, s);
  Node ite_19 = nm->mkNode(ITE, equal_25, ite_21, ite_20);
  Node ite_18 = nm->mkNode(ITE, geq_41, ite_27, ite_19);
  Node ite_11 = nm->mkNode(ITE, equal_13, plus_12, const_rational_7);
  Node equal_8 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_6 = nm->mkNode(ITE, equal_8, s, const_rational_7);
  Node ite_5 = nm->mkNode(ITE, equal_9, s, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_14, ite_11, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_16, s, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_43, ite_18, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_67, ite_44, ite_2);
  return ite_1;
}

// (define-fun int_bvor_3_nia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (ite (>= t s) t (+ s t)) (ite (= t 2) (+ s t) (ite (= t 3) t (ite
// (= t 4) (+ s t) (ite (= t 5) t (* s 7)))))) (ite (>= s (* s t)) (ite (= s (*
// s t)) (ite (= s (+ t t)) (+ s t) (ite (= s 3) s (ite (= s 4) (+ s t) (ite (=
// s 5) s (ite (= s 6) (+ s t) s))))) (+ s t)) (ite (>= t s) (ite (>= s t) t
// (ite (= t 3) t (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 2) (+ s t) (ite (=
// s 3) (+ s 4) t)) (ite (= s 2) t (ite (= s 3) (+ s 4) (ite (= s 4) t (ite (= s
// 5) (+ s 2) t)))))))) (ite (>= s (* t t)) (ite (= s (* t t)) (+ s t) (ite (= s
// 5) (+ s t) s)) (ite (>= s (+ t t)) (ite (= s (+ t t)) (+ s 1) s) (ite (= s 7)
// s (ite (= t 2) s (ite (= t 3) (ite (= s 4) (+ s t) (+ s 2)) (ite (= t 4) s (+
// s 1)))))))))))
Node int_bvor_3_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_70 = nm->mkNode(MULT, s, s);
  Node equal_69 = nm->mkNode(EQUAL, s, mult_70);
  Node mult_60 = nm->mkNode(MULT, s, t);
  Node geq_61 = nm->mkNode(GEQ, s, mult_60);
  Node geq_50 = nm->mkNode(GEQ, t, s);
  Node plus_17 = nm->mkNode(PLUS, s, t);
  Node ite_68 = nm->mkNode(ITE, geq_50, t, plus_17);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_21 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_19 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_12 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_48 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node mult_67 = nm->mkNode(MULT, s, const_rational_7);
  Node ite_66 = nm->mkNode(ITE, equal_48, t, mult_67);
  Node ite_65 = nm->mkNode(ITE, equal_12, plus_17, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_19, t, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_21, plus_17, ite_64);
  Node ite_62 = nm->mkNode(ITE, geq_61, ite_68, ite_63);
  Node equal_59 = nm->mkNode(EQUAL, s, mult_60);
  Node plus_26 = nm->mkNode(PLUS, t, t);
  Node equal_25 = nm->mkNode(EQUAL, s, plus_26);
  Node equal_44 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_18 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_30 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_57 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_56 = nm->mkNode(ITE, equal_57, plus_17, s);
  Node ite_55 = nm->mkNode(ITE, equal_30, s, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_18, plus_17, ite_55);
  Node ite_53 = nm->mkNode(ITE, equal_44, s, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_25, plus_17, ite_53);
  Node ite_51 = nm->mkNode(ITE, equal_59, ite_52, plus_17);
  Node geq_49 = nm->mkNode(GEQ, s, t);
  Node equal_45 = nm->mkNode(EQUAL, s, const_rational_2);
  Node plus_43 = nm->mkNode(PLUS, s, const_rational_4);
  Node ite_47 = nm->mkNode(ITE, equal_44, plus_43, t);
  Node ite_46 = nm->mkNode(ITE, equal_45, plus_17, ite_47);
  Node plus_15 = nm->mkNode(PLUS, s, const_rational_2);
  Node ite_42 = nm->mkNode(ITE, equal_30, plus_15, t);
  Node ite_41 = nm->mkNode(ITE, equal_18, t, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_44, plus_43, ite_41);
  Node ite_39 = nm->mkNode(ITE, equal_45, t, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_48, ite_46, ite_39);
  Node ite_37 = nm->mkNode(ITE, equal_12, plus_17, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_19, t, ite_37);
  Node ite_35 = nm->mkNode(ITE, geq_49, t, ite_36);
  Node mult_33 = nm->mkNode(MULT, t, t);
  Node geq_34 = nm->mkNode(GEQ, s, mult_33);
  Node equal_32 = nm->mkNode(EQUAL, s, mult_33);
  Node ite_29 = nm->mkNode(ITE, equal_30, plus_17, s);
  Node ite_28 = nm->mkNode(ITE, equal_32, plus_17, ite_29);
  Node geq_27 = nm->mkNode(GEQ, s, plus_26);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node plus_10 = nm->mkNode(PLUS, s, const_rational_1);
  Node ite_24 = nm->mkNode(ITE, equal_25, plus_10, s);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_14 = nm->mkNode(ITE, equal_18, plus_17, plus_15);
  Node ite_9 = nm->mkNode(ITE, equal_12, s, plus_10);
  Node ite_8 = nm->mkNode(ITE, equal_19, ite_14, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_21, s, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_22, s, ite_7);
  Node ite_5 = nm->mkNode(ITE, geq_27, ite_24, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_34, ite_28, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_50, ite_35, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_61, ite_51, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_69, ite_62, ite_2);
  return ite_1;
}

// (define-fun int_bvor_4_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (+ s t) (ite (>= s t) t (ite (= t 2) (+ s t) (ite (= t 3) t (ite (= t 4) (+ s
// t) (ite (= t 5) (ite (= s 1) t (ite (= s 2) (+ s t) (ite (= s 3) 7 t))) (ite
// (= t 6) (ite (= s 1) (+ s t) (ite (= s 2) t (ite (= s 3) 7 (ite (= s 4) t
// 7)))) (ite (= t 7) t (ite (= t 8) (+ s t) (ite (= t 9) (ite (= s 1) t (ite (=
// s 2) (+ s t) (ite (= s 8) t (ite (= s 3) 11 (ite (= s 4) (+ s t) (ite (= s 5)
// 13 (ite (= s 6) (+ s t) 15))))))) (ite (= t 10) (ite (= s 1) (+ s t) (ite (=
// s 2) t (ite (= s 3) 11 (ite (= s 4) (+ s t) (ite (= s 5) (+ s t) (ite (= s 6)
// 14 (ite (= s 7) 15 (ite (= s 8) t 11)))))))) (ite (= t 11) (ite (= s 1) t
// (ite (= s 2) t (ite (= s 3) t (ite (= s 4) (+ s t) (ite (= s 5) (* 3 s) (ite
// (= s 6) 15 (ite (= s 7) 15 t))))))) (ite (= t 12) (ite (= s 1) (+ s t) (ite
// (= s 2) (+ s t) (ite (= s 3) (+ s t) (ite (= s 4) t (ite (= s 5) 13 (ite (= s
// 6) 14 (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) 13 (ite (= s 10) 14
// 15)))))))))) (ite (= t 13) (ite (= s 1) t (ite (= s 2) (+ s t) (ite (= s 3)
// (* 5 s) (ite (= s 4) t (ite (= s 5) t (ite (= s 6) 15 (ite (= s 7) 15 (ite (=
// s 8) t (ite (= s 9) t (ite (= s 10) 15 (ite (= s 11) 15 t))))))))))) (ite (=
// s 1) (* 15 s) (ite (= s 2) t (ite (= s 3) (* 5 s) (ite (= s 4) t (ite (= s 5)
// (* 3 s) (ite (= s 6) t (ite (= s 7) 15 (ite (= s 8) t (ite (= s 9) 15 (ite (=
// s 10) t (ite (= s 11) 15 (ite (= s 12) t (ite (= s 13) 15
// t))))))))))))))))))))))))))) (ite (>= s (* 2 t)) (ite (>= s (* 3 t)) (ite (>=
// s (* 4 t)) (ite (>= s (* 5 t)) (ite (>= s (* 6 t)) (ite (>= s (* 7 t)) (ite
// (>= s (* 8 t)) (ite (>= s (* 9 t)) (ite (>= s (* 10 t)) (ite (>= s (* 11 t))
// (ite (>= s (* 12 t)) (ite (>= s (* 13 t)) (ite (>= s (* 14 t)) (ite (>= s (*
// 15 t)) s (+ s t)) s) (+ s t)) s) (+ s t)) s) (+ s t)) s) (+ s t)) s) (ite (=
// s (* 4 t)) (+ s t) (ite (= t 2) (+ s t) (* 5 t)))) (ite (= s (* 3 t)) (ite (=
// t 1) s (ite (= t 2) s (ite (= t 3) 11 s))) (ite (= t 2) s (ite (= t 3) (ite
// (= s 10) 11 s) s)))) (ite (= s (* 2 t)) (ite (= t 1) (+ s t) (ite (= t 2) (+
// s t) (ite (= t 3) 7 (ite (= t 4) (+ s t) (ite (= s 14) 15 (ite (= t 5) (+ s
// t) 14)))))) (ite (= t 2) (+ s t) (ite (= t 3) (ite (= s 8) (+ s t) s) (ite (=
// t 4) (+ s t) (ite (= t 5) (ite (= s 11) (* 3 t) (ite (= s 12) 13 (ite (= s
// 13) s (* 3 t)))) (ite (= t 6) (ite (= s 13) 15 s) s))))))) (ite (= t 2) s
// (ite (= t 3) (ite (= s 4) (+ s t) 7) (ite (= t 4) s (ite (= t 5) (ite (= s 6)
// 7 (ite (= s 7) s (ite (= s 8) (+ s t) 13))) (ite (= t 6) (ite (= s 7) s (ite
// (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) 14 15)))) (ite (= t 7)
// (ite (= s 8) (+ s t) (ite (= s 9) 15 (ite (= s 10) 15 (ite (= s 11) 15 (ite
// (= s 12) 15 15))))) (ite (= t 8) s (ite (= t 9) (ite (= s 10) 11 (ite (= s
// 15) s (ite (= s 11) s (ite (= s 12) 13 (ite (= s 14) 15 s))))) (ite (= t 10)
// (ite (= s 11) s (ite (= s 12) 14 (ite (= s 13) 15 s))) (ite (= t 11) (ite (=
// s 15) s (ite (= s 12) 15 (ite (= s 13) 15 15))) (ite (= t 12) s (ite (= t 13)
// (ite (= s 15) s 15) s)))))))))))))))
Node int_bvor_4_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_235 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_233 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_53 = nm->mkNode(PLUS, s, t);
  Node geq_232 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_76 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_70 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_68 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_182 = nm->mkNode(EQUAL, s, const_rational_1);
  Node equal_180 = nm->mkNode(EQUAL, s, const_rational_2);
  Node equal_179 = nm->mkNode(EQUAL, s, const_rational_3);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node ite_231 = nm->mkNode(ITE, equal_179, const_rational_7, t);
  Node ite_230 = nm->mkNode(ITE, equal_180, plus_53, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_182, t, ite_230);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_62 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_73 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_228 = nm->mkNode(ITE, equal_73, t, const_rational_7);
  Node ite_227 = nm->mkNode(ITE, equal_179, const_rational_7, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_180, t, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_182, plus_53, ite_226);
  Node equal_55 = nm->mkNode(EQUAL, t, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_45 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_43 = nm->mkNode(EQUAL, t, const_rational_9);
  Node equal_54 = nm->mkNode(EQUAL, s, const_rational_8);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_177 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_67 = nm->mkNode(EQUAL, s, const_rational_6);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node ite_224 = nm->mkNode(ITE, equal_67, plus_53, const_rational_15);
  Node ite_223 = nm->mkNode(ITE, equal_177, const_rational_13, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_73, plus_53, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_179, const_rational_11, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_54, t, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_180, plus_53, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_182, t, ite_219);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_34 = nm->mkNode(EQUAL, t, const_rational_10);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_61 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_217 = nm->mkNode(ITE, equal_54, t, const_rational_11);
  Node ite_216 = nm->mkNode(ITE, equal_61, const_rational_15, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_67, const_rational_14, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_177, plus_53, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_73, plus_53, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_179, const_rational_11, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_180, t, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_182, plus_53, ite_211);
  Node equal_27 = nm->mkNode(EQUAL, t, const_rational_11);
  Node mult_176 = nm->mkNode(MULT, const_rational_3, s);
  Node ite_209 = nm->mkNode(ITE, equal_61, const_rational_15, t);
  Node ite_208 = nm->mkNode(ITE, equal_67, const_rational_15, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_177, mult_176, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_73, plus_53, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_179, t, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_180, t, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_182, t, ite_204);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_20 = nm->mkNode(EQUAL, t, const_rational_12);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_9);
  Node equal_42 = nm->mkNode(EQUAL, s, const_rational_10);
  Node ite_60 = nm->mkNode(ITE, equal_42, const_rational_14, const_rational_15);
  Node ite_202 = nm->mkNode(ITE, equal_52, const_rational_13, ite_60);
  Node ite_201 = nm->mkNode(ITE, equal_54, t, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_61, const_rational_15, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_67, const_rational_14, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_177, const_rational_13, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_73, t, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_179, plus_53, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_180, plus_53, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_182, plus_53, ite_195);
  Node equal_18 = nm->mkNode(EQUAL, t, const_rational_13);
  Node mult_178 = nm->mkNode(MULT, const_rational_5, s);
  Node equal_33 = nm->mkNode(EQUAL, s, const_rational_11);
  Node ite_193 = nm->mkNode(ITE, equal_33, const_rational_15, t);
  Node ite_192 = nm->mkNode(ITE, equal_42, const_rational_15, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_52, t, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_54, t, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_61, const_rational_15, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_67, const_rational_15, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_177, t, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_73, t, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_179, mult_178, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_180, plus_53, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_182, t, ite_184);
  Node mult_181 = nm->mkNode(MULT, const_rational_15, s);
  Node equal_26 = nm->mkNode(EQUAL, s, const_rational_12);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_175 = nm->mkNode(ITE, equal_25, const_rational_15, t);
  Node ite_174 = nm->mkNode(ITE, equal_26, t, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_33, const_rational_15, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_42, t, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_52, const_rational_15, ite_172);
  Node ite_170 = nm->mkNode(ITE, equal_54, t, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_61, const_rational_15, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_67, t, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_177, mult_176, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_73, t, ite_167);
  Node ite_165 = nm->mkNode(ITE, equal_179, mult_178, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_180, t, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_182, mult_181, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_18, ite_183, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_20, ite_194, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_27, ite_203, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_34, ite_210, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_43, ite_218, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_45, plus_53, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_55, t, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_62, ite_225, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_68, ite_229, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_70, plus_53, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_74, t, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_76, plus_53, ite_152);
  Node ite_150 = nm->mkNode(ITE, geq_232, t, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_233, plus_53, ite_150);
  Node mult_99 = nm->mkNode(MULT, const_rational_2, t);
  Node geq_148 = nm->mkNode(GEQ, s, mult_99);
  Node mult_88 = nm->mkNode(MULT, const_rational_3, t);
  Node geq_147 = nm->mkNode(GEQ, s, mult_88);
  Node mult_114 = nm->mkNode(MULT, const_rational_4, t);
  Node geq_146 = nm->mkNode(GEQ, s, mult_114);
  Node mult_112 = nm->mkNode(MULT, const_rational_5, t);
  Node geq_145 = nm->mkNode(GEQ, s, mult_112);
  Node mult_144 = nm->mkNode(MULT, const_rational_6, t);
  Node geq_143 = nm->mkNode(GEQ, s, mult_144);
  Node mult_142 = nm->mkNode(MULT, const_rational_7, t);
  Node geq_141 = nm->mkNode(GEQ, s, mult_142);
  Node mult_140 = nm->mkNode(MULT, const_rational_8, t);
  Node geq_139 = nm->mkNode(GEQ, s, mult_140);
  Node mult_138 = nm->mkNode(MULT, const_rational_9, t);
  Node geq_137 = nm->mkNode(GEQ, s, mult_138);
  Node mult_136 = nm->mkNode(MULT, const_rational_10, t);
  Node geq_135 = nm->mkNode(GEQ, s, mult_136);
  Node mult_134 = nm->mkNode(MULT, const_rational_11, t);
  Node geq_133 = nm->mkNode(GEQ, s, mult_134);
  Node mult_132 = nm->mkNode(MULT, const_rational_12, t);
  Node geq_131 = nm->mkNode(GEQ, s, mult_132);
  Node mult_130 = nm->mkNode(MULT, const_rational_13, t);
  Node geq_129 = nm->mkNode(GEQ, s, mult_130);
  Node mult_128 = nm->mkNode(MULT, const_rational_14, t);
  Node geq_127 = nm->mkNode(GEQ, s, mult_128);
  Node mult_126 = nm->mkNode(MULT, const_rational_15, t);
  Node geq_125 = nm->mkNode(GEQ, s, mult_126);
  Node ite_124 = nm->mkNode(ITE, geq_125, s, plus_53);
  Node ite_123 = nm->mkNode(ITE, geq_127, ite_124, s);
  Node ite_122 = nm->mkNode(ITE, geq_129, ite_123, plus_53);
  Node ite_121 = nm->mkNode(ITE, geq_131, ite_122, s);
  Node ite_120 = nm->mkNode(ITE, geq_133, ite_121, plus_53);
  Node ite_119 = nm->mkNode(ITE, geq_135, ite_120, s);
  Node ite_118 = nm->mkNode(ITE, geq_137, ite_119, plus_53);
  Node ite_117 = nm->mkNode(ITE, geq_139, ite_118, s);
  Node ite_116 = nm->mkNode(ITE, geq_141, ite_117, plus_53);
  Node ite_115 = nm->mkNode(ITE, geq_143, ite_116, s);
  Node equal_113 = nm->mkNode(EQUAL, s, mult_114);
  Node ite_111 = nm->mkNode(ITE, equal_76, plus_53, mult_112);
  Node ite_110 = nm->mkNode(ITE, equal_113, plus_53, ite_111);
  Node ite_109 = nm->mkNode(ITE, geq_145, ite_115, ite_110);
  Node equal_108 = nm->mkNode(EQUAL, s, mult_88);
  Node equal_96 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_107 = nm->mkNode(ITE, equal_74, const_rational_11, s);
  Node ite_106 = nm->mkNode(ITE, equal_76, s, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_96, s, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_42, const_rational_11, s);
  Node ite_103 = nm->mkNode(ITE, equal_74, ite_104, s);
  Node ite_102 = nm->mkNode(ITE, equal_76, s, ite_103);
  Node ite_101 = nm->mkNode(ITE, equal_108, ite_105, ite_102);
  Node ite_100 = nm->mkNode(ITE, geq_146, ite_109, ite_101);
  Node equal_98 = nm->mkNode(EQUAL, s, mult_99);
  Node equal_41 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_95 = nm->mkNode(ITE, equal_68, plus_53, const_rational_14);
  Node ite_94 = nm->mkNode(ITE, equal_41, const_rational_15, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_70, plus_53, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_74, const_rational_7, ite_93);
  Node ite_91 = nm->mkNode(ITE, equal_76, plus_53, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_96, plus_53, ite_91);
  Node ite_89 = nm->mkNode(ITE, equal_54, plus_53, s);
  Node ite_87 = nm->mkNode(ITE, equal_25, s, mult_88);
  Node ite_86 = nm->mkNode(ITE, equal_26, const_rational_13, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_33, mult_88, ite_86);
  Node ite_31 = nm->mkNode(ITE, equal_25, const_rational_15, s);
  Node ite_84 = nm->mkNode(ITE, equal_62, ite_31, s);
  Node ite_83 = nm->mkNode(ITE, equal_68, ite_85, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_70, plus_53, ite_83);
  Node ite_81 = nm->mkNode(ITE, equal_74, ite_89, ite_82);
  Node ite_80 = nm->mkNode(ITE, equal_76, plus_53, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_98, ite_90, ite_80);
  Node ite_78 = nm->mkNode(ITE, geq_147, ite_100, ite_79);
  Node ite_72 = nm->mkNode(ITE, equal_73, plus_53, const_rational_7);
  Node ite_66 = nm->mkNode(ITE, equal_54, plus_53, const_rational_13);
  Node ite_65 = nm->mkNode(ITE, equal_61, s, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_67, const_rational_7, ite_65);
  Node ite_59 = nm->mkNode(ITE, equal_52, plus_53, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_54, plus_53, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_61, s, ite_58);
  Node ite_51 = nm->mkNode(ITE, equal_26, const_rational_15, const_rational_15);
  Node ite_50 = nm->mkNode(ITE, equal_33, const_rational_15, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_42, const_rational_15, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_52, const_rational_15, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_54, plus_53, ite_48);
  Node equal_17 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_40 = nm->mkNode(ITE, equal_41, const_rational_15, s);
  Node ite_39 = nm->mkNode(ITE, equal_26, const_rational_13, ite_40);
  Node ite_38 = nm->mkNode(ITE, equal_33, s, ite_39);
  Node ite_37 = nm->mkNode(ITE, equal_17, s, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_42, const_rational_11, ite_37);
  Node ite_30 = nm->mkNode(ITE, equal_26, const_rational_14, ite_31);
  Node ite_29 = nm->mkNode(ITE, equal_33, s, ite_30);
  Node ite_24 = nm->mkNode(ITE, equal_25, const_rational_15, const_rational_15);
  Node ite_23 = nm->mkNode(ITE, equal_26, const_rational_15, ite_24);
  Node ite_22 = nm->mkNode(ITE, equal_17, s, ite_23);
  Node ite_15 = nm->mkNode(ITE, equal_17, s, const_rational_15);
  Node ite_14 = nm->mkNode(ITE, equal_18, ite_15, s);
  Node ite_13 = nm->mkNode(ITE, equal_20, s, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_27, ite_22, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_34, ite_29, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_43, ite_36, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_45, s, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_55, ite_47, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_62, ite_57, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_68, ite_64, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_70, s, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_74, ite_72, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_76, s, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_148, ite_78, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_235, ite_149, ite_2);
  return ite_1;
}

// (define-fun int_bvor_4_nia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (ite (>= t s) t (+ s t)) (ite (= t 2) (+ s t) (ite (= t 3) t (ite
// (= t 4) (+ s t) (ite (= t 5) t (ite (= t 6) (+ s t) (ite (= t 7) t (ite (= t
// 8) (+ s t) (ite (= t 9) t (ite (= t 10) (+ s t) (ite (= t 11) t (ite (= t 12)
// (+ s t) (ite (= t 13) t (* s 15)))))))))))))) (ite (>= s (* s t)) (ite (= s
// (* s t)) (ite (= s (+ t t)) (+ s t) (ite (= s 3) s (ite (= s 4) (+ s t) (ite
// (= s 5) s (ite (= s 15) s (ite (= s 6) (+ s t) (ite (= s 7) s (ite (= s 8) (+
// s t) (ite (= s 9) s (ite (= s 10) (+ s t) (ite (= s 11) s (ite (= s 12) (+ s
// t) (ite (= s 14) (+ s t) s))))))))))))) (+ s t)) (ite (>= t s) (ite (>= s t)
// t (ite (= t 3) t (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 2) (+ s t) (ite
// (= s 3) (+ s 4) t)) (ite (= t 6) (ite (= s 2) t (ite (= s 3) (+ s 4) (+ s
// 2))) (ite (= t 7) t (ite (= t 8) (+ s t) (ite (= t 9) (ite (= s 2) (+ s t)
// (ite (= s 3) (+ s 8) (ite (= s 4) (+ s t) (ite (= s 5) (+ s 8) (ite (= s 6)
// (+ s t) (ite (= s 7) (+ s 8) t)))))) (ite (= t 10) (ite (= s 2) t (ite (= s
// 3) (+ s 8) (ite (= s 4) (+ s t) (ite (= s 5) (+ s t) (ite (= s 6) (+ s 8)
// (ite (= s 7) (+ s 8) (+ s 2))))))) (ite (= t 11) (ite (= s 2) t (ite (= s 3)
// t (ite (= s 4) (+ s t) (ite (= s 5) (* s 3) (ite (= s 6) (+ s 9) (ite (= s 7)
// (+ s 8) t)))))) (ite (= t 12) (ite (= s 2) (+ s t) (ite (= s 3) (+ s t) (ite
// (= s 4) t (ite (= s 5) (+ s 8) (ite (= s 6) (+ s 8) (ite (= s 7) (+ s 8) (+ s
// 4))))))) (ite (= t 13) (ite (= s 2) (+ s t) (ite (= s 3) (* s 5) (ite (= s 4)
// t (ite (= s 5) t (ite (= s 12) t (ite (= s 6) (+ s 9) (ite (= s 7) (+ s 8)
// (ite (= s 8) t (ite (= s 9) t (ite (= s 10) (+ s 5) (+ s 4))))))))))) (ite (=
// s 2) t (ite (= s 3) (* s 5) (ite (= s 4) t (ite (= s 5) (* s 3) (ite (= s 6)
// t (ite (= s 7) (+ s 8) (ite (= s 8) t (ite (= s 9) (+ s 6) (ite (= s 14) t
// (ite (= s 10) t (ite (= s 11) (+ s 4) (ite (= s 12) t (+ s
// 2))))))))))))))))))))))))) (ite (>= s (* t t)) (ite (= s (* t t)) (+ s 2)
// (ite (= t 2) (ite (= s 5) (+ s t) (ite (= s 6) s (ite (= s 7) s (ite (= s 8)
// (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) s (ite (= s 11) s (ite (= s 15) s
// (ite (= s 12) (+ s t) (ite (= s 13) (+ s t) s)))))))))) (ite (= s 10) (+ s 1)
// (ite (= s 11) s (ite (= s 12) (+ s t) (ite (= s 13) (+ s 2) (ite (= s 14) (+
// s 1) s))))))) (ite (>= s (+ t t)) (ite (= s (+ t t)) (ite (= t 3) (+ s 1)
// (ite (= t 4) (+ s t) (ite (= t 5) (+ s t) (ite (= t 6) (+ s 2) (+ s 1)))))
// (ite (= t 3) (ite (= s 7) s (+ s t)) (ite (= s 15) s (ite (= t 4) (ite (= s
// 9) (+ s t) (ite (= s 10) (+ s t) (ite (= s 11) (+ s t) s))) (ite (= t 5) (ite
// (= s 11) (+ s 4) (ite (= s 12) (+ s 1) (ite (= s 13) s (+ s 1)))) (ite (= s
// 13) (+ s 2) s)))))) (ite (= t 2) s (ite (= t 3) (ite (= s 4) (+ s t) (+ s 2))
// (ite (= t 4) s (ite (= t 5) (ite (= s 6) (+ s 1) (ite (= s 7) s (ite (= s 9)
// (+ s 4) (+ s t)))) (ite (= t 6) (ite (= s 7) s (ite (= s 8) (+ s t) (ite (= s
// 9) (+ s t) (+ s 4)))) (ite (= t 7) (ite (= s 8) (+ s t) (ite (= s 9) (+ s 6)
// (ite (= s 10) (+ s 5) (ite (= s 11) (+ s 4) (ite (= s 12) (+ s 3) (+ s
// 2)))))) (ite (= t 8) s (ite (= t 9) (ite (= s 15) s (ite (= s 10) (+ s 1)
// (ite (= s 11) s (ite (= s 14) (+ s 1) (ite (= s 12) (+ s 1) s))))) (ite (= t
// 10) (ite (= s 11) s (ite (= s 12) (+ s 2) (ite (= s 13) (+ s 2) s))) (ite (=
// t 11) (ite (= s 12) (+ s 3) (ite (= s 15) s (ite (= s 14) (+ s 1) (+ s 2))))
// (ite (= t 12) s (ite (= s 15) s (+ s 1)))))))))))))))))))
Node int_bvor_4_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_228 = nm->mkNode(MULT, s, s);
  Node equal_227 = nm->mkNode(EQUAL, s, mult_228);
  Node mult_210 = nm->mkNode(MULT, s, t);
  Node geq_211 = nm->mkNode(GEQ, s, mult_210);
  Node geq_194 = nm->mkNode(GEQ, t, s);
  Node plus_66 = nm->mkNode(PLUS, s, t);
  Node ite_226 = nm->mkNode(ITE, geq_194, t, plus_66);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_84 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_83 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_80 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_79 = nm->mkNode(EQUAL, t, const_rational_5);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_74 = nm->mkNode(EQUAL, t, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_68 = nm->mkNode(EQUAL, t, const_rational_7);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_52 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_50 = nm->mkNode(EQUAL, t, const_rational_9);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_42 = nm->mkNode(EQUAL, t, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_34 = nm->mkNode(EQUAL, t, const_rational_11);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_22 = nm->mkNode(EQUAL, t, const_rational_12);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_165 = nm->mkNode(EQUAL, t, const_rational_13);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node mult_225 = nm->mkNode(MULT, s, const_rational_15);
  Node ite_224 = nm->mkNode(ITE, equal_165, t, mult_225);
  Node ite_223 = nm->mkNode(ITE, equal_22, plus_66, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_34, t, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_42, plus_66, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_50, t, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_52, plus_66, ite_220);
  Node ite_218 = nm->mkNode(ITE, equal_68, t, ite_219);
  Node ite_217 = nm->mkNode(ITE, equal_74, plus_66, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_79, t, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_80, plus_66, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_83, t, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_84, plus_66, ite_214);
  Node ite_212 = nm->mkNode(ITE, geq_211, ite_226, ite_213);
  Node equal_209 = nm->mkNode(EQUAL, s, mult_210);
  Node plus_102 = nm->mkNode(PLUS, t, t);
  Node equal_101 = nm->mkNode(EQUAL, s, plus_102);
  Node equal_152 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_82 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_121 = nm->mkNode(EQUAL, s, const_rational_5);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_15);
  Node equal_78 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_73 = nm->mkNode(EQUAL, s, const_rational_7);
  Node equal_67 = nm->mkNode(EQUAL, s, const_rational_8);
  Node equal_65 = nm->mkNode(EQUAL, s, const_rational_9);
  Node equal_49 = nm->mkNode(EQUAL, s, const_rational_10);
  Node equal_41 = nm->mkNode(EQUAL, s, const_rational_11);
  Node equal_33 = nm->mkNode(EQUAL, s, const_rational_12);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_29 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_208 = nm->mkNode(ITE, equal_29, plus_66, s);
  Node ite_207 = nm->mkNode(ITE, equal_33, plus_66, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_41, s, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_49, plus_66, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_65, s, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_67, plus_66, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_73, s, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_78, plus_66, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_20, s, ite_201);
  Node ite_199 = nm->mkNode(ITE, equal_121, s, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_82, plus_66, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_152, s, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_101, plus_66, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_209, ite_196, plus_66);
  Node geq_193 = nm->mkNode(GEQ, s, t);
  Node equal_153 = nm->mkNode(EQUAL, s, const_rational_2);
  Node plus_59 = nm->mkNode(PLUS, s, const_rational_4);
  Node ite_192 = nm->mkNode(ITE, equal_152, plus_59, t);
  Node ite_191 = nm->mkNode(ITE, equal_153, plus_66, ite_192);
  Node plus_27 = nm->mkNode(PLUS, s, const_rational_2);
  Node ite_190 = nm->mkNode(ITE, equal_152, plus_59, plus_27);
  Node ite_189 = nm->mkNode(ITE, equal_153, t, ite_190);
  Node plus_149 = nm->mkNode(PLUS, s, const_rational_8);
  Node ite_177 = nm->mkNode(ITE, equal_73, plus_149, t);
  Node ite_188 = nm->mkNode(ITE, equal_78, plus_66, ite_177);
  Node ite_187 = nm->mkNode(ITE, equal_121, plus_149, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_82, plus_66, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_152, plus_149, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_153, plus_66, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_73, plus_149, plus_27);
  Node ite_182 = nm->mkNode(ITE, equal_78, plus_149, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_121, plus_66, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_82, plus_66, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_152, plus_149, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_153, t, ite_179);
  Node mult_150 = nm->mkNode(MULT, s, const_rational_3);
  Node plus_164 = nm->mkNode(PLUS, s, const_rational_9);
  Node ite_176 = nm->mkNode(ITE, equal_78, plus_164, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_121, mult_150, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_82, plus_66, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_152, t, ite_174);
  Node ite_172 = nm->mkNode(ITE, equal_153, t, ite_173);
  Node ite_171 = nm->mkNode(ITE, equal_73, plus_149, plus_59);
  Node ite_170 = nm->mkNode(ITE, equal_78, plus_149, ite_171);
  Node ite_169 = nm->mkNode(ITE, equal_121, plus_149, ite_170);
  Node ite_168 = nm->mkNode(ITE, equal_82, t, ite_169);
  Node ite_167 = nm->mkNode(ITE, equal_152, plus_66, ite_168);
  Node ite_166 = nm->mkNode(ITE, equal_153, plus_66, ite_167);
  Node mult_151 = nm->mkNode(MULT, s, const_rational_5);
  Node plus_61 = nm->mkNode(PLUS, s, const_rational_5);
  Node ite_163 = nm->mkNode(ITE, equal_49, plus_61, plus_59);
  Node ite_162 = nm->mkNode(ITE, equal_65, t, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_67, t, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_73, plus_149, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_78, plus_164, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_33, t, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_121, t, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_82, t, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_152, mult_151, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_153, plus_66, ite_155);
  Node plus_63 = nm->mkNode(PLUS, s, const_rational_6);
  Node ite_148 = nm->mkNode(ITE, equal_33, t, plus_27);
  Node ite_147 = nm->mkNode(ITE, equal_41, plus_59, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_49, t, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_29, t, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_65, plus_63, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_67, t, ite_144);
  Node ite_142 = nm->mkNode(ITE, equal_73, plus_149, ite_143);
  Node ite_141 = nm->mkNode(ITE, equal_78, t, ite_142);
  Node ite_140 = nm->mkNode(ITE, equal_121, mult_150, ite_141);
  Node ite_139 = nm->mkNode(ITE, equal_82, t, ite_140);
  Node ite_138 = nm->mkNode(ITE, equal_152, mult_151, ite_139);
  Node ite_137 = nm->mkNode(ITE, equal_153, t, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_165, ite_154, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_22, ite_166, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_34, ite_172, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_42, ite_178, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_50, ite_184, ite_133);
  Node ite_131 = nm->mkNode(ITE, equal_52, plus_66, ite_132);
  Node ite_130 = nm->mkNode(ITE, equal_68, t, ite_131);
  Node ite_129 = nm->mkNode(ITE, equal_74, ite_189, ite_130);
  Node ite_128 = nm->mkNode(ITE, equal_79, ite_191, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_80, plus_66, ite_128);
  Node ite_126 = nm->mkNode(ITE, equal_83, t, ite_127);
  Node ite_125 = nm->mkNode(ITE, geq_193, t, ite_126);
  Node mult_123 = nm->mkNode(MULT, t, t);
  Node geq_124 = nm->mkNode(GEQ, s, mult_123);
  Node equal_122 = nm->mkNode(EQUAL, s, mult_123);
  Node equal_39 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_120 = nm->mkNode(ITE, equal_39, plus_66, s);
  Node ite_119 = nm->mkNode(ITE, equal_33, plus_66, ite_120);
  Node ite_118 = nm->mkNode(ITE, equal_20, s, ite_119);
  Node ite_117 = nm->mkNode(ITE, equal_41, s, ite_118);
  Node ite_116 = nm->mkNode(ITE, equal_49, s, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_65, plus_66, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_67, plus_66, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_73, s, ite_114);
  Node ite_112 = nm->mkNode(ITE, equal_78, s, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_121, plus_66, ite_112);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node plus_18 = nm->mkNode(PLUS, s, const_rational_1);
  Node ite_110 = nm->mkNode(ITE, equal_29, plus_18, s);
  Node ite_109 = nm->mkNode(ITE, equal_39, plus_27, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_33, plus_66, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_41, s, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_49, plus_18, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_84, ite_111, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_122, plus_27, ite_105);
  Node geq_103 = nm->mkNode(GEQ, s, plus_102);
  Node ite_100 = nm->mkNode(ITE, equal_74, plus_27, plus_18);
  Node ite_99 = nm->mkNode(ITE, equal_79, plus_66, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_80, plus_66, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_83, plus_18, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_73, s, plus_66);
  Node ite_95 = nm->mkNode(ITE, equal_41, plus_66, s);
  Node ite_94 = nm->mkNode(ITE, equal_49, plus_66, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_65, plus_66, ite_94);
  Node ite_92 = nm->mkNode(ITE, equal_39, s, plus_18);
  Node ite_91 = nm->mkNode(ITE, equal_33, plus_18, ite_92);
  Node ite_90 = nm->mkNode(ITE, equal_41, plus_59, ite_91);
  Node ite_38 = nm->mkNode(ITE, equal_39, plus_27, s);
  Node ite_89 = nm->mkNode(ITE, equal_79, ite_90, ite_38);
  Node ite_88 = nm->mkNode(ITE, equal_80, ite_93, ite_89);
  Node ite_87 = nm->mkNode(ITE, equal_20, s, ite_88);
  Node ite_86 = nm->mkNode(ITE, equal_83, ite_96, ite_87);
  Node ite_85 = nm->mkNode(ITE, equal_101, ite_97, ite_86);
  Node ite_81 = nm->mkNode(ITE, equal_82, plus_66, plus_27);
  Node ite_77 = nm->mkNode(ITE, equal_65, plus_59, plus_66);
  Node ite_76 = nm->mkNode(ITE, equal_73, s, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_78, plus_18, ite_76);
  Node ite_72 = nm->mkNode(ITE, equal_65, plus_66, plus_59);
  Node ite_71 = nm->mkNode(ITE, equal_67, plus_66, ite_72);
  Node ite_70 = nm->mkNode(ITE, equal_73, s, ite_71);
  Node plus_31 = nm->mkNode(PLUS, s, const_rational_3);
  Node ite_58 = nm->mkNode(ITE, equal_33, plus_31, plus_27);
  Node ite_57 = nm->mkNode(ITE, equal_41, plus_59, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_49, plus_61, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_65, plus_63, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_67, plus_66, ite_55);
  Node ite_48 = nm->mkNode(ITE, equal_33, plus_18, s);
  Node ite_47 = nm->mkNode(ITE, equal_29, plus_18, ite_48);
  Node ite_46 = nm->mkNode(ITE, equal_41, s, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_49, plus_18, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_20, s, ite_45);
  Node ite_37 = nm->mkNode(ITE, equal_33, plus_27, ite_38);
  Node ite_36 = nm->mkNode(ITE, equal_41, s, ite_37);
  Node ite_26 = nm->mkNode(ITE, equal_29, plus_18, plus_27);
  Node ite_25 = nm->mkNode(ITE, equal_20, s, ite_26);
  Node ite_24 = nm->mkNode(ITE, equal_33, plus_31, ite_25);
  Node ite_17 = nm->mkNode(ITE, equal_20, s, plus_18);
  Node ite_16 = nm->mkNode(ITE, equal_22, s, ite_17);
  Node ite_15 = nm->mkNode(ITE, equal_34, ite_24, ite_16);
  Node ite_14 = nm->mkNode(ITE, equal_42, ite_36, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_50, ite_44, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_52, s, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_68, ite_54, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_74, ite_70, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_79, ite_75, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_80, s, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_83, ite_81, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_84, s, ite_7);
  Node ite_5 = nm->mkNode(ITE, geq_103, ite_85, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_124, ite_104, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_194, ite_125, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_211, ite_195, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_227, ite_212, ite_2);
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
// (+ s t) (ite (>= s t) 0 (ite (= t (+ s s)) (+ s t) (ite (= s 1) (+ s s) 1))))
// (ite (>= s (+ t t)) (ite (= s (+ s t)) (+ s t) (ite (= s (+ t t)) (+ s t) (+
// t t))) 1)))
Node int_bvxor_2_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_21 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_20 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_7 = nm->mkNode(PLUS, s, t);
  Node geq_19 = nm->mkNode(GEQ, s, t);
  Node plus_15 = nm->mkNode(PLUS, s, s);
  Node equal_17 = nm->mkNode(EQUAL, t, plus_15);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_16 = nm->mkNode(EQUAL, s, const_rational_1);
  Node ite_14 = nm->mkNode(ITE, equal_16, plus_15, const_rational_1);
  Node ite_13 = nm->mkNode(ITE, equal_17, plus_7, ite_14);
  Node ite_12 = nm->mkNode(ITE, geq_19, const_rational_0, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_20, plus_7, ite_12);
  Node plus_6 = nm->mkNode(PLUS, t, t);
  Node geq_10 = nm->mkNode(GEQ, s, plus_6);
  Node equal_9 = nm->mkNode(EQUAL, s, plus_7);
  Node equal_8 = nm->mkNode(EQUAL, s, plus_6);
  Node ite_5 = nm->mkNode(ITE, equal_8, plus_7, plus_6);
  Node ite_4 = nm->mkNode(ITE, equal_9, plus_7, ite_5);
  Node ite_2 = nm->mkNode(ITE, geq_10, ite_4, const_rational_1);
  Node ite_1 = nm->mkNode(ITE, geq_21, ite_11, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_2_nia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (ite (>= t s) (ite (= s 0) (+ s t) 0) (+ s t)) (ite (= t 2) (+ s
// t) (+ s s))) (ite (>= s (* s t)) (ite (= s (* s t)) (ite (= s (+ t t)) (+ s
// t) (+ t t)) (+ s t)) (ite (>= t s) (ite (>= s t) 0 (ite (>= s t) 0 1)) 1))))
Node int_bvxor_2_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_27 = nm->mkNode(MULT, s, s);
  Node equal_26 = nm->mkNode(EQUAL, s, mult_27);
  Node mult_16 = nm->mkNode(MULT, s, t);
  Node geq_17 = nm->mkNode(GEQ, s, mult_16);
  Node geq_9 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_11 = nm->mkNode(PLUS, s, t);
  Node ite_24 = nm->mkNode(ITE, equal_25, plus_11, const_rational_0);
  Node ite_23 = nm->mkNode(ITE, geq_9, ite_24, plus_11);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_21 = nm->mkNode(EQUAL, t, const_rational_2);
  Node plus_20 = nm->mkNode(PLUS, s, s);
  Node ite_19 = nm->mkNode(ITE, equal_21, plus_11, plus_20);
  Node ite_18 = nm->mkNode(ITE, geq_17, ite_23, ite_19);
  Node equal_15 = nm->mkNode(EQUAL, s, mult_16);
  Node plus_13 = nm->mkNode(PLUS, t, t);
  Node equal_14 = nm->mkNode(EQUAL, s, plus_13);
  Node ite_12 = nm->mkNode(ITE, equal_14, plus_11, plus_13);
  Node ite_10 = nm->mkNode(ITE, equal_15, ite_12, plus_11);
  Node geq_8 = nm->mkNode(GEQ, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node ite_6 = nm->mkNode(ITE, geq_8, const_rational_0, const_rational_1);
  Node ite_5 = nm->mkNode(ITE, geq_8, const_rational_0, ite_6);
  Node ite_3 = nm->mkNode(ITE, geq_9, ite_5, const_rational_1);
  Node ite_2 = nm->mkNode(ITE, geq_17, ite_10, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_26, ite_18, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_3_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// (+ s t) (ite (>= s t) 0 (ite (= t 2) (+ s t) (ite (= t 3) (ite (= s 1) (* 2
// s) 1) (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 1) (* 4 s) (ite (= s 2) (+
// s t) (ite (= s 3) (* 2 s) 1))) (ite (= s 6) 1 (ite (= t 6) (ite (= s 1) (+ s
// t) (ite (= s 2) (* 2 s) (ite (= s 3) 5 (ite (= s 4) 2 3)))) (ite (= s 1) (* 6
// s) (ite (= s 2) 5 (ite (= s 3) 4 (ite (= s 4) 3 2)))))))))))) (ite (>= s (* 2
// t)) (ite (>= s (* 3 t)) (ite (>= s (* 4 t)) (ite (>= s (* 5 t)) (ite (>= s (*
// 6 t)) (ite (>= s (* 7 t)) (ite (= s (+ s t)) (+ s t) (* 6 t)) (+ s t)) (* 4
// t)) (+ s t)) (ite (= s (* 3 t)) (* 2 t) 5)) (ite (= s (* 2 t)) (ite (= t 1)
// (+ s t) (ite (= s 6) 5 (+ s t))) (ite (= t 2) (+ s t) 4))) (ite (= t 2) 1
// (ite (= t 3) (ite (= s 4) (+ s t) (* 2 t)) (ite (= t 4) (ite (= s 5) 1 (ite
// (= s 6) 2 3)) (ite (= t 5) (ite (= s 7) 2 3) 1)))))))
Node int_bvxor_3_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_84 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_83 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_24 = nm->mkNode(PLUS, s, t);
  Node geq_82 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_27 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_26 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_69 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_74 = nm->mkNode(MULT, const_rational_2, s);
  Node ite_80 = nm->mkNode(ITE, equal_69, mult_74, const_rational_1);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_20 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_13 = nm->mkNode(EQUAL, t, const_rational_5);
  Node mult_79 = nm->mkNode(MULT, const_rational_4, s);
  Node equal_67 = nm->mkNode(EQUAL, s, const_rational_2);
  Node equal_66 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_78 = nm->mkNode(ITE, equal_66, mult_74, const_rational_1);
  Node ite_77 = nm->mkNode(ITE, equal_67, plus_24, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_69, mult_79, ite_77);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_17 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_75 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_73 = nm->mkNode(ITE, equal_25, const_rational_2, const_rational_3);
  Node ite_72 = nm->mkNode(ITE, equal_66, const_rational_5, ite_73);
  Node ite_71 = nm->mkNode(ITE, equal_67, mult_74, ite_72);
  Node ite_70 = nm->mkNode(ITE, equal_69, plus_24, ite_71);
  Node mult_68 = nm->mkNode(MULT, const_rational_6, s);
  Node ite_65 = nm->mkNode(ITE, equal_25, const_rational_3, const_rational_2);
  Node ite_64 = nm->mkNode(ITE, equal_66, const_rational_4, ite_65);
  Node ite_63 = nm->mkNode(ITE, equal_67, const_rational_5, ite_64);
  Node ite_62 = nm->mkNode(ITE, equal_69, mult_68, ite_63);
  Node ite_61 = nm->mkNode(ITE, equal_75, ite_70, ite_62);
  Node ite_60 = nm->mkNode(ITE, equal_17, const_rational_1, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_13, ite_76, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_20, plus_24, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_26, ite_80, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_27, plus_24, ite_57);
  Node ite_55 = nm->mkNode(ITE, geq_82, const_rational_0, ite_56);
  Node ite_54 = nm->mkNode(ITE, equal_83, plus_24, ite_55);
  Node mult_23 = nm->mkNode(MULT, const_rational_2, t);
  Node geq_53 = nm->mkNode(GEQ, s, mult_23);
  Node mult_38 = nm->mkNode(MULT, const_rational_3, t);
  Node geq_52 = nm->mkNode(GEQ, s, mult_38);
  Node mult_41 = nm->mkNode(MULT, const_rational_4, t);
  Node geq_51 = nm->mkNode(GEQ, s, mult_41);
  Node mult_50 = nm->mkNode(MULT, const_rational_5, t);
  Node geq_49 = nm->mkNode(GEQ, s, mult_50);
  Node mult_44 = nm->mkNode(MULT, const_rational_6, t);
  Node geq_48 = nm->mkNode(GEQ, s, mult_44);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node mult_47 = nm->mkNode(MULT, const_rational_7, t);
  Node geq_46 = nm->mkNode(GEQ, s, mult_47);
  Node equal_45 = nm->mkNode(EQUAL, s, plus_24);
  Node ite_43 = nm->mkNode(ITE, equal_45, plus_24, mult_44);
  Node ite_42 = nm->mkNode(ITE, geq_46, ite_43, plus_24);
  Node ite_40 = nm->mkNode(ITE, geq_48, ite_42, mult_41);
  Node ite_39 = nm->mkNode(ITE, geq_49, ite_40, plus_24);
  Node equal_37 = nm->mkNode(EQUAL, s, mult_38);
  Node ite_36 = nm->mkNode(ITE, equal_37, mult_23, const_rational_5);
  Node ite_35 = nm->mkNode(ITE, geq_51, ite_39, ite_36);
  Node equal_34 = nm->mkNode(EQUAL, s, mult_23);
  Node equal_33 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_32 = nm->mkNode(ITE, equal_17, const_rational_5, plus_24);
  Node ite_31 = nm->mkNode(ITE, equal_33, plus_24, ite_32);
  Node ite_30 = nm->mkNode(ITE, equal_27, plus_24, const_rational_4);
  Node ite_29 = nm->mkNode(ITE, equal_34, ite_31, ite_30);
  Node ite_28 = nm->mkNode(ITE, geq_52, ite_35, ite_29);
  Node ite_22 = nm->mkNode(ITE, equal_25, plus_24, mult_23);
  Node equal_19 = nm->mkNode(EQUAL, s, const_rational_5);
  Node ite_16 = nm->mkNode(ITE, equal_17, const_rational_2, const_rational_3);
  Node ite_15 = nm->mkNode(ITE, equal_19, const_rational_1, ite_16);
  Node equal_11 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_8 = nm->mkNode(ITE, equal_11, const_rational_2, const_rational_3);
  Node ite_6 = nm->mkNode(ITE, equal_13, ite_8, const_rational_1);
  Node ite_5 = nm->mkNode(ITE, equal_20, ite_15, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_26, ite_22, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_27, const_rational_1, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_53, ite_28, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_84, ite_54, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_3_nia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (ite (>= t s) (ite (= s 0) (+ s t) 0) (+ s t)) (ite (= t 2) (+ s
// t) (ite (= t 6) (+ s t) (ite (= t 3) (+ s (* s s)) (ite (= t 4) (+ s t) (ite
// (= t 5) (* s 4) (* s 6))))))) (ite (>= s (* s t)) (ite (= s (* s t)) (ite (=
// s (+ t t)) (+ s t) (ite (= s 3) (+ t t) (ite (= s 4) (+ s t) (ite (= s 5) 4
// (ite (= s 7) 6 (+ s t)))))) (+ s t)) (ite (>= t s) (ite (>= s t) 0 (ite (= t
// 3) 1 (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 2) (+ s t) (ite (= s 3) (+ s
// s) 1)) (ite (= t 6) (ite (= s 2) (* s s) (ite (= s 3) (+ s 2) (ite (= s 4) 2
// 3))) (ite (= s 2) (+ s 3) (ite (= s 3) (+ s 1) (ite (= s 4) 3 (ite (= s 5) 2
// 1))))))))) (ite (= s 7) (ite (>= s (* t t)) 5 (ite (= t 6) 1 (ite (>= s (+ t
// t)) 4 (ite (= t 4) 3 2)))) (ite (>= s (* t t)) (ite (= s (* t t)) (+ s t)
// (ite (= s 5) (+ s t) (* t t))) (ite (>= s (+ t t)) 5 (ite (= t 2) 1 (ite (= t
// 3) (ite (= s 4) (+ s t) (+ t t)) (ite (= t 4) (ite (= s 6) 2 1) 3))))))))))
Node int_bvxor_3_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_56 = nm->mkNode(MULT, s, s);
  Node equal_86 = nm->mkNode(EQUAL, s, mult_56);
  Node mult_72 = nm->mkNode(MULT, s, t);
  Node geq_73 = nm->mkNode(GEQ, s, mult_72);
  Node geq_63 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_85 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_20 = nm->mkNode(PLUS, s, t);
  Node ite_84 = nm->mkNode(ITE, equal_85, plus_20, const_rational_0);
  Node ite_83 = nm->mkNode(ITE, geq_63, ite_84, plus_20);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_23 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_36 = nm->mkNode(EQUAL, t, const_rational_6);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_22 = nm->mkNode(EQUAL, t, const_rational_3);
  Node plus_82 = nm->mkNode(PLUS, s, mult_56);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_16 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_60 = nm->mkNode(EQUAL, t, const_rational_5);
  Node mult_81 = nm->mkNode(MULT, s, const_rational_4);
  Node mult_80 = nm->mkNode(MULT, s, const_rational_6);
  Node ite_79 = nm->mkNode(ITE, equal_60, mult_81, mult_80);
  Node ite_78 = nm->mkNode(ITE, equal_16, plus_20, ite_79);
  Node ite_77 = nm->mkNode(ITE, equal_22, plus_82, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_36, plus_20, ite_77);
  Node ite_75 = nm->mkNode(ITE, equal_23, plus_20, ite_76);
  Node ite_74 = nm->mkNode(ITE, geq_73, ite_83, ite_75);
  Node equal_71 = nm->mkNode(EQUAL, s, mult_72);
  Node plus_19 = nm->mkNode(PLUS, t, t);
  Node equal_70 = nm->mkNode(EQUAL, s, plus_19);
  Node equal_49 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_21 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_29 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_37 = nm->mkNode(EQUAL, s, const_rational_7);
  Node ite_69 = nm->mkNode(ITE, equal_37, const_rational_6, plus_20);
  Node ite_68 = nm->mkNode(ITE, equal_29, const_rational_4, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_21, plus_20, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_49, plus_19, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_70, plus_20, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_71, ite_65, plus_20);
  Node geq_62 = nm->mkNode(GEQ, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_51 = nm->mkNode(EQUAL, s, const_rational_2);
  Node plus_59 = nm->mkNode(PLUS, s, s);
  Node ite_58 = nm->mkNode(ITE, equal_49, plus_59, const_rational_1);
  Node ite_57 = nm->mkNode(ITE, equal_51, plus_20, ite_58);
  Node plus_55 = nm->mkNode(PLUS, s, const_rational_2);
  Node ite_54 = nm->mkNode(ITE, equal_21, const_rational_2, const_rational_3);
  Node ite_53 = nm->mkNode(ITE, equal_49, plus_55, ite_54);
  Node ite_52 = nm->mkNode(ITE, equal_51, mult_56, ite_53);
  Node plus_50 = nm->mkNode(PLUS, s, const_rational_3);
  Node plus_48 = nm->mkNode(PLUS, s, const_rational_1);
  Node ite_47 = nm->mkNode(ITE, equal_29, const_rational_2, const_rational_1);
  Node ite_46 = nm->mkNode(ITE, equal_21, const_rational_3, ite_47);
  Node ite_45 = nm->mkNode(ITE, equal_49, plus_48, ite_46);
  Node ite_44 = nm->mkNode(ITE, equal_51, plus_50, ite_45);
  Node ite_43 = nm->mkNode(ITE, equal_36, ite_52, ite_44);
  Node ite_42 = nm->mkNode(ITE, equal_60, ite_57, ite_43);
  Node ite_41 = nm->mkNode(ITE, equal_16, plus_20, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_22, const_rational_1, ite_41);
  Node ite_39 = nm->mkNode(ITE, geq_62, const_rational_0, ite_40);
  Node mult_28 = nm->mkNode(MULT, t, t);
  Node geq_31 = nm->mkNode(GEQ, s, mult_28);
  Node geq_25 = nm->mkNode(GEQ, s, plus_19);
  Node ite_35 = nm->mkNode(ITE, equal_16, const_rational_3, const_rational_2);
  Node ite_34 = nm->mkNode(ITE, geq_25, const_rational_4, ite_35);
  Node ite_33 = nm->mkNode(ITE, equal_36, const_rational_1, ite_34);
  Node ite_32 = nm->mkNode(ITE, geq_31, const_rational_5, ite_33);
  Node equal_30 = nm->mkNode(EQUAL, s, mult_28);
  Node ite_27 = nm->mkNode(ITE, equal_29, plus_20, mult_28);
  Node ite_26 = nm->mkNode(ITE, equal_30, plus_20, ite_27);
  Node ite_18 = nm->mkNode(ITE, equal_21, plus_20, plus_19);
  Node equal_14 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_11 = nm->mkNode(ITE, equal_14, const_rational_2, const_rational_1);
  Node ite_9 = nm->mkNode(ITE, equal_16, ite_11, const_rational_3);
  Node ite_8 = nm->mkNode(ITE, equal_22, ite_18, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_23, const_rational_1, ite_8);
  Node ite_6 = nm->mkNode(ITE, geq_25, const_rational_5, ite_7);
  Node ite_5 = nm->mkNode(ITE, geq_31, ite_26, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_37, ite_32, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_63, ite_39, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_73, ite_64, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_86, ite_74, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_4_lia ((s Int) (t Int)) Int (ite (>= t s) (ite (= s 0)
// t (ite (>= s t) 0 (ite (= t 2) (+ s t) (ite (= t 3) (ite (= s 1) (* 2 s) 1)
// (ite (= t 4) (+ s t) (ite (= t 5) (ite (= s 1) (* 4 s) (ite (= s 2) (+ s t)
// (ite (= s 3) (* 2 s) 1))) (ite (= t 6) (ite (= s 1) (+ s t) (ite (= s 2) (* 2
// s) (ite (= s 3) 5 (ite (= s 4) 2 3)))) (ite (= t 7) (ite (= s 1) (* 6 s) (ite
// (= s 2) 5 (ite (= s 3) 4 (ite (= s 6) 1 (ite (= s 4) 3 2))))) (ite (= t 8) (+
// s t) (ite (= t 9) (ite (= s 1) (* 8 s) (ite (= s 2) (+ s t) (ite (= s 3) 10
// (ite (= s 4) (+ s t) (ite (= s 8) 1 (ite (= s 5) 12 (ite (= s 6) (+ s t) (* 2
// s)))))))) (ite (= t 10) (ite (= s 1) (+ s t) (ite (= s 2) (* 4 s) (ite (= s
// 3) (* 3 s) (ite (= s 4) (+ s t) (ite (= s 5) (+ s t) (ite (= s 6) (* 2 s)
// (ite (= s 7) 13 (ite (= s 8) 2 3)))))))) (ite (= t 11) (ite (= s 1) (* 10 s)
// (ite (= s 2) 9 (ite (= s 3) 8 (ite (= s 4) (+ s t) (ite (= s 5) 14 (ite (= s
// 6) 13 (ite (= s 7) 12 (ite (= s 8) 3 (ite (= s 9) 2 1))))))))) (ite (= t 12)
// (ite (= s 1) (+ s t) (ite (= s 2) (+ s t) (ite (= s 3) (+ s t) (ite (= s 4)
// (* 2 s) (ite (= s 5) 9 (ite (= s 6) 10 (ite (= s 7) 11 (ite (= s 11) 7 (ite
// (= s 8) 4 (ite (= s 9) 5 6)))))))))) (ite (= t 13) (ite (= s 1) (* 12 s) (ite
// (= s 2) (+ s t) (ite (= s 3) 14 (ite (= s 4) 9 (ite (= s 5) 8 (ite (= s 6) 11
// (ite (= s 7) 10 (ite (= s 8) 5 (ite (= s 9) 4 (ite (= s 10) 7 (ite (= s 11) 6
// 1))))))))))) (ite (= t 14) (ite (= s 1) (+ s t) (ite (= s 2) (* 6 s) (ite (=
// s 3) 13 (ite (= s 4) 10 (ite (= s 5) 11 (ite (= s 6) 8 (ite (= s 7) 9 (ite (=
// s 8) 6 (ite (= s 9) 7 (ite (= s 10) 4 (ite (= s 11) 5 (ite (= s 13) 3
// 2)))))))))))) (ite (= s 1) (* 14 s) (ite (= s 2) 13 (ite (= s 3) (* 4 s) (ite
// (= s 4) 11 (ite (= s 5) (* 2 s) (ite (= s 6) 9 (ite (= s 7) 8 (ite (= s 8) 7
// (ite (= s 9) 6 (ite (= s 10) 5 (ite (= s 14) 1 (ite (= s 11) 4 (ite (= s 12)
// 3 2)))))))))))))))))))))))))))) (ite (>= s (* 2 t)) (ite (>= s (* 3 t)) (ite
// (>= s (* 4 t)) (ite (>= s (* 5 t)) (ite (>= s (* 6 t)) (ite (>= s (* 7 t))
// (ite (>= s (* 8 t)) (ite (>= s (* 9 t)) (ite (>= s (* 10 t)) (ite (>= s (* 11
// t)) (ite (>= s (* 12 t)) (ite (>= s (* 13 t)) (ite (>= s (* 14 t)) (ite (>= s
// (* 15 t)) (ite (= s (+ s t)) (+ s t) (* 14 t)) (+ s t)) (* 12 t)) (+ s t)) (*
// 10 t)) (+ s t)) (* 8 t)) (+ s t)) (ite (= s (* 7 t)) (* 6 t) 13)) (+ s t))
// (ite (= s (* 5 t)) (* 4 t) 9)) (ite (= s (* 4 t)) (+ s t) (ite (= t 2) (+ s
// t) (ite (= s 14) 13 14)))) (ite (= s (* 3 t)) (ite (= s 15) (* 2 t) (ite (= t
// 1) (* 2 t) (ite (= t 2) (* 2 t) (ite (= t 3) 10 (* 2 t))))) (ite (= t 2) 5
// (ite (= t 3) (ite (= s 10) (* 3 t) 8) (ite (= s 13) 9 (ite (= s 14) 10
// 11)))))) (ite (= s (* 2 t)) (ite (>= s 8) (ite (= t 4) (+ s t) (ite (= t 5)
// (+ s t) (ite (= t 6) 10 9))) (ite (= s 6) 5 (+ s t))) (ite (= t 2) (+ s t)
// (ite (= t 3) (ite (= s 7) 4 (+ s t)) (ite (= t 4) (+ s t) (ite (= t 5) (ite
// (= s 11) 14 (ite (= s 12) 9 (ite (= s 13) 8 11))) (ite (= t 6) (ite (= s 13)
// 11 (ite (= s 14) 8 9)) 8))))))) (ite (= t 2) 1 (ite (= t 3) (ite (= s 4) (+ s
// t) (* 2 t)) (ite (= t 4) (ite (= s 5) 1 (ite (= s 6) 2 3)) (ite (= t 5) (ite
// (= s 6) 3 (ite (= s 7) 2 (ite (= s 8) (+ s t) 12))) (ite (= t 6) (ite (= s 7)
// 1 (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (= s 10) (* 2 t) 13)))) (ite
// (= t 7) (ite (= s 8) (+ s t) (ite (= s 9) (* 2 t) (ite (= s 10) 13 (ite (= s
// 11) 12 (ite (= s 13) 10 11))))) (ite (= t 8) (ite (= s 9) 1 (ite (= s 10) 2
// (ite (= s 11) 3 (ite (= s 12) 4 (ite (= s 13) 5 (ite (= s 14) 6 7)))))) (ite
// (= t 9) (ite (= s 10) 3 (ite (= s 15) 6 (ite (= s 11) 2 (ite (= s 12) 5 (ite
// (= s 13) 4 7))))) (ite (= t 10) (ite (= s 15) 5 (ite (= s 11) 1 (ite (= s 12)
// 6 (ite (= s 13) 7 4)))) (ite (= t 11) (ite (= s 12) 7 (ite (= s 15) 4 (ite (=
// s 13) 6 5))) (ite (= t 12) (ite (= s 13) 1 (ite (= s 14) 2 3)) (ite (= t 13)
// (ite (= s 14) 3 2) 1)))))))))))))))
Node int_bvxor_4_lia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node geq_286 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_285 = nm->mkNode(EQUAL, s, const_rational_0);
  Node geq_284 = nm->mkNode(GEQ, s, t);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_91 = nm->mkNode(EQUAL, t, const_rational_2);
  Node plus_70 = nm->mkNode(PLUS, s, t);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_90 = nm->mkNode(EQUAL, t, const_rational_3);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_206 = nm->mkNode(EQUAL, s, const_rational_1);
  Node mult_201 = nm->mkNode(MULT, const_rational_2, s);
  Node ite_282 = nm->mkNode(ITE, equal_206, mult_201, const_rational_1);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_87 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_83 = nm->mkNode(EQUAL, t, const_rational_5);
  Node mult_202 = nm->mkNode(MULT, const_rational_4, s);
  Node equal_204 = nm->mkNode(EQUAL, s, const_rational_2);
  Node equal_203 = nm->mkNode(EQUAL, s, const_rational_3);
  Node ite_281 = nm->mkNode(ITE, equal_203, mult_201, const_rational_1);
  Node ite_280 = nm->mkNode(ITE, equal_204, plus_70, ite_281);
  Node ite_279 = nm->mkNode(ITE, equal_206, mult_202, ite_280);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_78 = nm->mkNode(EQUAL, t, const_rational_6);
  Node equal_89 = nm->mkNode(EQUAL, s, const_rational_4);
  Node ite_278 = nm->mkNode(ITE, equal_89, const_rational_2, const_rational_3);
  Node ite_277 = nm->mkNode(ITE, equal_203, const_rational_5, ite_278);
  Node ite_276 = nm->mkNode(ITE, equal_204, mult_201, ite_277);
  Node ite_275 = nm->mkNode(ITE, equal_206, plus_70, ite_276);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_72 = nm->mkNode(EQUAL, t, const_rational_7);
  Node mult_219 = nm->mkNode(MULT, const_rational_6, s);
  Node equal_82 = nm->mkNode(EQUAL, s, const_rational_6);
  Node ite_274 = nm->mkNode(ITE, equal_89, const_rational_3, const_rational_2);
  Node ite_273 = nm->mkNode(ITE, equal_82, const_rational_1, ite_274);
  Node ite_272 = nm->mkNode(ITE, equal_203, const_rational_4, ite_273);
  Node ite_271 = nm->mkNode(ITE, equal_204, const_rational_5, ite_272);
  Node ite_270 = nm->mkNode(ITE, equal_206, mult_219, ite_271);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_62 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_53 = nm->mkNode(EQUAL, t, const_rational_9);
  Node mult_269 = nm->mkNode(MULT, const_rational_8, s);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_71 = nm->mkNode(EQUAL, s, const_rational_8);
  Node equal_86 = nm->mkNode(EQUAL, s, const_rational_5);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node ite_268 = nm->mkNode(ITE, equal_82, plus_70, mult_201);
  Node ite_267 = nm->mkNode(ITE, equal_86, const_rational_12, ite_268);
  Node ite_266 = nm->mkNode(ITE, equal_71, const_rational_1, ite_267);
  Node ite_265 = nm->mkNode(ITE, equal_89, plus_70, ite_266);
  Node ite_264 = nm->mkNode(ITE, equal_203, const_rational_10, ite_265);
  Node ite_263 = nm->mkNode(ITE, equal_204, plus_70, ite_264);
  Node ite_262 = nm->mkNode(ITE, equal_206, mult_269, ite_263);
  Node equal_45 = nm->mkNode(EQUAL, t, const_rational_10);
  Node mult_261 = nm->mkNode(MULT, const_rational_3, s);
  Node equal_77 = nm->mkNode(EQUAL, s, const_rational_7);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node ite_260 = nm->mkNode(ITE, equal_71, const_rational_2, const_rational_3);
  Node ite_259 = nm->mkNode(ITE, equal_77, const_rational_13, ite_260);
  Node ite_258 = nm->mkNode(ITE, equal_82, mult_201, ite_259);
  Node ite_257 = nm->mkNode(ITE, equal_86, plus_70, ite_258);
  Node ite_256 = nm->mkNode(ITE, equal_89, plus_70, ite_257);
  Node ite_255 = nm->mkNode(ITE, equal_203, mult_261, ite_256);
  Node ite_254 = nm->mkNode(ITE, equal_204, mult_202, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_206, plus_70, ite_254);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_38 = nm->mkNode(EQUAL, t, const_rational_11);
  Node mult_252 = nm->mkNode(MULT, const_rational_10, s);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_61 = nm->mkNode(EQUAL, s, const_rational_9);
  Node ite_251 = nm->mkNode(ITE, equal_61, const_rational_2, const_rational_1);
  Node ite_250 = nm->mkNode(ITE, equal_71, const_rational_3, ite_251);
  Node ite_249 = nm->mkNode(ITE, equal_77, const_rational_12, ite_250);
  Node ite_248 = nm->mkNode(ITE, equal_82, const_rational_13, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_86, const_rational_14, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_89, plus_70, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_203, const_rational_8, ite_246);
  Node ite_244 = nm->mkNode(ITE, equal_204, const_rational_9, ite_245);
  Node ite_243 = nm->mkNode(ITE, equal_206, mult_252, ite_244);
  Node equal_26 = nm->mkNode(EQUAL, t, const_rational_12);
  Node equal_44 = nm->mkNode(EQUAL, s, const_rational_11);
  Node ite_242 = nm->mkNode(ITE, equal_61, const_rational_5, const_rational_6);
  Node ite_241 = nm->mkNode(ITE, equal_71, const_rational_4, ite_242);
  Node ite_240 = nm->mkNode(ITE, equal_44, const_rational_7, ite_241);
  Node ite_239 = nm->mkNode(ITE, equal_77, const_rational_11, ite_240);
  Node ite_238 = nm->mkNode(ITE, equal_82, const_rational_10, ite_239);
  Node ite_237 = nm->mkNode(ITE, equal_86, const_rational_9, ite_238);
  Node ite_236 = nm->mkNode(ITE, equal_89, mult_201, ite_237);
  Node ite_235 = nm->mkNode(ITE, equal_203, plus_70, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_204, plus_70, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_206, plus_70, ite_234);
  Node equal_21 = nm->mkNode(EQUAL, t, const_rational_13);
  Node mult_232 = nm->mkNode(MULT, const_rational_12, s);
  Node equal_52 = nm->mkNode(EQUAL, s, const_rational_10);
  Node ite_231 = nm->mkNode(ITE, equal_44, const_rational_6, const_rational_1);
  Node ite_230 = nm->mkNode(ITE, equal_52, const_rational_7, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_61, const_rational_4, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_71, const_rational_5, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_77, const_rational_10, ite_228);
  Node ite_226 = nm->mkNode(ITE, equal_82, const_rational_11, ite_227);
  Node ite_225 = nm->mkNode(ITE, equal_86, const_rational_8, ite_226);
  Node ite_224 = nm->mkNode(ITE, equal_89, const_rational_9, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_203, const_rational_14, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_204, plus_70, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_206, mult_232, ite_222);
  Node equal_220 = nm->mkNode(EQUAL, t, const_rational_14);
  Node equal_25 = nm->mkNode(EQUAL, s, const_rational_13);
  Node ite_218 = nm->mkNode(ITE, equal_25, const_rational_3, const_rational_2);
  Node ite_217 = nm->mkNode(ITE, equal_44, const_rational_5, ite_218);
  Node ite_216 = nm->mkNode(ITE, equal_52, const_rational_4, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_61, const_rational_7, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_71, const_rational_6, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_77, const_rational_9, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_82, const_rational_8, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_86, const_rational_11, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_89, const_rational_10, ite_211);
  Node ite_209 = nm->mkNode(ITE, equal_203, const_rational_13, ite_210);
  Node ite_208 = nm->mkNode(ITE, equal_204, mult_219, ite_209);
  Node ite_207 = nm->mkNode(ITE, equal_206, plus_70, ite_208);
  Node mult_205 = nm->mkNode(MULT, const_rational_14, s);
  Node equal_19 = nm->mkNode(EQUAL, s, const_rational_14);
  Node equal_37 = nm->mkNode(EQUAL, s, const_rational_12);
  Node ite_200 = nm->mkNode(ITE, equal_37, const_rational_3, const_rational_2);
  Node ite_199 = nm->mkNode(ITE, equal_44, const_rational_4, ite_200);
  Node ite_198 = nm->mkNode(ITE, equal_19, const_rational_1, ite_199);
  Node ite_197 = nm->mkNode(ITE, equal_52, const_rational_5, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_61, const_rational_6, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_71, const_rational_7, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_77, const_rational_8, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_82, const_rational_9, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_86, mult_201, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_89, const_rational_11, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_203, mult_202, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_204, const_rational_13, ite_190);
  Node ite_188 = nm->mkNode(ITE, equal_206, mult_205, ite_189);
  Node ite_187 = nm->mkNode(ITE, equal_220, ite_207, ite_188);
  Node ite_186 = nm->mkNode(ITE, equal_21, ite_221, ite_187);
  Node ite_185 = nm->mkNode(ITE, equal_26, ite_233, ite_186);
  Node ite_184 = nm->mkNode(ITE, equal_38, ite_243, ite_185);
  Node ite_183 = nm->mkNode(ITE, equal_45, ite_253, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_53, ite_262, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_62, plus_70, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_72, ite_270, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_78, ite_275, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_83, ite_279, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_87, plus_70, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_90, ite_282, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_91, plus_70, ite_176);
  Node ite_174 = nm->mkNode(ITE, geq_284, const_rational_0, ite_175);
  Node ite_173 = nm->mkNode(ITE, equal_285, t, ite_174);
  Node mult_69 = nm->mkNode(MULT, const_rational_2, t);
  Node geq_172 = nm->mkNode(GEQ, s, mult_69);
  Node mult_119 = nm->mkNode(MULT, const_rational_3, t);
  Node geq_171 = nm->mkNode(GEQ, s, mult_119);
  Node mult_131 = nm->mkNode(MULT, const_rational_4, t);
  Node geq_170 = nm->mkNode(GEQ, s, mult_131);
  Node mult_135 = nm->mkNode(MULT, const_rational_5, t);
  Node geq_169 = nm->mkNode(GEQ, s, mult_135);
  Node mult_139 = nm->mkNode(MULT, const_rational_6, t);
  Node geq_168 = nm->mkNode(GEQ, s, mult_139);
  Node mult_141 = nm->mkNode(MULT, const_rational_7, t);
  Node geq_167 = nm->mkNode(GEQ, s, mult_141);
  Node mult_144 = nm->mkNode(MULT, const_rational_8, t);
  Node geq_166 = nm->mkNode(GEQ, s, mult_144);
  Node mult_165 = nm->mkNode(MULT, const_rational_9, t);
  Node geq_164 = nm->mkNode(GEQ, s, mult_165);
  Node mult_147 = nm->mkNode(MULT, const_rational_10, t);
  Node geq_163 = nm->mkNode(GEQ, s, mult_147);
  Node mult_162 = nm->mkNode(MULT, const_rational_11, t);
  Node geq_161 = nm->mkNode(GEQ, s, mult_162);
  Node mult_150 = nm->mkNode(MULT, const_rational_12, t);
  Node geq_160 = nm->mkNode(GEQ, s, mult_150);
  Node mult_159 = nm->mkNode(MULT, const_rational_13, t);
  Node geq_158 = nm->mkNode(GEQ, s, mult_159);
  Node mult_153 = nm->mkNode(MULT, const_rational_14, t);
  Node geq_157 = nm->mkNode(GEQ, s, mult_153);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node mult_156 = nm->mkNode(MULT, const_rational_15, t);
  Node geq_155 = nm->mkNode(GEQ, s, mult_156);
  Node equal_154 = nm->mkNode(EQUAL, s, plus_70);
  Node ite_152 = nm->mkNode(ITE, equal_154, plus_70, mult_153);
  Node ite_151 = nm->mkNode(ITE, geq_155, ite_152, plus_70);
  Node ite_149 = nm->mkNode(ITE, geq_157, ite_151, mult_150);
  Node ite_148 = nm->mkNode(ITE, geq_158, ite_149, plus_70);
  Node ite_146 = nm->mkNode(ITE, geq_160, ite_148, mult_147);
  Node ite_145 = nm->mkNode(ITE, geq_161, ite_146, plus_70);
  Node ite_143 = nm->mkNode(ITE, geq_163, ite_145, mult_144);
  Node ite_142 = nm->mkNode(ITE, geq_164, ite_143, plus_70);
  Node equal_140 = nm->mkNode(EQUAL, s, mult_141);
  Node ite_138 = nm->mkNode(ITE, equal_140, mult_139, const_rational_13);
  Node ite_137 = nm->mkNode(ITE, geq_166, ite_142, ite_138);
  Node ite_136 = nm->mkNode(ITE, geq_167, ite_137, plus_70);
  Node equal_134 = nm->mkNode(EQUAL, s, mult_135);
  Node ite_133 = nm->mkNode(ITE, equal_134, mult_131, const_rational_9);
  Node ite_132 = nm->mkNode(ITE, geq_168, ite_136, ite_133);
  Node equal_130 = nm->mkNode(EQUAL, s, mult_131);
  Node ite_129 =
      nm->mkNode(ITE, equal_19, const_rational_13, const_rational_14);
  Node ite_128 = nm->mkNode(ITE, equal_91, plus_70, ite_129);
  Node ite_127 = nm->mkNode(ITE, equal_130, plus_70, ite_128);
  Node ite_126 = nm->mkNode(ITE, geq_169, ite_132, ite_127);
  Node equal_125 = nm->mkNode(EQUAL, s, mult_119);
  Node equal_34 = nm->mkNode(EQUAL, s, const_rational_15);
  Node equal_124 = nm->mkNode(EQUAL, t, const_rational_1);
  Node ite_123 = nm->mkNode(ITE, equal_90, const_rational_10, mult_69);
  Node ite_122 = nm->mkNode(ITE, equal_91, mult_69, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_124, mult_69, ite_122);
  Node ite_120 = nm->mkNode(ITE, equal_34, mult_69, ite_121);
  Node ite_118 = nm->mkNode(ITE, equal_52, mult_119, const_rational_8);
  Node ite_117 =
      nm->mkNode(ITE, equal_19, const_rational_10, const_rational_11);
  Node ite_116 = nm->mkNode(ITE, equal_25, const_rational_9, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_90, ite_118, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_91, const_rational_5, ite_115);
  Node ite_113 = nm->mkNode(ITE, equal_125, ite_120, ite_114);
  Node ite_112 = nm->mkNode(ITE, geq_170, ite_126, ite_113);
  Node equal_111 = nm->mkNode(EQUAL, s, mult_69);
  Node geq_110 = nm->mkNode(GEQ, s, const_rational_8);
  Node ite_109 = nm->mkNode(ITE, equal_78, const_rational_10, const_rational_9);
  Node ite_108 = nm->mkNode(ITE, equal_83, plus_70, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_87, plus_70, ite_108);
  Node ite_106 = nm->mkNode(ITE, equal_82, const_rational_5, plus_70);
  Node ite_105 = nm->mkNode(ITE, geq_110, ite_107, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_77, const_rational_4, plus_70);
  Node ite_103 = nm->mkNode(ITE, equal_25, const_rational_8, const_rational_11);
  Node ite_102 = nm->mkNode(ITE, equal_37, const_rational_9, ite_103);
  Node ite_101 = nm->mkNode(ITE, equal_44, const_rational_14, ite_102);
  Node ite_100 = nm->mkNode(ITE, equal_19, const_rational_8, const_rational_9);
  Node ite_99 = nm->mkNode(ITE, equal_25, const_rational_11, ite_100);
  Node ite_98 = nm->mkNode(ITE, equal_78, ite_99, const_rational_8);
  Node ite_97 = nm->mkNode(ITE, equal_83, ite_101, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_87, plus_70, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_90, ite_104, ite_96);
  Node ite_94 = nm->mkNode(ITE, equal_91, plus_70, ite_95);
  Node ite_93 = nm->mkNode(ITE, equal_111, ite_105, ite_94);
  Node ite_92 = nm->mkNode(ITE, geq_171, ite_112, ite_93);
  Node ite_88 = nm->mkNode(ITE, equal_89, plus_70, mult_69);
  Node ite_85 = nm->mkNode(ITE, equal_82, const_rational_2, const_rational_3);
  Node ite_84 = nm->mkNode(ITE, equal_86, const_rational_1, ite_85);
  Node ite_81 = nm->mkNode(ITE, equal_71, plus_70, const_rational_12);
  Node ite_80 = nm->mkNode(ITE, equal_77, const_rational_2, ite_81);
  Node ite_79 = nm->mkNode(ITE, equal_82, const_rational_3, ite_80);
  Node ite_76 = nm->mkNode(ITE, equal_52, mult_69, const_rational_13);
  Node ite_75 = nm->mkNode(ITE, equal_61, plus_70, ite_76);
  Node ite_74 = nm->mkNode(ITE, equal_71, plus_70, ite_75);
  Node ite_73 = nm->mkNode(ITE, equal_77, const_rational_1, ite_74);
  Node ite_68 = nm->mkNode(ITE, equal_25, const_rational_10, const_rational_11);
  Node ite_67 = nm->mkNode(ITE, equal_44, const_rational_12, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_52, const_rational_13, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_61, mult_69, ite_66);
  Node ite_64 = nm->mkNode(ITE, equal_71, plus_70, ite_65);
  Node ite_60 = nm->mkNode(ITE, equal_19, const_rational_6, const_rational_7);
  Node ite_59 = nm->mkNode(ITE, equal_25, const_rational_5, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_37, const_rational_4, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_44, const_rational_3, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_52, const_rational_2, ite_57);
  Node ite_55 = nm->mkNode(ITE, equal_61, const_rational_1, ite_56);
  Node ite_51 = nm->mkNode(ITE, equal_25, const_rational_4, const_rational_7);
  Node ite_50 = nm->mkNode(ITE, equal_37, const_rational_5, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_44, const_rational_2, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_34, const_rational_6, ite_49);
  Node ite_47 = nm->mkNode(ITE, equal_52, const_rational_3, ite_48);
  Node ite_43 = nm->mkNode(ITE, equal_25, const_rational_7, const_rational_4);
  Node ite_42 = nm->mkNode(ITE, equal_37, const_rational_6, ite_43);
  Node ite_41 = nm->mkNode(ITE, equal_44, const_rational_1, ite_42);
  Node ite_40 = nm->mkNode(ITE, equal_34, const_rational_5, ite_41);
  Node ite_30 = nm->mkNode(ITE, equal_25, const_rational_6, const_rational_5);
  Node ite_29 = nm->mkNode(ITE, equal_34, const_rational_4, ite_30);
  Node ite_28 = nm->mkNode(ITE, equal_37, const_rational_7, ite_29);
  Node ite_24 = nm->mkNode(ITE, equal_19, const_rational_2, const_rational_3);
  Node ite_23 = nm->mkNode(ITE, equal_25, const_rational_1, ite_24);
  Node ite_16 = nm->mkNode(ITE, equal_19, const_rational_3, const_rational_2);
  Node ite_14 = nm->mkNode(ITE, equal_21, ite_16, const_rational_1);
  Node ite_13 = nm->mkNode(ITE, equal_26, ite_23, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_38, ite_28, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_45, ite_40, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_53, ite_47, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_62, ite_55, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_72, ite_64, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_78, ite_73, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_83, ite_79, ite_7);
  Node ite_5 = nm->mkNode(ITE, equal_87, ite_84, ite_6);
  Node ite_4 = nm->mkNode(ITE, equal_90, ite_88, ite_5);
  Node ite_3 = nm->mkNode(ITE, equal_91, const_rational_1, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_172, ite_92, ite_3);
  Node ite_1 = nm->mkNode(ITE, geq_286, ite_173, ite_2);
  return ite_1;
}

// (define-fun int_bvxor_4_nia ((s Int) (t Int)) Int (ite (= s (* s s)) (ite (>=
// s (* s t)) (ite (>= t s) (ite (= s 0) (+ s t) 0) (+ s t)) (ite (= t 2) (+ s
// t) (ite (= t 3) (+ s (* s s)) (ite (= t 4) (+ s t) (ite (= t 5) (* s 4) (ite
// (= t 14) (+ s t) (ite (= t 6) (+ s t) (ite (= t 7) (* s 6) (ite (= t 8) (+ s
// t) (ite (= t 9) (* s 8) (ite (= t 10) (+ s t) (ite (= t 11) (* s 10) (ite (=
// t 12) (+ s t) (ite (= t 13) (* s 12) (* s 14))))))))))))))) (ite (>= s (* s
// t)) (ite (= s (* s t)) (ite (= s (+ t t)) (+ s t) (ite (= s 3) (+ t t) (ite
// (= s 4) (+ s t) (ite (= s 5) 4 (ite (= s 6) (+ s t) (ite (= s 7) 6 (ite (= s
// 8) (+ s t) (ite (= s 9) 8 (ite (= s 10) (+ s t) (ite (= s 11) 10 (ite (= s
// 12) (+ s t) (ite (= s 13) 12 (ite (= s 14) (+ s t) 14))))))))))))) (+ s t))
// (ite (>= t s) (ite (>= s t) 0 (ite (= t 3) 1 (ite (= t 4) (+ s t) (ite (= t
// 5) (ite (= s 2) (+ s t) (ite (= s 3) (+ s s) 1)) (ite (= t 6) (ite (= s 2) (*
// s s) (ite (= s 3) (+ s 2) (ite (= s 5) 3 2))) (ite (= t 7) (ite (= s 2) (+ s
// 3) (ite (= s 3) (+ s 1) (ite (= s 4) 3 (ite (= s 5) 2 1)))) (ite (= t 8) (+ s
// t) (ite (= t 9) (ite (= s 2) (+ s t) (ite (= s 3) (+ s 7) (ite (= s 4) (+ s
// t) (ite (= s 5) (+ s 7) (ite (= s 6) (+ s t) (ite (= s 7) (+ s s) 1))))))
// (ite (= t 10) (ite (= s 2) (* s (* s s)) (ite (= s 3) (* s s) (ite (= s 4) (+
// s t) (ite (= s 5) (+ s t) (ite (= s 6) (+ s s) (ite (= s 7) (+ s 6) (ite (= s
// 8) 2 3))))))) (ite (= t 11) (ite (= s 2) (+ s 7) (ite (= s 3) (+ s 5) (ite (=
// s 4) (+ s t) (ite (= s 10) 1 (ite (= s 9) 2 (ite (= s 5) (+ s 9) (ite (= s 6)
// (+ s 7) (ite (= s 7) (+ s 5) 3)))))))) (ite (= t 12) (ite (= s 2) (+ s t)
// (ite (= s 3) (+ s t) (ite (= s 4) (+ s s) (ite (= s 5) (+ s 4) (ite (= s 6)
// (+ s 4) (ite (= s 7) (+ s 4) (ite (= s 8) 4 (ite (= s 9) 5 (ite (= s 10) 6
// 7))))))))) (ite (= t 13) (ite (= s 2) (+ s t) (ite (= s 3) (+ s 11) (ite (= s
// 4) (+ s 5) (ite (= s 5) (+ s 3) (ite (= s 6) (+ s 5) (ite (= s 7) (+ s 3)
// (ite (= s 8) 5 (ite (= s 9) 4 (ite (= s 10) 7 (ite (= s 12) 1 6))))))))))
// (ite (= t 14) (ite (= s 2) (* s 6) (ite (= s 3) (+ s 10) (ite (= s 4) (+ s 6)
// (ite (= s 5) (+ s 6) (ite (= s 6) (+ s 2) (ite (= s 7) (+ s 2) (ite (= s 8) 6
// (ite (= s 9) 7 (ite (= s 10) 4 (ite (= s 11) 5 (ite (= s 12) 2 3)))))))))))
// (ite (= s 2) (+ s 11) (ite (= s 3) (+ s (* s s)) (ite (= s 4) (+ s 7) (ite (=
// s 5) (+ s s) (ite (= s 6) (+ s 3) (ite (= s 7) (+ s 1) (ite (= s 8) 7 (ite (=
// s 9) 6 (ite (= s 10) 5 (ite (= s 11) 4 (ite (= s 12) 3 (ite (= s 14) 1
// 2))))))))))))))))))))))))) (ite (>= s (* t t)) (ite (= s (* t t)) (ite (= s
// (+ t t)) (+ s t) (+ s 1)) (ite (= t 2) (ite (= s 5) (+ s t) (ite (= s 6) (* t
// t) (ite (= s 7) 5 (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (ite (= s 15) 13
// (ite (= s 10) 8 (ite (= s 11) 9 (ite (= s 12) (+ s t) (ite (= s 13) (+ s t)
// 12)))))))))) (ite (= s 10) (* t t) (ite (= s 11) 8 (ite (= s 15) 12 (ite (= s
// 12) (+ s t) (ite (= s 13) (+ s 1) 13))))))) (ite (>= s (+ t t)) (ite (= s (+
// t t)) (ite (= t 3) 5 (ite (= t 4) (+ s t) (ite (= t 5) (+ s t) (ite (= t 6)
// 10 9)))) (ite (= t 3) (ite (= s 7) 4 (+ s t)) (ite (= t 4) (ite (= s 9) (+ s
// t) (ite (= s 10) (+ s t) (ite (= s 11) (+ s t) (ite (= s 12) (+ t t) (ite (=
// s 13) 9 (ite (= s 14) 10 11)))))) (ite (= t 5) (ite (= s 11) (+ s 3) (ite (=
// s 12) 9 (ite (= s 13) 8 (ite (= s 14) 11 (+ t t))))) (ite (= t 6) (ite (= s
// 13) 11 (ite (= s 15) 9 8)) 8))))) (ite (= t 2) 1 (ite (= t 3) (ite (= s 4) (+
// s t) (+ t t)) (ite (= t 4) (ite (= s 5) 1 (ite (= s 6) 2 3)) (ite (= t 5)
// (ite (= s 6) 3 (ite (= s 7) 2 (ite (= s 8) (+ s t) (+ s 3)))) (ite (= t 6)
// (ite (= s 7) 1 (ite (= s 8) (+ s t) (ite (= s 9) (+ s t) (+ s 2)))) (ite (= t
// 7) (ite (= s 8) (+ s t) (ite (= s 9) (+ t t) (ite (= s 10) (+ s 3) (ite (= s
// 11) (+ s 1) (ite (= s 12) 11 10))))) (ite (= t 8) (ite (= s 9) 1 (ite (= s
// 10) 2 (ite (= s 11) 3 (ite (= s 12) 4 (ite (= s 13) 5 (ite (= s 14) 6 7))))))
// (ite (= t 9) (ite (= s 10) 3 (ite (= s 11) 2 (ite (= s 12) 5 (ite (= s 13) 4
// (ite (= s 14) 7 6))))) (ite (= t 10) (ite (= s 11) 1 (ite (= s 12) 6 (ite (=
// s 13) 7 (ite (= s 14) 4 5)))) (ite (= t 11) (ite (= s 12) 7 (ite (= s 13) 6
// (ite (= s 14) 5 4))) (ite (= t 12) (ite (= s 13) 1 (ite (= s 14) 2 3)) (ite
// (= t 13) (ite (= s 14) 3 2) 1))))))))))))))))))
Node int_bvxor_4_nia(Node s, Node t)
{
  NodeManager * nm = NodeManager::currentNM();
  Node mult_170 = nm->mkNode(MULT, s, s);
  Node equal_284 = nm->mkNode(EQUAL, s, mult_170);
  Node mult_260 = nm->mkNode(MULT, s, t);
  Node geq_261 = nm->mkNode(GEQ, s, mult_260);
  Node geq_244 = nm->mkNode(GEQ, t, s);
  Node const_rational_0 = nm->mkConst<Rational>(0);
  Node equal_283 = nm->mkNode(EQUAL, s, const_rational_0);
  Node plus_73 = nm->mkNode(PLUS, s, t);
  Node ite_282 = nm->mkNode(ITE, equal_283, plus_73, const_rational_0);
  Node ite_281 = nm->mkNode(ITE, geq_244, ite_282, plus_73);
  Node const_rational_2 = nm->mkConst<Rational>(2);
  Node equal_94 = nm->mkNode(EQUAL, t, const_rational_2);
  Node const_rational_3 = nm->mkConst<Rational>(3);
  Node equal_93 = nm->mkNode(EQUAL, t, const_rational_3);
  Node plus_169 = nm->mkNode(PLUS, s, mult_170);
  Node const_rational_4 = nm->mkConst<Rational>(4);
  Node equal_90 = nm->mkNode(EQUAL, t, const_rational_4);
  Node const_rational_5 = nm->mkConst<Rational>(5);
  Node equal_86 = nm->mkNode(EQUAL, t, const_rational_5);
  Node mult_280 = nm->mkNode(MULT, s, const_rational_4);
  Node const_rational_14 = nm->mkConst<Rational>(14);
  Node equal_188 = nm->mkNode(EQUAL, t, const_rational_14);
  Node const_rational_6 = nm->mkConst<Rational>(6);
  Node equal_81 = nm->mkNode(EQUAL, t, const_rational_6);
  Node const_rational_7 = nm->mkConst<Rational>(7);
  Node equal_75 = nm->mkNode(EQUAL, t, const_rational_7);
  Node mult_187 = nm->mkNode(MULT, s, const_rational_6);
  Node const_rational_8 = nm->mkConst<Rational>(8);
  Node equal_63 = nm->mkNode(EQUAL, t, const_rational_8);
  Node const_rational_9 = nm->mkConst<Rational>(9);
  Node equal_54 = nm->mkNode(EQUAL, t, const_rational_9);
  Node mult_279 = nm->mkNode(MULT, s, const_rational_8);
  Node const_rational_10 = nm->mkConst<Rational>(10);
  Node equal_46 = nm->mkNode(EQUAL, t, const_rational_10);
  Node const_rational_11 = nm->mkConst<Rational>(11);
  Node equal_39 = nm->mkNode(EQUAL, t, const_rational_11);
  Node mult_278 = nm->mkNode(MULT, s, const_rational_10);
  Node const_rational_12 = nm->mkConst<Rational>(12);
  Node equal_29 = nm->mkNode(EQUAL, t, const_rational_12);
  Node const_rational_13 = nm->mkConst<Rational>(13);
  Node equal_24 = nm->mkNode(EQUAL, t, const_rational_13);
  Node mult_277 = nm->mkNode(MULT, s, const_rational_12);
  Node mult_276 = nm->mkNode(MULT, s, const_rational_14);
  Node ite_275 = nm->mkNode(ITE, equal_24, mult_277, mult_276);
  Node ite_274 = nm->mkNode(ITE, equal_29, plus_73, ite_275);
  Node ite_273 = nm->mkNode(ITE, equal_39, mult_278, ite_274);
  Node ite_272 = nm->mkNode(ITE, equal_46, plus_73, ite_273);
  Node ite_271 = nm->mkNode(ITE, equal_54, mult_279, ite_272);
  Node ite_270 = nm->mkNode(ITE, equal_63, plus_73, ite_271);
  Node ite_269 = nm->mkNode(ITE, equal_75, mult_187, ite_270);
  Node ite_268 = nm->mkNode(ITE, equal_81, plus_73, ite_269);
  Node ite_267 = nm->mkNode(ITE, equal_188, plus_73, ite_268);
  Node ite_266 = nm->mkNode(ITE, equal_86, mult_280, ite_267);
  Node ite_265 = nm->mkNode(ITE, equal_90, plus_73, ite_266);
  Node ite_264 = nm->mkNode(ITE, equal_93, plus_169, ite_265);
  Node ite_263 = nm->mkNode(ITE, equal_94, plus_73, ite_264);
  Node ite_262 = nm->mkNode(ITE, geq_261, ite_281, ite_263);
  Node equal_259 = nm->mkNode(EQUAL, s, mult_260);
  Node plus_72 = nm->mkNode(PLUS, t, t);
  Node equal_119 = nm->mkNode(EQUAL, s, plus_72);
  Node equal_171 = nm->mkNode(EQUAL, s, const_rational_3);
  Node equal_92 = nm->mkNode(EQUAL, s, const_rational_4);
  Node equal_89 = nm->mkNode(EQUAL, s, const_rational_5);
  Node equal_85 = nm->mkNode(EQUAL, s, const_rational_6);
  Node equal_80 = nm->mkNode(EQUAL, s, const_rational_7);
  Node equal_74 = nm->mkNode(EQUAL, s, const_rational_8);
  Node equal_62 = nm->mkNode(EQUAL, s, const_rational_9);
  Node equal_53 = nm->mkNode(EQUAL, s, const_rational_10);
  Node equal_45 = nm->mkNode(EQUAL, s, const_rational_11);
  Node equal_38 = nm->mkNode(EQUAL, s, const_rational_12);
  Node equal_28 = nm->mkNode(EQUAL, s, const_rational_13);
  Node equal_22 = nm->mkNode(EQUAL, s, const_rational_14);
  Node ite_258 = nm->mkNode(ITE, equal_22, plus_73, const_rational_14);
  Node ite_257 = nm->mkNode(ITE, equal_28, const_rational_12, ite_258);
  Node ite_256 = nm->mkNode(ITE, equal_38, plus_73, ite_257);
  Node ite_255 = nm->mkNode(ITE, equal_45, const_rational_10, ite_256);
  Node ite_254 = nm->mkNode(ITE, equal_53, plus_73, ite_255);
  Node ite_253 = nm->mkNode(ITE, equal_62, const_rational_8, ite_254);
  Node ite_252 = nm->mkNode(ITE, equal_74, plus_73, ite_253);
  Node ite_251 = nm->mkNode(ITE, equal_80, const_rational_6, ite_252);
  Node ite_250 = nm->mkNode(ITE, equal_85, plus_73, ite_251);
  Node ite_249 = nm->mkNode(ITE, equal_89, const_rational_4, ite_250);
  Node ite_248 = nm->mkNode(ITE, equal_92, plus_73, ite_249);
  Node ite_247 = nm->mkNode(ITE, equal_171, plus_72, ite_248);
  Node ite_246 = nm->mkNode(ITE, equal_119, plus_73, ite_247);
  Node ite_245 = nm->mkNode(ITE, equal_259, ite_246, plus_73);
  Node geq_243 = nm->mkNode(GEQ, s, t);
  Node const_rational_1 = nm->mkConst<Rational>(1);
  Node equal_173 = nm->mkNode(EQUAL, s, const_rational_2);
  Node plus_167 = nm->mkNode(PLUS, s, s);
  Node ite_241 = nm->mkNode(ITE, equal_171, plus_167, const_rational_1);
  Node ite_240 = nm->mkNode(ITE, equal_173, plus_73, ite_241);
  Node plus_79 = nm->mkNode(PLUS, s, const_rational_2);
  Node ite_239 = nm->mkNode(ITE, equal_89, const_rational_3, const_rational_2);
  Node ite_238 = nm->mkNode(ITE, equal_171, plus_79, ite_239);
  Node ite_237 = nm->mkNode(ITE, equal_173, mult_170, ite_238);
  Node plus_71 = nm->mkNode(PLUS, s, const_rational_3);
  Node plus_70 = nm->mkNode(PLUS, s, const_rational_1);
  Node ite_236 = nm->mkNode(ITE, equal_89, const_rational_2, const_rational_1);
  Node ite_235 = nm->mkNode(ITE, equal_92, const_rational_3, ite_236);
  Node ite_234 = nm->mkNode(ITE, equal_171, plus_70, ite_235);
  Node ite_233 = nm->mkNode(ITE, equal_173, plus_71, ite_234);
  Node plus_168 = nm->mkNode(PLUS, s, const_rational_7);
  Node ite_232 = nm->mkNode(ITE, equal_80, plus_167, const_rational_1);
  Node ite_231 = nm->mkNode(ITE, equal_85, plus_73, ite_232);
  Node ite_230 = nm->mkNode(ITE, equal_89, plus_168, ite_231);
  Node ite_229 = nm->mkNode(ITE, equal_92, plus_73, ite_230);
  Node ite_228 = nm->mkNode(ITE, equal_171, plus_168, ite_229);
  Node ite_227 = nm->mkNode(ITE, equal_173, plus_73, ite_228);
  Node mult_226 = nm->mkNode(MULT, s, mult_170);
  Node plus_185 = nm->mkNode(PLUS, s, const_rational_6);
  Node ite_225 = nm->mkNode(ITE, equal_74, const_rational_2, const_rational_3);
  Node ite_224 = nm->mkNode(ITE, equal_80, plus_185, ite_225);
  Node ite_223 = nm->mkNode(ITE, equal_85, plus_167, ite_224);
  Node ite_222 = nm->mkNode(ITE, equal_89, plus_73, ite_223);
  Node ite_221 = nm->mkNode(ITE, equal_92, plus_73, ite_222);
  Node ite_220 = nm->mkNode(ITE, equal_171, mult_170, ite_221);
  Node ite_219 = nm->mkNode(ITE, equal_173, mult_226, ite_220);
  Node plus_199 = nm->mkNode(PLUS, s, const_rational_5);
  Node plus_218 = nm->mkNode(PLUS, s, const_rational_9);
  Node ite_217 = nm->mkNode(ITE, equal_80, plus_199, const_rational_3);
  Node ite_216 = nm->mkNode(ITE, equal_85, plus_168, ite_217);
  Node ite_215 = nm->mkNode(ITE, equal_89, plus_218, ite_216);
  Node ite_214 = nm->mkNode(ITE, equal_62, const_rational_2, ite_215);
  Node ite_213 = nm->mkNode(ITE, equal_53, const_rational_1, ite_214);
  Node ite_212 = nm->mkNode(ITE, equal_92, plus_73, ite_213);
  Node ite_211 = nm->mkNode(ITE, equal_171, plus_199, ite_212);
  Node ite_210 = nm->mkNode(ITE, equal_173, plus_168, ite_211);
  Node plus_209 = nm->mkNode(PLUS, s, const_rational_4);
  Node ite_208 = nm->mkNode(ITE, equal_53, const_rational_6, const_rational_7);
  Node ite_207 = nm->mkNode(ITE, equal_62, const_rational_5, ite_208);
  Node ite_206 = nm->mkNode(ITE, equal_74, const_rational_4, ite_207);
  Node ite_205 = nm->mkNode(ITE, equal_80, plus_209, ite_206);
  Node ite_204 = nm->mkNode(ITE, equal_85, plus_209, ite_205);
  Node ite_203 = nm->mkNode(ITE, equal_89, plus_209, ite_204);
  Node ite_202 = nm->mkNode(ITE, equal_92, plus_167, ite_203);
  Node ite_201 = nm->mkNode(ITE, equal_171, plus_73, ite_202);
  Node ite_200 = nm->mkNode(ITE, equal_173, plus_73, ite_201);
  Node plus_172 = nm->mkNode(PLUS, s, const_rational_11);
  Node ite_198 = nm->mkNode(ITE, equal_38, const_rational_1, const_rational_6);
  Node ite_197 = nm->mkNode(ITE, equal_53, const_rational_7, ite_198);
  Node ite_196 = nm->mkNode(ITE, equal_62, const_rational_4, ite_197);
  Node ite_195 = nm->mkNode(ITE, equal_74, const_rational_5, ite_196);
  Node ite_194 = nm->mkNode(ITE, equal_80, plus_71, ite_195);
  Node ite_193 = nm->mkNode(ITE, equal_85, plus_199, ite_194);
  Node ite_192 = nm->mkNode(ITE, equal_89, plus_71, ite_193);
  Node ite_191 = nm->mkNode(ITE, equal_92, plus_199, ite_192);
  Node ite_190 = nm->mkNode(ITE, equal_171, plus_172, ite_191);
  Node ite_189 = nm->mkNode(ITE, equal_173, plus_73, ite_190);
  Node plus_186 = nm->mkNode(PLUS, s, const_rational_10);
  Node ite_184 = nm->mkNode(ITE, equal_38, const_rational_2, const_rational_3);
  Node ite_183 = nm->mkNode(ITE, equal_45, const_rational_5, ite_184);
  Node ite_182 = nm->mkNode(ITE, equal_53, const_rational_4, ite_183);
  Node ite_181 = nm->mkNode(ITE, equal_62, const_rational_7, ite_182);
  Node ite_180 = nm->mkNode(ITE, equal_74, const_rational_6, ite_181);
  Node ite_179 = nm->mkNode(ITE, equal_80, plus_79, ite_180);
  Node ite_178 = nm->mkNode(ITE, equal_85, plus_79, ite_179);
  Node ite_177 = nm->mkNode(ITE, equal_89, plus_185, ite_178);
  Node ite_176 = nm->mkNode(ITE, equal_92, plus_185, ite_177);
  Node ite_175 = nm->mkNode(ITE, equal_171, plus_186, ite_176);
  Node ite_174 = nm->mkNode(ITE, equal_173, mult_187, ite_175);
  Node ite_166 = nm->mkNode(ITE, equal_22, const_rational_1, const_rational_2);
  Node ite_165 = nm->mkNode(ITE, equal_38, const_rational_3, ite_166);
  Node ite_164 = nm->mkNode(ITE, equal_45, const_rational_4, ite_165);
  Node ite_163 = nm->mkNode(ITE, equal_53, const_rational_5, ite_164);
  Node ite_162 = nm->mkNode(ITE, equal_62, const_rational_6, ite_163);
  Node ite_161 = nm->mkNode(ITE, equal_74, const_rational_7, ite_162);
  Node ite_160 = nm->mkNode(ITE, equal_80, plus_70, ite_161);
  Node ite_159 = nm->mkNode(ITE, equal_85, plus_71, ite_160);
  Node ite_158 = nm->mkNode(ITE, equal_89, plus_167, ite_159);
  Node ite_157 = nm->mkNode(ITE, equal_92, plus_168, ite_158);
  Node ite_156 = nm->mkNode(ITE, equal_171, plus_169, ite_157);
  Node ite_155 = nm->mkNode(ITE, equal_173, plus_172, ite_156);
  Node ite_154 = nm->mkNode(ITE, equal_188, ite_174, ite_155);
  Node ite_153 = nm->mkNode(ITE, equal_24, ite_189, ite_154);
  Node ite_152 = nm->mkNode(ITE, equal_29, ite_200, ite_153);
  Node ite_151 = nm->mkNode(ITE, equal_39, ite_210, ite_152);
  Node ite_150 = nm->mkNode(ITE, equal_46, ite_219, ite_151);
  Node ite_149 = nm->mkNode(ITE, equal_54, ite_227, ite_150);
  Node ite_148 = nm->mkNode(ITE, equal_63, plus_73, ite_149);
  Node ite_147 = nm->mkNode(ITE, equal_75, ite_233, ite_148);
  Node ite_146 = nm->mkNode(ITE, equal_81, ite_237, ite_147);
  Node ite_145 = nm->mkNode(ITE, equal_86, ite_240, ite_146);
  Node ite_144 = nm->mkNode(ITE, equal_90, plus_73, ite_145);
  Node ite_143 = nm->mkNode(ITE, equal_93, const_rational_1, ite_144);
  Node ite_142 = nm->mkNode(ITE, geq_243, const_rational_0, ite_143);
  Node mult_128 = nm->mkNode(MULT, t, t);
  Node geq_141 = nm->mkNode(GEQ, s, mult_128);
  Node equal_140 = nm->mkNode(EQUAL, s, mult_128);
  Node ite_139 = nm->mkNode(ITE, equal_119, plus_73, plus_70);
  Node const_rational_15 = nm->mkConst<Rational>(15);
  Node equal_102 = nm->mkNode(EQUAL, s, const_rational_15);
  Node ite_138 = nm->mkNode(ITE, equal_28, plus_73, const_rational_12);
  Node ite_137 = nm->mkNode(ITE, equal_38, plus_73, ite_138);
  Node ite_136 = nm->mkNode(ITE, equal_45, const_rational_9, ite_137);
  Node ite_135 = nm->mkNode(ITE, equal_53, const_rational_8, ite_136);
  Node ite_134 = nm->mkNode(ITE, equal_102, const_rational_13, ite_135);
  Node ite_133 = nm->mkNode(ITE, equal_62, plus_73, ite_134);
  Node ite_132 = nm->mkNode(ITE, equal_74, plus_73, ite_133);
  Node ite_131 = nm->mkNode(ITE, equal_80, const_rational_5, ite_132);
  Node ite_130 = nm->mkNode(ITE, equal_85, mult_128, ite_131);
  Node ite_129 = nm->mkNode(ITE, equal_89, plus_73, ite_130);
  Node ite_127 = nm->mkNode(ITE, equal_28, plus_70, const_rational_13);
  Node ite_126 = nm->mkNode(ITE, equal_38, plus_73, ite_127);
  Node ite_125 = nm->mkNode(ITE, equal_102, const_rational_12, ite_126);
  Node ite_124 = nm->mkNode(ITE, equal_45, const_rational_8, ite_125);
  Node ite_123 = nm->mkNode(ITE, equal_53, mult_128, ite_124);
  Node ite_122 = nm->mkNode(ITE, equal_94, ite_129, ite_123);
  Node ite_121 = nm->mkNode(ITE, equal_140, ite_139, ite_122);
  Node geq_120 = nm->mkNode(GEQ, s, plus_72);
  Node ite_118 = nm->mkNode(ITE, equal_81, const_rational_10, const_rational_9);
  Node ite_117 = nm->mkNode(ITE, equal_86, plus_73, ite_118);
  Node ite_116 = nm->mkNode(ITE, equal_90, plus_73, ite_117);
  Node ite_115 = nm->mkNode(ITE, equal_93, const_rational_5, ite_116);
  Node ite_114 = nm->mkNode(ITE, equal_80, const_rational_4, plus_73);
  Node ite_113 =
      nm->mkNode(ITE, equal_22, const_rational_10, const_rational_11);
  Node ite_112 = nm->mkNode(ITE, equal_28, const_rational_9, ite_113);
  Node ite_111 = nm->mkNode(ITE, equal_38, plus_72, ite_112);
  Node ite_110 = nm->mkNode(ITE, equal_45, plus_73, ite_111);
  Node ite_109 = nm->mkNode(ITE, equal_53, plus_73, ite_110);
  Node ite_108 = nm->mkNode(ITE, equal_62, plus_73, ite_109);
  Node ite_107 = nm->mkNode(ITE, equal_22, const_rational_11, plus_72);
  Node ite_106 = nm->mkNode(ITE, equal_28, const_rational_8, ite_107);
  Node ite_105 = nm->mkNode(ITE, equal_38, const_rational_9, ite_106);
  Node ite_104 = nm->mkNode(ITE, equal_45, plus_71, ite_105);
  Node ite_101 = nm->mkNode(ITE, equal_102, const_rational_9, const_rational_8);
  Node ite_100 = nm->mkNode(ITE, equal_28, const_rational_11, ite_101);
  Node ite_99 = nm->mkNode(ITE, equal_81, ite_100, const_rational_8);
  Node ite_98 = nm->mkNode(ITE, equal_86, ite_104, ite_99);
  Node ite_97 = nm->mkNode(ITE, equal_90, ite_108, ite_98);
  Node ite_96 = nm->mkNode(ITE, equal_93, ite_114, ite_97);
  Node ite_95 = nm->mkNode(ITE, equal_119, ite_115, ite_96);
  Node ite_91 = nm->mkNode(ITE, equal_92, plus_73, plus_72);
  Node ite_88 = nm->mkNode(ITE, equal_85, const_rational_2, const_rational_3);
  Node ite_87 = nm->mkNode(ITE, equal_89, const_rational_1, ite_88);
  Node ite_84 = nm->mkNode(ITE, equal_74, plus_73, plus_71);
  Node ite_83 = nm->mkNode(ITE, equal_80, const_rational_2, ite_84);
  Node ite_82 = nm->mkNode(ITE, equal_85, const_rational_3, ite_83);
  Node ite_78 = nm->mkNode(ITE, equal_62, plus_73, plus_79);
  Node ite_77 = nm->mkNode(ITE, equal_74, plus_73, ite_78);
  Node ite_76 = nm->mkNode(ITE, equal_80, const_rational_1, ite_77);
  Node ite_69 = nm->mkNode(ITE, equal_38, const_rational_11, const_rational_10);
  Node ite_68 = nm->mkNode(ITE, equal_45, plus_70, ite_69);
  Node ite_67 = nm->mkNode(ITE, equal_53, plus_71, ite_68);
  Node ite_66 = nm->mkNode(ITE, equal_62, plus_72, ite_67);
  Node ite_65 = nm->mkNode(ITE, equal_74, plus_73, ite_66);
  Node ite_61 = nm->mkNode(ITE, equal_22, const_rational_6, const_rational_7);
  Node ite_60 = nm->mkNode(ITE, equal_28, const_rational_5, ite_61);
  Node ite_59 = nm->mkNode(ITE, equal_38, const_rational_4, ite_60);
  Node ite_58 = nm->mkNode(ITE, equal_45, const_rational_3, ite_59);
  Node ite_57 = nm->mkNode(ITE, equal_53, const_rational_2, ite_58);
  Node ite_56 = nm->mkNode(ITE, equal_62, const_rational_1, ite_57);
  Node ite_52 = nm->mkNode(ITE, equal_22, const_rational_7, const_rational_6);
  Node ite_51 = nm->mkNode(ITE, equal_28, const_rational_4, ite_52);
  Node ite_50 = nm->mkNode(ITE, equal_38, const_rational_5, ite_51);
  Node ite_49 = nm->mkNode(ITE, equal_45, const_rational_2, ite_50);
  Node ite_48 = nm->mkNode(ITE, equal_53, const_rational_3, ite_49);
  Node ite_44 = nm->mkNode(ITE, equal_22, const_rational_4, const_rational_5);
  Node ite_43 = nm->mkNode(ITE, equal_28, const_rational_7, ite_44);
  Node ite_42 = nm->mkNode(ITE, equal_38, const_rational_6, ite_43);
  Node ite_41 = nm->mkNode(ITE, equal_45, const_rational_1, ite_42);
  Node ite_33 = nm->mkNode(ITE, equal_22, const_rational_5, const_rational_4);
  Node ite_32 = nm->mkNode(ITE, equal_28, const_rational_6, ite_33);
  Node ite_31 = nm->mkNode(ITE, equal_38, const_rational_7, ite_32);
  Node ite_27 = nm->mkNode(ITE, equal_22, const_rational_2, const_rational_3);
  Node ite_26 = nm->mkNode(ITE, equal_28, const_rational_1, ite_27);
  Node ite_19 = nm->mkNode(ITE, equal_22, const_rational_3, const_rational_2);
  Node ite_17 = nm->mkNode(ITE, equal_24, ite_19, const_rational_1);
  Node ite_16 = nm->mkNode(ITE, equal_29, ite_26, ite_17);
  Node ite_15 = nm->mkNode(ITE, equal_39, ite_31, ite_16);
  Node ite_14 = nm->mkNode(ITE, equal_46, ite_41, ite_15);
  Node ite_13 = nm->mkNode(ITE, equal_54, ite_48, ite_14);
  Node ite_12 = nm->mkNode(ITE, equal_63, ite_56, ite_13);
  Node ite_11 = nm->mkNode(ITE, equal_75, ite_65, ite_12);
  Node ite_10 = nm->mkNode(ITE, equal_81, ite_76, ite_11);
  Node ite_9 = nm->mkNode(ITE, equal_86, ite_82, ite_10);
  Node ite_8 = nm->mkNode(ITE, equal_90, ite_87, ite_9);
  Node ite_7 = nm->mkNode(ITE, equal_93, ite_91, ite_8);
  Node ite_6 = nm->mkNode(ITE, equal_94, const_rational_1, ite_7);
  Node ite_5 = nm->mkNode(ITE, geq_120, ite_95, ite_6);
  Node ite_4 = nm->mkNode(ITE, geq_141, ite_121, ite_5);
  Node ite_3 = nm->mkNode(ITE, geq_244, ite_142, ite_4);
  Node ite_2 = nm->mkNode(ITE, geq_261, ite_245, ite_3);
  Node ite_1 = nm->mkNode(ITE, equal_284, ite_262, ite_2);
  return ite_1;
}
