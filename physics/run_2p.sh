

INPUTFILE=/Users/phoebe/Research/analysis/fromifarm/data/heliumdata_analyzed.root
INPUTTREE=analyzed_helium_2p_inc_data
OUTPUTNAME=physics_output_helium.root
OUTPUTCSVNAME=rho0_He4_2p_inc_KMISS_tdist_data.csv

root -b -q 'physics_rho0_2p.C("'${INPUTFILE}'","'${INPUTTREE}'","'${OUTPUTNAME}'","'${OUTPUTCSVNAME}'")'
