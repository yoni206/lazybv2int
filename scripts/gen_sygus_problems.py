import sys
import os

OPS = ["bvand", "bvor", "bvxor"]
GRANULARITIES = range(1, 9) #actually 1..8

skeleton = """
(set-logic <logic>)
(synth-fun <F> ((s Int) (t Int)) Int
(
  (I Int) (Ic Int) (B Bool)
)
(
  (I Int  (
       Ic
       (+ I I )
       <multiplication>
       (ite B I I)
    )
  )
  (Ic Int (
  s
  t
    <constants>
  )
)
  (B Bool (
       (= I I)
       (>= I I)
       (not B)
     )
  )
)
)

(declare-var s Int)
(declare-var t Int)

(constraint (=> (and (<= 0 s <max>) (<= 0 t <max>)) (= (int_bvand_<gran> s t) (bv2nat (bvand ((_ int2bv <gran>) s) ((_ int2bv <gran>) t))) )))
(check-synth)
"""

def create_sygus_problem_template_for_op_and_granularity(op, granularity):
    result = skeleton.replace("<F>", "int_" + op + "_" + str(granularity))
    result = result.replace("<max>", str(2**granularity - 1))
    result = result.replace("<gran>", str(granularity))
    return result

def get_constants_up_to(n):
    return range(0, (2 ** n))

def get_constraints_for_op_and_granularity(op, granularity):
    constraint = "(constraint" 
    constraints= []
    for i in range(0, 2 ** granularity):
        for j in range(0, 2 ** granularity):
            eval = evaluate(op, i, j,granularity)
            constraint = "(constraint (= " + "(int_" + op + "_" + str(granularity)  + " " + str(i) + " " + str(j) + ") " + str(eval) + "))"
            constraints.append(str(constraint))
    return constraints

def bvnot(x, k):
    return 2**k - 1 - x


def evaluate(op, x, y, k):
    if op == "bvand":
        return x & y
    elif op == "bvor":
        return x|y
    elif op == "bvxor":
        return x^y

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
        nia_template = problem_template.replace("<logic>", "BVNIA").replace("<multiplication>", "(* I I)")
        lia_template = problem_template.replace("<logic>", "BVLIA").replace("<multiplication>", "(* Ic I)")

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

