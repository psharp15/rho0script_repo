
INPUTFILE=$1
INPUTTREE=$2
OUPUTFILE=$3


root -b -q 'filtered_rho0_1p.C("'${INPUTFILE}'","'${INPUTTREE}'","'${OUPUTFILE}'")'

#mv ./${OUTPUTFILE} /work/halld2/home/psharp/data/results/analyzed/
