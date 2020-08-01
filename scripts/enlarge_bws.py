import sys
import re
import os
from pathlib import Path
import filter_smtlib as fs

PATTERN = re.compile('\(_ bv(\d+) \d+\)')
MAX_BW=1024

def do_replacements(content, bw, new_bw):
    assert(new_bw >= bw)
    result = content
    result = result.replace("(_ BitVec " + str(bw), "(_ BitVec " + str(new_bw))
    result = re.sub(PATTERN, r'(_ bv\1 ' + str(bw) + ')', result)
    return result




if len(sys.argv) < 3:
    print("arg1: file with list of relevant paths")
    print("arg2: dir to put all files in")
    sys.exit(1)
full_paths_file = sys.argv[1]
output_dir = sys.argv[2]
with open(full_paths_file, "r") as f:
    paths = f.readlines()
for path in paths:
    path = path.strip()
    begin = path.find("QF_")
    path_suffix = path[begin:]
    dir_of_all_bws = output_dir + "/" + path_suffix
    dir_of_all_bws_path = Path(dir_of_all_bws)
    dir_of_all_bws_path.mkdir(parents=True)
    with open(path, "r") as fi:
        content = "".join(fi.readlines())
    bws = fs.get_bitwidths(content)
    assert(len(bws) == 1)
    bw = list(bws)[0]
    new_bw = bw
    while new_bw <= MAX_BW:
        filename = str(new_bw) + ".smt2"
        new_path = dir_of_all_bws + "/" + filename
        new_content = do_replacements(content, bw, new_bw)
        with open(new_path, "w") as f:
            f.write(new_content)
        new_bw *= 2

