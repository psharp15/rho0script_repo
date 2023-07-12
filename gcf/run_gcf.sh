#read run "potential" "target"
if [ $# < 2 ]
then
    echo "You must provide an argument!"
    exit -1
fi

potential=$1
target=$2
run=$3

#if [target = "C12"]
#then Z=6 && N=6

#elif [target = "He4"]
#then Z=2 && N=2

#else [target = "D2"]
#then Z=1 && N=1
#fi 

case $1 in
        AV18)
                echo "Using AV18 potential"
                ;;
        N2LO)
                echo "Using N2LO potential"
                ;;
        AV4)
                echo "Using AV4 potential"
                ;;
        *)
                echo "unsure which potential"
                ;;
esac

case $2 in
	C12)
		echo "Using carbon target"
		Z=6
		N=6	
		;;
	He4)
		echo "Using helium 4 target"
		Z=2
		N=2
		;;
	D2)
		echo "Using deuterium target"
		Z=1
		N=1
		;;
	*)
		echo "unsure which target"
		;;
esac
echo "Inputs are valid"

#if [$3 = C12]
#then Z=6 #N=6

#elif [$3 = He4]
#then Z=2 #N=2

#else [$3 = D2]
#Z=1 #N=1
#fi 

program=/w/halld-scshelf2101/halld2/home/psharp/simulation/GCF_Generator_Suite/build/src/programs/genPhoto/genPhoto

outdir=/volatile/halld/home/psharp/simulation/gcf_raw/8GeV/${potential}_${target}
outfile=${outdir}/genoutput_${run}.root

$program $Z $N $outfile 100000000 -R rho0 -u $potential -B 8
echo "I'm all done!"
