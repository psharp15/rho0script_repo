

if [ $# < 3 ]
then
    echo "What's the input file, input tree, and outputfile?"
    exit -1
fi

INPUTFILE=$1
INPUTTREE=$2
OUPUTFILE=$3


root -b -q 'analysis_rho0_2p.C("'${INPUTFILE}'","'${INPUTTREE}'","'${OUPUTFILE}'")'