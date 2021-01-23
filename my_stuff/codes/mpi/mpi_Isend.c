#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int s1=10, s2;
    MPI_Request req;

    MPI_Isend(&s1, 1, MPI_INT, !rank, rank, MPI_COMM_WORLD, &req);
    MPI_Recv(&s2, 1, MPI_INT, !rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //MPI_Wait(&req, MPI_STATUS_IGNORE);
    printf("%d\n", s1+s2);

    MPI_Finalize();

    return 0;
}