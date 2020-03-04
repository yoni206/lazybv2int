import sys
import os

OPS = ["bvand", "bvor", "bvxor", "bvxnor", "bvnand", "bvnor"]
GRANULARITIES = range(1, 9) #actually 1..8
skeleton = """
(set-logic <logic>)
(synth-fun <F> ((s Int) (t Int)) Int
  (
   (Start Int (
     StartCons
     s
     t
     (+ Start Start)
     (- Start  Start)
     <multiplication>
     (ite StartBool Start Start)
   ))
   (StartCons Int ( 
    <constants>
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

def create_sygus_problem_template_for_op_and_granularity(op, granularity):
    result = skeleton.replace("<F>", "int_" + op + "_" + str(granularity))
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






def save_data_to_path(problem, path):
    with open(path, "w") as f:
        f.write(problem)

if len(sys.argv) < 2:
        print('arg1: dir of generated sygus files')
        sys.exit(1)
sygus_problems_dir = sys.argv[1]
os.makedirs(sygus_problems_dir)

for op in OPS:
    for gran in GRANULARITIES:
        problem_template = create_sygus_problem_template_for_op_and_granularity(op, gran)
        nia_template = problem_template.replace("<logic>", "NIA").replace("<multiplication>", "(* Start Start)")
        lia_template = problem_template.replace("<logic>", "LIA").replace("<multiplication>", "(* StartCons Start)")

        problem_nia_explicit_constants = nia_template.replace("<constants>", "\n".join([str(x) for x in get_constants_up_to(gran)]))
        problem_nia_zero_one_constants = nia_template.replace("<constants>", "0\n1")
        problem_nia_builtin_constants = nia_template.replace("<constants>", "(Constant Int)")

        problem_lia_explicit_constants = lia_template.replace("<constants>", "\n".join([str(x) for x in get_constants_up_to(gran)]))
        problem_lia_zero_one_constants = lia_template.replace("<constants>", "0\n1")
        problem_lia_builtin_constants = lia_template.replace("<constants>", "(Constant Int)")

        path = sygus_problems_dir + "/" + op + "_" + str(gran) + "_nia_explicit" +  ".sy"
        save_data_to_path(problem_nia_explicit_constants, path)

        path = sygus_problems_dir + "/" + op + "_" + str(gran) + "_nia_zero_one" +  ".sy"
        save_data_to_path(problem_nia_zero_one_constants, path)

        path = sygus_problems_dir + "/" + op + "_" + str(gran) + "_nia_builtin" +  ".sy"
        save_data_to_path(problem_nia_builtin_constants, path)

        path = sygus_problems_dir + "/" + op + "_" + str(gran) + "_lia_explicit" +  ".sy"
        save_data_to_path(problem_lia_explicit_constants, path)

        path = sygus_problems_dir + "/" + op + "_" + str(gran) + "_lia_zero_one" +  ".sy"
        save_data_to_path(problem_lia_zero_one_constants, path)

        path = sygus_problems_dir + "/" + op + "_" + str(gran) + "_lia_builtin" +  ".sy"
        save_data_to_path(problem_lia_builtin_constants, path)

