

INPUTFILE=~/Research/analysis/rho0script_repo/recon/propsal/output_analyzed_sim.root
INPUTTREE=analyzed_helium_2p_inc_data
OUTPUTNAME=physics_output_helium_sim.root
OUTPUTCSVNAME=rho0_He4_2p_inc_KMISS_tdist_sim.csv

root -b -q 'physics_rho0_2p.C("'${INPUTFILE}'","'${INPUTTREE}'","'${OUTPUTNAME}'","'${OUTPUTCSVNAME}'")'
