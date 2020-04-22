#!/bin/bash
MY_DIR="`dirname \"$0\"`"
MY_DIR=`realpath $MY_DIR`
echo $MY_DIR
SOL_DIR=$MY_DIR/../../ethereum/yoni206/solidity/test/formal
rm $SOL_DIR/smtlib/*
cd $SOL_DIR
for f in `ls|grep \.py | grep -v util.py | grep -v pycache | grep -v rule.py | grep -v opcodes.py | grep -v sub_not_zero_x_to_not_x_256.py`; do
  python3 $f;
done
rm $MY_DIR/../solidity/*
cp $SOL_DIR/smtlib/* $MY_DIR/../solidity/
