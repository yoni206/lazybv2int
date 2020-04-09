import sys
import os

def get_lines(path):
    with open(path, "r") as f:
        s = f.read()
        return s.splitlines()

def get_function_name_from_line(line):
    first_space = line.find(" ")
    second_space = line[first_space+1:].find(" ") + first_space
    return line[first_space+1:second_space+1]

def count_symbols(line):
    return line.count("(ite ") + line.count("*") + line.count("+") + line.count("-") + line.count("=")

def choose_best_line(lines):
    stats = {}
    for line in lines:
        stats[line] = count_symbols(line)
    print(stats.values())
    print(min(stats.values()))
    return min(stats, key=stats.get)

def save(d, path):
    with open(path, "w") as f:
        f.write("\n".join([d[k] for k in d]))

if len(sys.argv) < 2:
        print('arg1: path to file with all the results')
        sys.exit(1)
sygus_results_file = sys.argv[1]
lines = get_lines(sygus_results_file)
db = {}
for line in lines:
    function_name = get_function_name_from_line(line)
    if function_name not in db:
        db[function_name] = []
    db[function_name].append(line)

chosen_db = {}

for function_name in db:
    lines = db[function_name]
    line = choose_best_line(lines)
    print(count_symbols(line))
    chosen_db[function_name] = line

save(chosen_db, sygus_results_file + "_chosen.txt")

