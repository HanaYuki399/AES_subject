#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 8

static long steps = 1000000;
//double step;

int main (int argc, const char *argv[]) {

    int i,j;
    double check;
    double d;
    double pi, sum = 0;

    double start, delta;
    

    

    // Compute parallel compute times for 1-MAX_THREADS
    for (j=1; j<= MAX_THREADS; j++) {

        printf(" running on %d threads: ", j);

        // This is the beginning of a single PI computation 
        omp_set_num_threads(j);

        sum = 0;
        d = 1;
        check = 0;
        
        double start = omp_get_wtime();


        #pragma omp parallel for reduction(+:sum) private(check)
        for (i=0; i < steps; i++) {

            
            
             //even index add to sum
            check= i%2;
            if (check == 0)
                {sum = sum + 4/d;
                }
            else
            {
             //odd index subtract from sum
                sum = sum - 4/d;
            }
 
        //increment denominator by 2 
        d = d + 2;
           
        }

        // Out of the parallel region, finialize computation
        pi = sum;
        delta = omp_get_wtime() - start;
        printf("PI = %.16g computed in %.4g seconds\n", sum, delta);

    }
    

}