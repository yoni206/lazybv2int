import sys
import os
import get_sygus_problem_for_bw_op_and_gran as get_syg

OPS = ["bvand", "bvor", "bvxor", "bvxnor", "bvnand", "bvnor"]
GRANULARITIES = range(1, 9) #actually 1..8



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
        problem = get_syg.create_sygus_problem_for_op_and_granularity(op, gran)
        filename = op + "_" + str(gran) + ".sy"
        path = sygus_problems_dir + "/" + filename
        save_data_to_path(problem, path)


