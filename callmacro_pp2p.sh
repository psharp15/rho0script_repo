

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

		
for p in 0 #1 2 3 4
do
		root -l -b -q /work/halld2/home/psharp/rho0analysis/rhoscript_repo/ppvsp_rho0.c\(\"/volatile/halld/home/psharp/gcf_sim_slurm/$1_$2/genoutput_${p}.root\",\"/work/halld2/home/psharp/gcf_sim/$1_$2/rho0_${p}_analyzed.root\",\"/work/halld2/home/psharp/gcf_sim/$1_$2/rho0_${p}_pp2p.txt\"\)
done

#hadd /work/halld2/home/psharp/gcf_sim/AV4_C12/histsall.root /work/halld2/home/psharp/gcf_sim/AV4_C12/rho_*_analyzed.root
echo alldone
