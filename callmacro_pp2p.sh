echo "Chose a potential: AV18, N2L0, or AV4. And then a target: C12, He4, D2"

if [ $# -lt 2 ];
then
		echo "$0: Not enough arguements: $@"
		exit 1
elif [$# -gt 2];
then
		echo "$0: Too many arguments: $@"
		exit 1
else
		echo "Running potential $2 over target $3"
fi

p=$1
potential=$2
target=$3	

	
for p in 0 1 2 3 4
do
		root -l -b -q /work/halld2/home/psharp/rho0analysis/rhoscript_repo/ppvsp_rho0.c\(\"/volatile/halld/home/psharp/simulation/gcf_sim_slurm/confirm/${potential}_${target}/genoutput_${p}.root\",\"/work/halld2/home/psharp/analysis/gcf_sim/confirm/${potential}_${target}/rho0_${p}_analyzed.root\",\"/work/halld2/home/psharp/analysis/gcf_sim/confirm/${potential}_${target}/rho0_${p}_pp2p.txt\"\)
done

hadd -f /work/halld2/home/psharp/analysis/gcf_sim/confirm/${potential}_${target}/histsall_${potential}_${target}.root /work/halld2/home/psharp/analysis/gcf_sim/confirm/${potential}_${target}/rho0_*_analyzed.root
echo alldone
