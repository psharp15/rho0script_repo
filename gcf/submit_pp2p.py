#!/apps/bin/python
while True:
	potential = input("Which potential(AV18, N2LO, AV4): ")
#if input_potential in allowed_potentials:
	break
while True:
	target = input("Which target (C12, He4, D2): ")
	break

print ('Working on it!')

from subprocess import Popen, PIPE

for i in range(10):
	job_name = 'gcf_pp2p_%s_%s_%i' % (potential,target,i)
	out_file = '/work/halld2/home/psharp/simulation/output/gcf_raw/8GeV/%s_%s/pp2p_out_%s_%s_%i.txt' % (potential,target,potential,target,i)
	err_file = '/work/halld2/home/psharp/simulation/output/gcf_raw/8GeV/%s_%s/pp2p_err_%s_%s_%i.txt' % (potential,target,potential,target,i)
	print ('Working on submitting run '+str(i))
	command="""#!/bin/sh
#SBATCH --job-name=%s
#SBATCH --output=%s
#SBATCH --error=%s
#SBATCH --partition=priority
#SBATCH --account=halld
#SBATCH --mem-per-cpu=512
#SBATCH -t180
#SBATCH --cpus-per-task=1
#SBATCH --nodes=1
#SBATCH --ntasks=1
sh /w/halld-scshelf2101/halld2/home/psharp/rho0script_repo/gcf/run_pp2p_gcf.sh %s %s %i""" % (job_name,out_file,err_file,potential,target,i)
	print(command)        
	p=Popen(args=["sbatch"],stdin=PIPE);
	p.communicate(command.encode())

print ('All done')
