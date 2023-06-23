
#!/usr/bin/env bash

TREENAME=gc12_pippimprotprotinc__F4_B4_Tree
DSELECTOR=/work/halld2/home/psharp/rho0script_repo/DSelectors/2p_DS/DS_2p_0cuts.C
NTHREADS=32

INPUTFILE=/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_C12/0bg/root/trees/tree_gc12_pippimprotprotinc__F4_B4_gen_gcf_090306_*.root
    
root -q -b 'Run_Selector.C("'${INPUTFILE}'","'${TREENAME}'","'${DSELECTOR}'",'${NTHREADS}')'

mv output.root /work/halld2/home/psharp/simulation/output/geant_gcf/0cuts_study/flattree_C12_2p_inc_AV18.root


INPUTFILE=/volatile/halld/home/psharp/simulation/halld_sim_swif/AV4_C12/0bg/root/trees/tree_gc12_pippimprotprotinc__F4_B4_gen_gcf_090306_*.root
    
root -q -b 'Run_Selector.C("'${INPUTFILE}'","'${TREENAME}'","'${DSELECTOR}'",'${NTHREADS}')'

mv output.root /work/halld2/home/psharp/simulation/output/geant_gcf/0cuts_study/flattree_C12_2p_inc_AV4.root


INPUTFILE=/volatile/halld/home/psharp/simulation/halld_sim_swif/N2LO_C12/0bg/root/trees/tree_gc12_pippimprotprotinc__F4_B4_gen_gcf_090306_*.root
    
root -q -b 'Run_Selector.C("'${INPUTFILE}'","'${TREENAME}'","'${DSELECTOR}'",'${NTHREADS}')'

mv output.root /work/halld2/home/psharp/simulation/output/geant_gcf/0cuts_study/flattree_C12_2p_inc_N2LO.root

