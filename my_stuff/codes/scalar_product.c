#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(double* a, unsigned long int n) {
    for(unsigned long int i=0; i<n; i++) {
        a[i] = drand48()*2.0 - 1.0;
    }
}

void print_array(double* a, unsigned long int n) {
    for(unsigned long int i=0; i<n; i++) {
        printf("%lf ", a[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {

    // Getting the array size and number of repetitions
    const unsigned long int n = atol(argv[1]);
    unsigned int m=1;
    if(argc>2) {
        m = atoi(argv[2]);
    }
    
    clock_t start1 = clock();
    double* restrict a = (double*)malloc(n*sizeof(double));
    double* restrict b = (double*)malloc(n*sizeof(double));
    init(a, n);
    init(b, n);

    clock_t start2 = clock();
    double register sum = 0., sum1=0., sum2=0.;
    for (unsigned int j = 0; j<m; j++) {
        double register old_a=a[0], old_b=b[0];
        double register new_a, new_b;
        unsigned long int n_ = ((n-1)/8)*8;
        
        for (unsigned long int i = 0; i<n_; i+=8) {
            new_a = a[i+8];
            new_b = b[i+8];
            sum1 += old_a*old_b + a[i+1]*b[i+1] +
                a[i+2]*b[i+2] + a[i+3]*b[i+3];
            sum2 += a[i+4]*b[i+4] + a[i+5]*b[i+5] +
                a[i+6]*b[i+6] + a[i+7]*b[i+7];
            old_a = new_a;
            old_b = new_b;
        }
        sum = sum1+sum2;
        for (unsigned long int i = n_; i<n; i++) {
            sum += a[i]*b[i];
        }

    }
    clock_t end = clock();
    
    double cpu_time1 = ((double)(start2-start1)) / CLOCKS_PER_SEC;
    double cpu_time2 = ((double)(end-start2)) / CLOCKS_PER_SEC;
    printf("%lf %lf \n", sum, cpu_time2);

    return 0;
}