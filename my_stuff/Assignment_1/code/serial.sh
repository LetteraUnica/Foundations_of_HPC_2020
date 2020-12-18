#!/bin/bash
#PBS -l nodes=1:ppn=48
#PBS -l walltime=03:00:00
#PBS -q dssc

cd PBS_O_WORKDIR
cd Foundations_of_HPC_2020/my_stuff/code

for MOVES in 100000000000 ; do
	/usr/bin/time ./pi.x ${MOVES} &>> serial.${MOVES}
	/usr/bin/time ./pi.x ${MOVES} &>> serial.${MOVES}
	/usr/bin/time ./pi.x ${MOVES} &>> serial.${MOVES}
done

