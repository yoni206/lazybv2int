(set-option :incremental false)
(set-info :source "Hand-crafted bit-vector benchmarks.  Some are from the SVC benchmark suite.
Contributed by Vijay Ganesh (vganesh@stanford.edu).  Translated into SMT-LIB
format by Clark Barrett using CVC3.")



(set-logic QF_BV)
(declare-fun a () Bool)
(assert  (not (= (concat (_ bv1 1) (ite a (_ bv0 1) (_ bv1 1))) (ite a (_ bv2 2) (_ bv3 2)))) )
(check-sat)
