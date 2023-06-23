#$!/bin/bash
echo "Chose a potential: AV18, N2L0, or AV4. And then a target: C12, He4, D2"


if [ $# -eq 0 ];
then
		echo "$0: Missing arguments"
		exit 1
elif [$# -gt 2];
then
		echo "$0: Too many arguments: $@"
		exit 1
else
		echo "Running potential $1 over target $2"
fi

potential=$1
target=$2
p=$3
		
for p in {0..9}
do
		root -l -b -q /work/halld2/home/psharp/analysis/rho0script_repo/gcf/pp2p_gcf.c\(\"/volatile/halld/home/psharp/simulation/gcf_sim_slurm/$1_$2/genoutput_${p}.root\",\"/work/halld2/home/psharp/analysis/simulation/gcf_sim/8GeV/$1_$2/rho0_${p}_analyzed.root\"\)
done

#hadd /work/halld2/home/psharp/gcf_sim/AV4_C12/histsall.root /work/halld2/home/psharp/gcf_sim/AV4_C12/rho_*_analyzed.root
echo "done with ${target}, ${potential}, number ${p} "
