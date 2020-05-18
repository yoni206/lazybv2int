# Install
To build with mathsat (which is currently required for parsing SMT-LIB), you must obtain the MathSAT libraries yourself. You are responsible for ensuring that you meet the conditions of the MathSAT license. Please download the mathsat distribution, unpack the compressed directory and move it to `./deps/mathsat`. Then, run the following commands:
```
./contrib/setup-smt-switch.sh
./configure.sh
cd build
make
```

#Use
From `build` do:
```
./lazybv2int <smtlib-file>
```
or
```
./lazybv2int -h
```
to see possible options.
