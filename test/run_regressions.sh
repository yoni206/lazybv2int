#!/bin/bash
MY_DIR="`dirname \"$0\"`"
MY_DIR=`realpath $MY_DIR`
CVC4_PATH=$MY_DIR/../deps/smt-switch/deps/CVC4/build/bin/cvc4
LAZY_PATH=$MY_DIR/../build/lazybv2int
SMTLIB_FILES_DIR=$MY_DIR/smtlib_files
TIME_LIMIT=3
#SMTLIB_FILES_DIR=$MY_DIR/build/tmp

for f in `find $SMTLIB_FILES_DIR -name "*.smt2"`
do
  cvc4_res=`runlim -t $TIME_LIMIT --output-file=tmp1.log $CVC4_PATH $f`
  lbv2int_res_eager=`runlim -t $TIME_LIMIT --output-file=tmp2.log $LAZY_PATH $f --msat`
  lbv2int_res_lazy=`runlim -t $TIME_LIMIT --output-file=tmp2.log $LAZY_PATH --lazy --full-refinement $f`
  lbv2int_res_eager_boolcomp=`runlim -t $TIME_LIMIT --output-file=tmp2.log $LAZY_PATH --use-boolcomp-bvops $f --msat`

  #consistency issues 1
  if [ "$lbv2int_res_eager" != "$lbv2int_res_lazy" ]
  then
    echo $lbv2int_res_lazy
    echo $f FAIL -- eager vs. lazy
  fi

  #consistency issue 2
  if [ "$lbv2int_res_eager" != "$lbv2int_res_eager_boolcomp" ]
  then
    echo $f FAIL -- eager vs. bool_comp
  fi

  #consistency issue 3
  if [ "$lbv2int_res_lazy" != "$lbv2int_res_eager_boolcomp" ]
  then
    echo $f FAIL -- lazy vs. bool_comp
  fi

  #soundness issues 1
  if [ "$cvc4_res" = "sat" -a "$lbv2int_res_eager" = "unsat" ] 
  then
    echo $f FAIL -- saying unsat instead of sat
  fi
  
  #soundness issues 1
  if [ "$cvc4_res" = "unsat" -a "$lbv2int_res_eager" = "sat" ] 
  then
    echo $f FAIL -- saying sat instead of unsat
  fi

  #Assertion failures, run-time exceptions, etc.
  if [ "$lbv2int_res_eager" != "sat" -a "$lbv2int_res_eager" != "unsat" ]
  then
    echo $f $lbv2int_res_eager FAIL -- not saying sat nor unsat. 
  fi
done
echo If you do not see any FAIL above, then you are good.
echo Otherwise, you may have good intentions, but thats about it.
