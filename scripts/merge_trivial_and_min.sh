#!/bin/bash
cat /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/all_functions.txt_chosen.txt | sed 's/ ((s Int/_min ((s Int/g' > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt
echo >> /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt
cat /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/trivial_functions.txt | sed 's/ ((s Int/_trivial ((s Int/g' >> /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt
cat /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt | sort > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt.tmp
mv /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt.tmp /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt
