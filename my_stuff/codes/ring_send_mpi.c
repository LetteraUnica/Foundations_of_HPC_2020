#include <stdio.h>
#include <mpi.h>
#include <time.h>

void print_number(int number, int rank, int size) {
    // Sleeps in order to print the numbers sorted by processor rank
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000*rank;
    nanosleep(&ts, &ts);

    printf("processor=%d, message:%d\n", rank, number);
    if(rank==size-1)
        printf("\n");
}

int main(int argc, char* argv[]) {
    // MPI and variable initialization
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int s_old=rank, s_new;

    print_number(s_old, rank, size);
    MPI_Barrier(MPI_COMM_WORLD); // Waits for all processors to finish printing

    // Sets the destination and source of the messages in the ring topology
    int dest = (rank+1)%size;
    int src = (size+rank-1)%size;

    // I use a non blocking send operation and wait for it to complete,
    // however the check isn't really required since MPI_Recv is a blocking
    // operation. So the call to MPI_Wait is only included for safety 
    MPI_Request req;
    MPI_Isend(&s_old, 1, MPI_INT, dest, rank, MPI_COMM_WORLD, &req);
    MPI_Recv(&s_new, 1, MPI_INT, src, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Wait(&req, MPI_STATUS_IGNORE);

    s_old = s_new;
    print_number(s_old, rank, size);

    MPI_Finalize(); // Close MPI
    return 0;
}