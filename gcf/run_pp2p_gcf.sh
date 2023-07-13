#$!/bin/bash

potential=$1
target=$2
p=$3
		

root -l -b -q /work/halld2/home/psharp/rho0script_repo/gcf/pp2p_gcf.c\(\"/volatile/halld/home/psharp/simulation/gcf_raw/8GeV/$1_$2/genoutput_${p}.root\",\"/work/halld2/home/psharp/simulation/output/gcf_raw/8GeV/$1_$2/rho0_${p}_analyzed.root\"\)

echo "done with ${target}, ${potential}, number ${p} "

