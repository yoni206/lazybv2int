# Welcome
Welcome to lazybv2int. It is an SMT-solver for the thory
of bit-vectors and uninterpreted functions.

It is based on a translation of the input problem into an equisatisfiable problem over the theory of integer arithmetic and uninterpreted functions.
There are several variants of this translation, all activated with various options that are described in the tool's help (see below).

Incremental solving is supported.

The tool uses [mathsat](https://mathsat.fbk.eu/) to parse the input problem and [cvc4](https://cvc4.github.io/) to solve the arithmetic translations.

# Install
```
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
