#PBS -l nodes=1:ppn=2
#PBS -l walltime=00:01:00
#PBS -q dssc

pwd # Prints where I start
cd $PBS_O_WORKDIR
pwd # Prints the working directory
./omp101

export OMP_NUM_THREADS=20 # 10 threads per core
./omp101

uname -a
