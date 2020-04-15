#!/bin/bash
cat /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/nia_functions.txt_chosen.txt | sed 's/ ((s Int/_nia ((s Int/g' > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt
echo >> /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt

cat /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/lia_functions.txt_chosen.txt | sed 's/ ((s Int/_lia ((s Int/g' >> /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt
echo >> /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt

cat /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/relational_functions.txt_chosen.txt | sed 's/ ((s Int/_relational ((s Int/g' >> /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt

cat /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt | sort > /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt.tmp
mv /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt.tmp /home/yoniz/git/lazybv2int/bw-op-synth/sygus_results/merged_functions.txt
