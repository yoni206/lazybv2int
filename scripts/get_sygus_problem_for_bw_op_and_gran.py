import sys
import os

skeleton = """
(set-logic NIA)
(synth-fun <F> ((s Int) (t Int)) Int
  (
   (Start Int (
     s
     t
     <constants>
     (+ Start Start)
     (- Start  Start)
     (* Start Start)
     (ite StartBool Start Start)
   ))
(StartBool Bool (
     (= Start Start)
     (>= Start Start)
     (not StartBool)
   ))
))
<constraints>
(check-synth)
"""

def create_sygus_problem_for_op_and_granularity(op, granularity):
    result = skeleton.replace("<F>", "int_" + op + "_" + str(granularity))
    result = result.replace("<constants>", "\n".join([str(x) for x in get_constants_up_to(granularity)]))
    result = result.replace("<constraints>", "\n".join(get_constraints_for_op_and_granularity(op, granularity)))
    return result

def get_constants_up_to(n):
    return range(0, (2 ** n))

def get_constraints_for_op_and_granularity(op, granularity):
    constraints= []
    for i in range(0, 2 ** granularity):
        for j in range(0, 2 ** granularity):
            eval = evaluate(op, i, j)
            constraint = "(constraint (= " + "(int_" + op + "_" + str(granularity)  + " " + str(i) + " " + str(j) + ") " + str(eval) + "))"
            constraints.append(str(constraint))
    return constraints

def evaluate(op, x, y):
    if op == "bvand":
        return x & y
    elif op == "bvor":
        return x|y
    elif op == "bvxor":
        return x^y
    elif op == "bvxnor":
        return (x|~y)&(~x|y)
    elif op == "bvnand":
        return ~(x&y)
    elif op == "bvnor":
        return ~(x|y)



if __name__ == "__main__":
    if len(sys.argv) < 3:
        print('arg1: op\narg2: granularity')
        sys.exit(1)
    op = sys.argv[1]
    granularity = int(sys.argv[2])
    sygus_problem = create_sygus_problem_for_op_and_granularity(op, granularity)
    print(sygus_problem)
