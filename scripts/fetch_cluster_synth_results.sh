#!/bin/bash
ssh barrett2 grep -r -m 1 --no-filename --include="*nia*"  define.fun /barrett/scratch/yoniz/lazy-bv-to-int/sygus/cluster_results_* |sort|uniq > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/nia_functions.txt 
ssh barrett2 grep -r -m 1 --no-filename --include="*lia*"  define.fun /barrett/scratch/yoniz/lazy-bv-to-int/sygus/cluster_results_* |sort|uniq > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/lia_functions.txt 
ssh barrett2 grep -r -m 1 --no-filename --include="*relational*"  define.fun /barrett/scratch/yoniz/lazy-bv-to-int/sygus/cluster_results_* |sort|uniq > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/relational_functions.txt 
#ssh barrett2 grep -r --no-filename define.fun /barrett/scratch/yoniz/lazy-bv-to-int/sygus/cluster_results* |sort|uniq > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/all_functions.txt 
#ssh barrett2 grep -r -m 1 --no-filename --include="*trivial*"  define.fun /barrett/scratch/yoniz/lazy-bv-to-int/sygus/cluster_results_pbe |sort|uniq > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/trivial_functions.txt 
