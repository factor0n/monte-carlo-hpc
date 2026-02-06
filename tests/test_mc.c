#include <stdio.h>
#include <assert.h>
#include "../include/monte_carlo.h"

int main()
{
    MonteCarloStats stats =
        monte_carlo_integral(1.0, 5.0, 1000000);

    /* On vérifie juste que le résultat est raisonnable */
    assert(stats.estimate > 2.5);
    assert(stats.estimate < 4.0);

    printf("Test passed!\n");
    return 0;
}
