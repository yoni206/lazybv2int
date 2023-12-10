# Welcome
Welcome to lazybv2int. It is an SMT-solver for the theory
of bit-vectors and uninterpreted functions.

lazybv2int is based on a translation of the input problem into an equisatisfiable problem over the theory of integer arithmetic and uninterpreted functions.
There are several variants of this translation, all activated with various options that are described in the tool's help (see below).

Incremental solving is supported.

The tool is built on top of [smt-switch](https://github.com/stanford-centaur/smt-switch). 
It uses [mathsat](https://mathsat.fbk.eu/) to parse the input problem and [cvc4](https://cvc4.github.io/) to solve the arithmetic translations.

A description of lazybv2int is available [here](https://github.com/yoni206/lazybv2int/blob/master/smtcomp-2020.pdf).

The tool is an early prototype. Currently, the technique is implemented as part of [cvc5](https://github.com/cvc5/cvc5), and is
described in:
[Bit-precise reasoning via Int-blasting](https://u.cs.biu.ac.il/~zoharyo1/vmcai22.pdf)

# Install
```
# make sure you meet all the license requirements to use mathsat
./contrib/setup-msat.sh

./contrib/setup-smt-switch.sh
./configure.sh
cd build
make
```

# Use
From `build` do:
```
./lazybv2int <smtlib-file>
```
or
```
./lazybv2int -h
```
to see possible options.
