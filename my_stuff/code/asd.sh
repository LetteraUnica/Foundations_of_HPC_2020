#!/bin/bash
#PBS -l nodes=1:ppn=48
#PBS -l walltime=5:00:00
#PBS -q dssc

cd PBS_O_WORKDIR
cd Foundations_of_HPC_2020/my_stuff/code

module load openmpi/4.0.3/gnu/9.3.0

procs=48
MOVES=10000000000
iters=$(( $MOVES * $procs ))
/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}

procs=24
MOVES=100000000000
iters=$(( $MOVES * $procs ))
/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}