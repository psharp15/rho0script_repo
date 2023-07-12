#!/apps/bin/python
while True:
	input_potential = input("Which potential(AV18, N2LO, AV4): ")
#if input_potential in allowed_potentials:
	potential = input_potential
	break
while True:
	target = input("Which target (C12, He4, D2): ")
	break

print ('Working on it!')

from subprocess import Popen, PIPE

for i in range(10):
    job_name = 'gcf_sim_%s_%s_%i' % (potential,target,i)
    out_file = '/volatile/halld/home/psharp/simulation/gcf_raw/8GeV/%s_%s/gcf_sim_out_%s_%s_%i.txt' % (potential,target,potential,target,i)
    err_file = '/volatile/halld/home/psharp/simulation/gcf_raw/8GeV/%s_%s/gcf_sim_err_%s_%s_%i.txt' % (potential,target,potential,target,i)
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
sh ~/work/rho0script_repo/gcf/run_gcf.sh %s %s %i""" % (job_name,out_file,err_file,potential,target,i)
    print(command)
    p=Popen(args=["sbatch"],stdin=PIPE);
    p.communicate(command.encode())

print ('All done')
