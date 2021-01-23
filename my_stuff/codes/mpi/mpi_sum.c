#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>

void create_array(double* a, long int N) {
    long int N_ = (N/4)*4;
    #pragma omp parallel for schedule(dynamic, 100) shared(a)
    for (long int i=0; i<N_/4; i+=4) {
        a[i] = (double)drand48()*2. - 1.;
        a[i+1] = (double)drand48()*2. - 1.;
        a[i+2] = (double)drand48()*2. - 1.;
        a[i+3] = (double)drand48()*2. - 1.;
    }
    for (long int i=N_; i<N; i++) {
        a[i] = (double)drand48()*2. - 1.;
    }
}

double sum(double* a, long int N) {
    double sum=0;
    long int N_ = (N/4)*4;
    for(int i=0; i<N_; i++) {
        sum += a[i]+a[i+1]+a[i+2]+a[i+3];
    }
    for (long int i=N_; i<N; i++) {
        sum += a[i];
    }

    return sum;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    long int N = 1000000000;
    if(argc > 1)
        N = atol(argv[1]);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    double* a;
    if(rank==0) {
        a = (double*)malloc(N*sizeof(double));
        //create_array(a, N);
    }

    long int chunk = N/size + (N%size < rank);
    double* local_a = (double*)malloc(chunk*sizeof(double));
    MPI_Scatter(a, chunk, MPI_DOUBLE, local_a, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double local_sum = sum(local_a, chunk);
    
    double* sums;
    if(rank==0)
        sums = (double*)malloc(size*sizeof(double));
    MPI_Gather(&local_sum, 1, MPI_DOUBLE, sums, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    if(rank==0) {
        double final_sum=sum(sums, size);
        printf("%lf\n",final_sum);
    }

    MPI_Finalize();
    
    return 0;
}