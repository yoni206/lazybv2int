#!/bin/sh
#Change full paths yourself. I am too lazy for a general script.

CVC4_PATH=/home/yoniz/git/lazybv2int/deps/smt-switch/deps/CVC4/build/bin/cvc4
LAZY_PATH=/home/yoniz/git/lazybv2int/build/lazybv2int
f=$1

#store the result of cvc4
cvc4_res=`$CVC4_PATH $f`

#store the result of bv2int. Change this line to invoke different options.
lbv2int_res=`$LAZY_PATH $f --lazy --full-refinement`

if [ "$lbv2int_res" = "sat" -a "$cvc4_res" = "unsat" ]
then
  echo different
  return 1
fi

if [ "$lbv2int_res" = "unsat" -a "$cvc4_res" = "sat" ]
then
  echo different
  return 1
fi
echo same
return 0
