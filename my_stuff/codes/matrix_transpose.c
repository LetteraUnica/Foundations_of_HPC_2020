#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(double* A, unsigned int N) {
    for (unsigned int i=0; i<N; i++) {
        for (unsigned int j=0; j<N; j++)
            printf("%f ", A[i*N + j]);
        printf("\n");
    }
}

void init_matrix(double* A, unsigned int N) {
    for (unsigned int i=0; i<N; i++)
        for (unsigned int j=0; j<N; j++)
            A[i*N + j] = i*N + j;
}

double* transpose(double* restrict A, unsigned int N) {
    double* restrict B = (double*)malloc(N*N*sizeof(double));
    const unsigned int stride=8;
    for (unsigned int i=0; i<N; i++)
        for (unsigned int j=0; j<N/stride; j+=stride)
            for (unsigned int k=0; k<stride; k++)
                B[i*N + j+k] = A[(j+k)*N + i];
    
    free(A);
    A = NULL;

    return B;
}

int main(int argc, char* argv[]) {
    unsigned int N = (unsigned int)atol(argv[1]);
    unsigned int runs = (unsigned int)atol(argv[2]);
    double* A = (double*)malloc(N*N*sizeof(double));

    init_matrix(A, N);
    //print_matrix(A, N);

    clock_t start = clock();
    for (unsigned int run=0; run<runs; run++) {
        A = transpose(A, N);
    }
    clock_t end = clock();
    double cpu_time = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f\n", cpu_time);

    //print_matrix(A, N);

    free(A);
    return 0;
}