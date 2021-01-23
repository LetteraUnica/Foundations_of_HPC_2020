#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

#define NDIM 2

void init_matrix(int* a, int rows, int cols) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            a[i*cols + j] = i*cols + j;
        }
    }
}

void print_matrix(int* a, int rows, int cols) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            printf("%d ", a[i*cols + j]);
        }
        printf("\n");
    }
}


int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int N = 4;
    int* global = (int*)malloc(N*N*sizeof(int));
    int* local = (int*)malloc((N/2)*(N/2)*sizeof(int));
    

    if(rank == 0) {
        init_matrix(global, N, N);
        print_matrix(global, N, N);
    }

    MPI_Datatype block, resizedblock;
    int sizes[2] = {N,N};
    int subsizes[2] = {3,3};
    int starts[2] = {0,0};
    
    MPI_Type_create_subarray(2, sizes, subsizes, starts,
                            MPI_ORDER_C, MPI_INT, &block);
    // Resize the type otherwise the displacements are in units of the type size
    MPI_Type_create_resized(block, 0, sizeof(int), &resizedblock);
    MPI_Type_commit(&resizedblock);

    int counts[4] = {1,1,1,1};
    int displs[4] = {1,2,8,10};
    MPI_Scatterv(global, counts, displs, resizedblock, local, 4, MPI_INT, 0, MPI_COMM_WORLD);
    
    sleep(rank);
    print_matrix(local, N/2, N/2);

    MPI_Finalize();
    return 0;
}