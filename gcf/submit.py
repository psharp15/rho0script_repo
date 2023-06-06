#!/apps/bin/python
#allowed_potentials = ['AV4']
while True:
	input_potential = input("Which potential(AV18, N2LO, AV4): ")
#if input_potential in allowed_potentials:
	potential = input_potential
	break
while True:
	target = input("Which target (C12, He4, D2): ")
	break

print "Working on it!"

from subprocess import Popen, PIPE

for i in range(5):
        print "Working on submitting run ", i
        command="""#!/bin/sh
#SBATCH --job-name=gcf_sim_{0}_{potential}_{target}
#SBATCH --output=/farm_out/psharp/gcf_sim_{0}_out_{potential}_{target}.txt
#SBATCH --error=/farm_out/psharp/gcf_sim_{0}_err_{potential}_{target}.txt
#SBATCH --partition=priority
#SBATCH --account=halld
#SBATCH --mem-per-cpu=512
#SBATCH -t180
#SBATCH --cpus-per-task=1
#SBATCH --nodes=1
#SBATCH --ntasks=1

bash run_gcf.bash {0} %potential %target 
""".format(str(i))
	print(command)        
p=Popen(args=["sbatch"],stdin=PIPE);
        p.communicate(command)

print "All done"
