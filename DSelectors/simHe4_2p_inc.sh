
#!/usr/bin/env bash

TREENAME=ghe_pippimprotprotinc__F4_B4_T2_S4_Tree
DSELECTOR=/work/halld2/home/psharp/rho0script_repo/DSelectors/2p_DS/DS_2p_0cuts.C
NTHREADS=32

INPUTFILE=/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_He4/0bg/root/trees/tree_ghe_pippimprotprotinc__F4_B4_T2_S4_gen_gcf_090091_*.root
    
root -q -b 'Run_Selector.C("'${INPUTFILE}'","'${TREENAME}'","'${DSELECTOR}'",'${NTHREADS}')'

mv output.root /work/halld2/home/psharp/simulation/output/geant_gcf/0cuts_study/flattree_He4_2p_inc_AV18.root

#INPUTFILE=/work/halld2/home/jrpybus/analysis/jpsi/simulation/output/SRC_CT/root/trees/tree_ghe_epemprotinc__B4_F4_T1_S2_gen_gcf_SRC_*.root

#root -q -b 'Run_Selector.C("'${INPUTFILE}'","'${TREENAME}'","'${DSELECTOR}'",'${NTHREADS}')'

#mv e_e_p_X.root /work/halld2/home/jrpybus/analysis/jpsi/analysis/trees/DSelector/sim/SRC_CT/tree_DSelector_SRC.root


