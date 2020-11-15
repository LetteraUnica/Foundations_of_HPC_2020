#!/bin/bash
#PBS -l nodes=1:ppn=48
#PBS -l walltime=13:00:00
#PBS -q dssc

cd PBS_O_WORKDIR
cd Foundations_of_HPC_2020/my_stuff/code

module load openmpi/4.0.3/gnu/9.3.0

for MOVES in 100000000 1000000000 10000000000 ; do
	for procs in 1 4 8 12 16 20 24 28 32 36 40 44 48 ; do
		iters=$(( $MOVES * $procs ))
		echo "executing ", ${iters}, " iterations on ", ${procs}, " processors" 
		/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &> weak.${procs}.${MOVES} 
		/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
        	/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
	done 
done


for MOVES in 100000000000 ; do
	for procs in 1 12 24 48 ; do
		iters=$(( $MOVES * $procs ))
		echo "executing ", ${iters}, " iterations on ", ${procs}, " processors" 
		/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &> weak.${procs}.${MOVES}
		/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
		/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
	done 
done
