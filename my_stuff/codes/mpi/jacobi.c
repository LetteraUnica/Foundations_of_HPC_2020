#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>

#define NDIM 2

void print_array(int* a, int size) {
    for(int i=0; i<size; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int dims[NDIM] = {0};
    int qperiods[NDIM] = {0};
    MPI_Comm cart_comm;
    MPI_Dims_create(size, NDIM, dims);
    MPI_Cart_create(MPI_COMM_WORLD, NDIM, dims, qperiods, 1, &cart_comm);
    // print_array(dims, NDIM);

    int cart_rank, cart_size;
    MPI_Comm_rank(cart_comm, &cart_rank);
    MPI_Comm_size(cart_comm, &cart_size);

    int cart_coords[NDIM];
    MPI_Cart_coords(cart_comm, cart_rank, NDIM, cart_coords);
  
    int src_rank, dest_rank;
    MPI_Cart_shift(cart_comm, 0, 1, &src_rank, &dest_rank);   
    printf("%d %d %d %d %d\n", rank, src_rank, cart_coords[0], cart_coords[1], dest_rank);

    MPI_Finalize();
    return 0;
}