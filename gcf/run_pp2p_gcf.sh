

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

p=$3

		
for p in 0 #1 2 3 4
do
		root -l -b -q /work/halld2/home/psharp/analysis/rho0script_repo/gcf/pp2p_gcf.c\(\"/volatile/halld/home/psharp/simulation/gcf_sim_slurm/$1_$2/genoutput_${p}.root\",\"/work/halld2/home/psharp/analysis/simulation/gcf_sim/tesst/$1_$2/rho0_${p}_analyzed.root\"\)
done

#hadd /work/halld2/home/psharp/gcf_sim/AV4_C12/histsall.root /work/halld2/home/psharp/gcf_sim/AV4_C12/rho_*_analyzed.root
echo alldone
