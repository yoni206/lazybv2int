import sys
import re
import os

if len(sys.argv) < 3:
    print("arg1: path to dir with all the relevant smtlib problems")
    print("arg2: path to file with filtered paths")
    sys.exit(1)
smtlib_problems_dir = sys.argv[1]
output_file = sys.argv[2]
