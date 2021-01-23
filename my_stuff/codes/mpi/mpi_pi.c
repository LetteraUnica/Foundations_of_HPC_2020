#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned long long global_iter=10000000;
    if(argc>1)
        global_iter = (unsigned long long)atoll(argv[1]);
    
    unsigned long long register const iter = global_iter/size + (global_iter%size < rank);
    unsigned long long count=0;
    for (unsigned long long i=0; i<iter; i++) {
        double x = drand48();
        double y = drand48();
        double d = x*x + y*y;
        count += (d<1);
    }
    unsigned long long global_count=0;
    MPI_Reduce(&count, &global_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(rank==0) {
        double pi = (double)global_count / (double)global_iter * 4;
        printf("pi=%lf\n",pi);    
    }

    MPI_Finalize();
    
    return 0;
}