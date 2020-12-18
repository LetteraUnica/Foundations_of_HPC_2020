#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int s1=10, s2;
    if(rank == 0) {
        MPI_Send(&s1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&s2, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%d\n", s1+s2);
    }
    if(rank == 1) {
        MPI_Recv(&s2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&s1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        printf("%d\n", s1-s2);
    }
    
    MPI_Finalize();

    return 0;
}