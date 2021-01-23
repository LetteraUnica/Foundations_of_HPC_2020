#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>
#include <omp.h>
#include <time.h>

int main(int argc, char* argv[]) {
    long int const register N = 2000000000;
    double* restrict a = (double*)malloc(N*sizeof(double));
    int P = omp_get_max_threads();

    double register sum=0;
    #pragma omp parallel for schedule(dynamic, N/100) shared(a) reduction(+:sum)
    for(long int i=0; i<N/4; i+=4) {
        sum += a[i] + a[i+1] + a[i+2] + a[i+3];
    }

    printf("%lf\n",sum);
    return 0;
}