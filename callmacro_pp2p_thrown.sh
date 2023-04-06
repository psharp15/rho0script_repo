#$!/bin/bash
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
		echo "Running potential $1 over target $2"
fi

#p=$1
potential=$1
target=$2

	
for p in {000..100}
do
#CARBON
		root -l -b -q /work/halld2/home/psharp/analysis/rhoscript_repo/pp2p_throwntrees.c\(\"/volatile/halld/home/psharp/simulation/halld_sim_swif/${potential}_${target}/0bg/root/thrown/tree_thrown_gen_gcf_090306_${p}.root\",\"/volatile/halld/home/psharp/simulation/halld_sim_swif/${potential}_${target}/thrown/rho0_${p}_analyzed.root\"\)
echo "done with tree_thrown_gen_gcf_090306_${p}.root"
#		root -l -b -q /work/halld2/home/psharp/analysis/rhoscript_repo/pp2p_throwntrees.c\(\"/volatile/halld/home/psharp/simulation/halld_sim_swif/${potential}_${target}/0bg/root/thrown/tree_thrown_gen_gcf_090306_${p}.root\",\"/work/halld2/home/psharp/analysis/halld_gcf_sim/rho0_${p}_analyzed_TEST_${potential}_${target}.root\"\)
#		root -l -b -q /work/halld2/home/psharp/analysis/rhoscript_repo/pp2p_throwntrees.c\(\"/volatile/halld/home/psharp/simulation/halld_sim_swif/$potential$_${target}/0bg/root/thrown/tree_thrown_gen_gcf_090306_499.root\",\"/volatile/halld/home/psharp/simulation/halld_sim_swif/$potential$_${target}/rho0_${p}_analyzed.root\",\"/w/halld-scshelf2101/halld2/home/psharp/analysis/halld_gcf_sim/testrho0_${p}_pp2p.txt\"\)

#HELIUM
#		root -l -b -q /work/halld2/home/psharp/analysis/rhoscript_repo/pp2p_throwntrees.c\(\"/volatile/halld/home/psharp/simulation/halld_sim_swif/${potential}_${target}/0bg/root/thrown/tree_thrown_gen_gcf_090091_${p}.root\",\"/volatile/halld/home/psharp/simulation/halld_sim_swif/${potential}_${target}/rho0_${p}_analyzed.root\"\)
#echo "done with tree_thrown_gen_gcf_090091_${p}.root"

#DEUTERIUM
#		root -l -b -q /work/halld2/home/psharp/analysis/rhoscript_repo/pp2p_throwntrees.c\(\"/volatile/halld/home/psharp/simulation/halld_sim_swif/${potential}_${target}/0bg/root/thrown/tree_thrown_gen_gcf_090207_${p}.root\",\"/volatile/halld/home/psharp/simulation/halld_sim_swif/${potential}_${target}/rho0_${p}_analyzed.root\"\)
#echo "done with tree_thrown_gen_gcf_090207_${p}.root"
done

#hadd -f /work/halld2/home/psharp/gcf_sim/${potential}_${target}/histsall_${potential}_${target}.root /work/halld2/home/psharp/gcf_sim/${potential}_${target}/rho0_*_analyzed.root
echo alldone 
