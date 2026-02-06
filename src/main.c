#include <stdio.h>
#include <omp.h>
#include "../include/monte_carlo.h"

int main()
{
    double lower = 1.0;
    double upper = 5.0;
    int samples = 10000000;

    printf("Threads | Time (s) | Estimate\n");

    for(int t = 1; t <= 8; t++)
    {
        omp_set_num_threads(t);

        double start = omp_get_wtime();

        MonteCarloStats stats =
            monte_carlo_integral(lower, upper, samples);

        double end = omp_get_wtime();

        printf("%d | %.4f | %.6f\n",
               t, end - start, stats.estimate);
    }

    return 0;
}
