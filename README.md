# Welcome
Welcome to lazybv2int. It is an SMT-solver for the thory
of bit-vectors and uninterpreted functions.

It is based on a translation of the input problem into an equisatisfiable problem over the theory of integer arithmetic and uninterpreted functions.
There are several variants of this translation, all activated with various options that are described in the tool's help (see below).

Incremental solving is supported.

The tool uses [mathsat](https://mathsat.fbk.eu/) to parse the input problem and [cvc4](https://cvc4.github.io/) to solve the arithmetic translations.

# Install
To build with mathsat (which is currently required for parsing SMT-LIB), you must obtain the MathSAT libraries yourself. You are responsible for ensuring that you meet the conditions of the MathSAT license. Please download the mathsat distribution, unpack the compressed directory and move it to `./deps/mathsat` (create `deps` directory if it does not exist). 
After that, you should be able to do the following:
```
$ cd <repo-path>/deps
$ ls
CREDITS.txt  LICENSE.txt  README.txt  bin  configurations  examples  gpl-3.0.txt  include  java  lgpl-3.0.txt  lib  python
```

Then, run the following commands:
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
