#!/bin/bash
cd scripts
mkdir ../bw-op-synth/cpp
./smtlib2cvc4.sh ../bw-op-synth/sygus_results/functions.txt > ../bw-op-synth/cpp/bw_functions.cpp
echo "#include \"bw_functions.h\"" > tmp
cat ../bw-op-synth/cpp/bw_functions.cpp > tmp
cat tmp > ../bw-op-synth/cpp/bw_functions.cpp
rm tmp
echo "#include \"expr/node.h\"" > ../bw-op-synth/cpp/bw_functions.h
echo "using namespace CVC4;" > ../bw-op-synth/cpp/bw_functions.h
grep ^Node ../bw-op-synth/cpp/bw_functions.cpp |sort | sed 's/$/;/g'>> ../bw-op-synth/cpp/bw_functions.h
cd ..
