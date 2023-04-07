#$!/bin/bash
#echo "Chose a potential: AV18, N2L0, or AV4. And then a target: C12, He4, D2"

#if [ $# -lt 2 ];
#then
#		echo "$0: Not enough arguements: $@"
#		exit 1
#elif [$# -gt 2];
#then
#		echo "$0: Too many arguments: $@"
#		exit 1
#else
#		echo "Running potential $2 over target $3"
#fi

#p=$1
potential=$1
target=$2

	
for p in {000..000}
do
		root -l -b -q /work/halld2/home/psharp/analysis/rhoscript_repo/pp2p_throwntrees.c\(\"/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_C12/0bg/root/thrown/tree_thrown_gen_gcf_090306_${p}.root\",\"/work/halld2/home/psharp/analysis/simulation/thrown/rho0_${p}_analyzed_C12_TEST.root\"\)
#		root -l -b -q /work/halld2/home/psharp/analysis/rhoscript_repo/pp2p_throwntrees.c\(\"/volatile/halld/home/psharp/simulation/halld_sim_swif/$potential$_${target}/0bg/root/thrown/tree_thrown_gen_gcf_090306_499.root\",\"/volatile/halld/home/psharp/simulation/halld_sim_swif/$potential$_${target}/rho0_${p}_analyzed.root\",\"/w/halld-scshelf2101/halld2/home/psharp/analysis/halld_gcf_sim/testrho0_${p}_pp2p.txt\"\)

#echo $p
done

#hadd -f /work/halld2/home/psharp/gcf_sim/${potential}_${target}/histsall_${potential}_${target}.root /work/halld2/home/psharp/gcf_sim/${potential}_${target}/rho0_*_analyzed.root
echo alldone
