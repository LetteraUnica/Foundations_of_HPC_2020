#!/bin/bash

for MOVES in 100000000 1000000000 10000000000 ; do
	for procs in 1 4 8 12 16 20 24 28 32 36 40 44 48 ; do
		iters=$(( $MOVES * $procs ))
		#echo "executing ", ${iters}, " iterations on ", ${procs}, " processors" 
		echo "/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &> weak.${procs}.${MOVES}"
		#/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
        #/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
	done 
done


for MOVES in 100000000000 ; do
	for procs in 1 12 24 48 ; do
		iters=$(( $MOVES * $procs ))
		#echo "executing ", ${iters}, " iterations on ", ${procs}, " processors" 
		echo "/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &> weak.${procs}.${MOVES}"
		#/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
		#/usr/bin/time mpirun  --mca btl '^openib' -np ${procs} mpi_pi.x  ${iters} &>> weak.${procs}.${MOVES}
	done 
done

