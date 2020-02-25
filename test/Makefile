all:
	$(CXX) -o test1 -Wl,-rpath,../deps/smt-switch/local/lib/ -I../src -I../deps/smt-switch/local/include -L../deps/smt-switch/local/lib test1.cpp ../src/bv2int.cpp ../src/lbv2isolver.cpp ../src/preprocessor.cpp ../src/smtlibsolver.cpp -lsmt-switch -lsmt-switch-msat
	./test1
