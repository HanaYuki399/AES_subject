#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 8

static long steps = 1000000;


int main (int argc, const char *argv[]) {

    int i,j;
    double sign;
    double d;
    double pi, sum = 0;

    double start, delta;
    


    // Compute parallel compute times for 1-MAX_THREADS
    for (j=1; j<= MAX_THREADS; j++) {

        printf(" running on %d threads: ", j);

        // This is the beginning of a single PI computation 
        omp_set_num_threads(j);

        //Initializing according to Nilakantha Series
        sum = 3;
        d = 2;
        sign=1;
        double start = omp_get_wtime();


        #pragma omp parallel for reduction(+:sum) //private(sign)
        for (i=0; i < steps; i++) {

            sum=sum+(sign*(4/((d)*(d+1)*(d+2))));
       
            //for addition and subtraction of alternate terms
            sign=sign*(-1); 
       
            //Increment by 2 according to formula
            d=d+2;
       
            
             
        }

        // Out of the parallel region, finialize computation
        pi = sum;
        delta = omp_get_wtime() - start;
        printf("PI = %.16g computed in %.4g seconds\n", pi, delta);

    }
    

}