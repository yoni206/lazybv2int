import sys
import re
import os

log = []

def smtlib_file(f):
    return f.endswith(".smt2")

def get_bitwidths(content):
    bitvec_consts_widths = get_bv_consts_widths(content)
    bitvec_types_widths = get_bv_types_widths(content)
    all_widths = set([])
    all_widths.update(bitvec_consts_widths)
    all_widths.update(bitvec_types_widths)
    return all_widths

#returns a set. If (_ BitVec n) is in content, n is in the set.
def get_bv_types_widths(content):
    result = set([])
    bv_type_exprs = get_bv_type_exprs(content)
    for expr in bv_type_exprs:
        n = get_width(expr)
        result.add(n)
    return result

#returns a list of all (_ BitVec n) in the content
def get_bv_type_exprs(content):
    result = set([])
    p = re.compile('\(_ BitVec \d+\)')
    all_matches = p.findall(content)
    result.update(all_matches)
    return result

#returns a set. If (_ bv* n) is in content, n is in the set
def get_bv_consts_widths(content):
    result = set([])
    bv_const_exprs = get_bv_const_exprs(content)
    for expr in bv_const_exprs:
        n = get_width(expr)
        result.add(n)
    return result

#returns a list of all (_ bv* n) in the content
def get_bv_const_exprs(content):
    result = set([])
    p = re.compile('\(_ bv\d+ \d+\)')
    all_matches = p.findall(content)
    result.update(all_matches)
    return result

def get_width(expr):
    #for (_ bv22 300) returns 7.
    #for (_ BitVec22 300) returns 12.
    #This is just the indnex of the second space
    index_of_first_space_after_bv = find_2nd(expr, " ")
    index_of_closing_paren = len(expr)-1
    width_as_str = expr[index_of_first_space_after_bv:index_of_closing_paren]
    width = int(width_as_str)
    return width

def find_2nd(string, substring):
   return string.find(substring, string.find(substring) + 1)

def has_concat(content):
    return "(concat " in content

def has_extract(content):
    return "(_ extract " in content

def has_z_extend(content):
    return "(zero_extend " in content

def has_s_extend(content):
    return "(sign_extend " in content

def all_constants_zero_or_one(content):
    constants_exprs = get_bv_const_exprs(content)
    for expr in constants_exprs:
        if "(_ bv0 " in expr:
            continue
        if "(_ bv1 " in expr:
            continue
        return False
    return True

def filter_paths(full_paths):
    res = set([])
    for f in full_paths:
        add = True
        logline = ""
        logline += f + ":"
        #only *.smt2 files
        if not smtlib_file(f):
            continue

        with open(f, "r") as fi:
            content = "".join(fi.readlines())

        #only one bitwidths, or two, if one of them is 1
        bitwidths = get_bitwidths(content)
        if len(bitwidths) > 2:
            logline += ":more_than_2_bws"
            add = False
        if len(bitwidths) == 2:
            if 1 not in bitwidths:
                logline += ":2_bws_without_1"
                add = False

        #constants must be 0 or 1
        if not all_constants_zero_or_one(content):
            logline += ":cons_other_than_0_1"
            add = False

        #no concat, no extract, no extend
        if has_concat(content):
            logline += ":has_concat"
            add = False
        if has_extract(content):
            logline += ":has_extract"
            add = False
        if has_z_extend(content):
            logline += ":has_z_extend"
            add = False
        if has_s_extend(content):
            logline += ":has_s_extand"
            add = False

        if add:
            res.add(f)
        else:
            log.append(logline)
    with open("filter.log", "w") as f:
        f.write("\n".join(log))
    return res


if len(sys.argv) < 3:
    print("arg1: path to dir with all the relevant smtlib problems")
    print("arg2: path to file with filtered paths")
    sys.exit(1)
smtlib_problems_dir = sys.argv[1]
output_file = sys.argv[2]
full_paths=set([])
for currentpath, folders, files in os.walk(smtlib_problems_dir):
    files = [f for f in files if not f[0] == '.']
    folders[:] = [d for d in folders if not d[0] == '.']
    for f in files:
        rel_path = os.path.join(currentpath, f)
        full_path = os.path.abspath(rel_path)
        full_paths.add(full_path)
full_paths = list(full_paths)
full_paths.sort()

filtered_paths = filter_paths(full_paths)
filtered_paths = list(filtered_paths)
filtered_paths.sort()
with open(output_file, "w") as f:
    f.write("\n".join(filtered_paths))

