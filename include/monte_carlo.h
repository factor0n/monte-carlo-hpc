#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

typedef struct {
    double estimate;
    double std;
} MonteCarloStats;

double my_function(double x);

MonteCarloStats monte_carlo_integral(
    double lower,
    double upper,
    int n_samples
);

#endif
