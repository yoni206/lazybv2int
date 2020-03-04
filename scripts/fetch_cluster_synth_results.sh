#!/bin/bash
ssh barrett2 grep -r --no-filename define.fun /barrett/scratch/yoniz/lazy-bv-to-int/cluster_results* |sort > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/functions.txt 
