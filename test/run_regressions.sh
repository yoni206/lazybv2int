#!/bin/bash
MY_DIR="`dirname \"$0\"`"
MY_DIR=`realpath $MY_DIR`
CVC4_PATH=$MY_DIR/../deps/smt-switch/deps/CVC4/build/bin/cvc4
LAZY_PATH=$MY_DIR/../build/lazybv2int
SMTLIB_FILES_DIR=$MY_DIR/smtlib_files

for f in `find $SMTLIB_FILES_DIR -name "*.smt2"`
do
  cvc4_res=`runlim -t 1 --output-file=tmp1.log $CVC4_PATH $f`
  lazy_res=`runlim -t 1 --output-file=tmp2.log $LAZY_PATH $f`
  if [ "$cvc4_res" = "sat" -a "$lazy_res" = "unsat" ] 
  then
    echo $f FAIL
#  else
#    echo $f PASS
  fi
  
  if [ "$cvc4_res" = "unsat" -a "$lazy_res" = "sat" ] 
  then
    echo $f FAIL
#  else
#    echo $f PASS
  fi

  if [ "$lazy_res" != "sat" -a "$lazy_res" != "unsat" ]
  then
    echo $f $lazy_res FAIL
  fi
done
echo If you do not see any FAIL above, then you are good.
