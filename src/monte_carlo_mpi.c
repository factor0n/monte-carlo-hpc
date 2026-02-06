#include <mpi.h>
#include <stdio.h>
#include "../include/monte_carlo.h"

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int total_samples = 10000000;
    int local_samples = total_samples / size;

    MonteCarloStats local =
        monte_carlo_integral(1.0, 5.0, local_samples);

    double global_estimate;

    MPI_Reduce(&local.estimate,
               &global_estimate,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    if(rank == 0)
    {
        global_estimate /= size;
        printf("MPI estimate: %f\n", global_estimate);
    }

    MPI_Finalize();
}
