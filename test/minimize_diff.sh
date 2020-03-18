#!/bin/sh
MY_DIR="`dirname \"$0\"`"
MY_DIR=`realpath $MY_DIR`
DDSMT_PATH=$MY_DIR/../deps/ddSMT/ddsmt.py
RUNNING_SCRIPT_PATH=$MY_DIR/compare_script_for_ddsmt.sh
f=$1

$DDSMT_PATH -v --match-out different $f $f.minimized.smt2 $RUNNING_SCRIPT_PATH
