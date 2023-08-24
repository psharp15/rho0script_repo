

if [ $# < 3 ]
then
    echo "What's the input file, input tree, and outputfile?"
    exit -1
fi

INPUTFILE=$1
INPUTTREE=$2
OUPUTFILE=$3


root -b -q 'filtered_rho0_2p.C("'${INPUTFILE}'","'${INPUTTREE}'","'${OUPUTFILE}'")'

#mv ./${OUTPUTFILE} /work/halld2/home/psharp/data/results/analyzed/
