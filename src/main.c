#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "../include/monte_carlo.h"

double my_function(double x)
{
    return pow(x, 4) * exp(-x);
}

MonteCarloStats monte_carlo_integral(double lower, double upper, int n_samples)
{
    double sum = 0.0;
    double sum_sq = 0.0;

#pragma omp parallel reduction(+:sum,sum_sq)
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();

#pragma omp for
        for (int i = 0; i < n_samples; i++)
        {
            double u = (double)rand_r(&seed) / RAND_MAX;
            double x = lower + u * (upper - lower);

            double fx = my_function(x);
            sum += fx;
            sum_sq += fx * fx;
        }
    }

    double mean = sum / n_samples;
    double variance = (sum_sq / n_samples) - mean * mean;

    MonteCarloStats stats;
    stats.estimate = (upper - lower) * mean;
    stats.std = (upper - lower) * sqrt(variance / n_samples);

    return stats;
}
