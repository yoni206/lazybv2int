## Overview
* `lazybv2int` is an SMT-solver for QF_BV and QF_UFBV, both incremental and non-incremental.
* It is implemented in c++, on top of smt-switch
* The backend solvers are cvc4 and mathsat
* We use CVC4's UFNIA solver
* We use mathsat's UFNIA solver + parser

## So Far
* Tool is working
* no errors on 2019 QF_BV incremental/non-incremental 5min timeouts
* also no discrepencies
* Contribution improves for virtual timeout of 1 sec in non-incremental

## Need to improve the performance
* Performence is not amazing (we were focusing on the correctness -- now working on performance tricks)
* Not a lot of contribution to virtual best solver w.r.t. 2019 winners


## Techniques
* notation: x[i] = x div 2^i mod 2
* (bvand x y) ---> fbvand(k, x, y)

### Eager Techniques
* eager sum mode: fbvand(k,x,y) = min(x[0],y[0])*2^0 + ... + min(x[k-1],y[k-1]*2{k-1}
* eager comp mode: fbvand(k,x,y)[0] = min(x[0],y[0]) /\ ... /\ fbvand(k,x,y)[k-1] = min(x[k-1], y[k-1])
* granularities 1 -- 4. Above is 1.
* example for sum mode in granularity 2: 
* fbvand(k,x,y) = INTBVNAD_2(x[1:0], y[1:0])*2^{0}+ ... + INTBVAND_2(x[k-1:k-2], y[k-1:k-2])

|x | y | INTBVAND_2(x,y)| 
|--|---|----------------|
|0 | 0 |       0
|0 | 1 |       0
|0 | 2 |       0
|0 | 3 |       0
|1 | 0 |       0
|1 | 1 |       1
|1 | 2 |       0
|1 | 3 |       1
|2 | 0 |       0
|2 | 1 |       0
|2 | 2 |       1
|2 | 3 |       2
|3 | 0 |       0
|3 | 1 |       1
|3 | 2 |       2
|3 | 3 |       3

But sygus finds shorter representations.

### Lazy Techniques
* lazy mode: start with some axioms about bvand, and lazylly expand the sum/comparisons:
  * f(k,x,y) >= 000...0[-] /\ f(k,x,y) <=[-]1111...1
  * f(k,x,y) >= 000...[--] /\ f(k,x,y) <= [--]11...1
  ...
  *f(k,x,y) >= [---------] /\ f(k,x,y) <= [--------]
* lazy granularity: how fast to do these steps

## TODO
* lazy shift operator
* better spuriousness check
* under-approximate SAT check

## What can be reported in a paper?
* SMTLIB QF_BV - not a lot of contribution
* trying to get blockchain benchmars from ethereum, but.... who knows
* cosa-2?
* sygus benchmarks and results, sizes of generated functions
* sygus is interesting but does not seem to be very useful...

## SMT-COMP
* We plan to submit it to SMT-COMP QF_BV incremental+non-incremental

## License
* we want BSD 3
* we use mathsat:
  * parsing
  * solving
* current solution: use mathsat license

