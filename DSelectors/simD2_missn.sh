
#!/usr/bin/env bash

TREENAME=gd_pippimprotmissn__F4_B4_T2_S4_Tree
DSELECTOR=/work/halld2/home/psharp/rho0script_repo/DSelectors/1p_DS/DS_1p_0cuts.C
NTHREADS=32

INPUTFILE=/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_D2/0bg/root/trees/tree_gd_pippimprotmissn__F4_B4_T2_S4_gen_gcf_090207_*.root
    
root -q -b 'Run_Selector.C("'${INPUTFILE}'","'${TREENAME}'","'${DSELECTOR}'",'${NTHREADS}')'

mv output.root /work/halld2/home/psharp/simulation/output/geant_gcf/0cuts_study/flattree_D2_1p_missn_AV18.root