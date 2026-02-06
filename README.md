# Documentation – Monte Carlo HPC Project

## 1. Overview

This project implements a **Monte Carlo integration method** for estimating
a definite integral.  
The code is designed with **High-Performance Computing (HPC)** principles in mind
and includes:

- A sequential / OpenMP parallel implementation
- Performance measurements (speedup)
- Unit tests
- A distributed-memory version using MPI
- A structured build system using Makefile

---

## 2. Mathematical Background

We want to estimate the integral:

I = ∫₁⁵ x⁴ e⁻ˣ dx

Using the Monte Carlo method, the integral is approximated by:

I ≈ (b − a) · (1 / N) · Σ f(xᵢ)

where:
- xᵢ are uniformly distributed random variables in [a, b]
- N is the number of samples

The statistical error decreases proportionally to:

error ∝ 1 / √N

---

## 3. Algorithm Description

1. Generate N random samples uniformly in [a, b]
2. Evaluate the function f(x) for each sample
3. Compute the mean value
4. Scale by the interval length (b − a)
5. Estimate the standard deviation of the result

The algorithm is **embarrassingly parallel**, making it ideal for OpenMP and MPI.

---

## 4. Code Architecture

monte-carlo-hpc/
│
├── Makefile
├── README.md
│
├── src/
│   ├── main.c              # OpenMP execution + timing
│   ├── monte_carlo.c       # Monte Carlo implementation
│   └── monte_carlo_mpi.c   # MPI version
│
├── include/
│   └── monte_carlo.h       # Public API
│
├── tests/
│   └── test_mc.c           # Unit tests
│
├── results/
│   └── (performance outputs, plots)
│
└── docs/
    └── DOCUMENTATION.md
## 5. OpenMP Parallelization

### Strategy

The main Monte Carlo sampling loop is parallelized using OpenMP.
The computation is embarrassingly parallel since each random sample
is independent.

- The `#pragma omp parallel for` directive distributes iterations
  across threads
- A `reduction` clause is used to safely accumulate partial sums
- Each thread uses an independent random seed to avoid correlation

### Implementation Example

#pragma omp parallel reduction(+:sum,sum_sq)
{
    unsigned int seed = time(NULL) ^ omp_get_thread_num();

    #pragma omp for
    for (int i = 0; i < n_samples; i++) {
        double u = (double) rand_r(&seed) / RAND_MAX;
        double x = lower + u * (upper - lower);
        double fx = my_function(x);

        sum += fx;
        sum_sq += fx * fx;
    }
}

## 6. Performance Measurement (Speedup)

This section evaluates the performance improvement obtained using **OpenMP parallelization** compared to the sequential implementation of the Monte Carlo algorithm.

### 6.1 Definition of Speedup

The **speedup** is defined as:

S(p) = \frac{T_1}{T_p}


## 7. Build System

This project uses **Make** to automate compilation, execution, testing, and performance evaluation.

### 7.1 Requirements

- GCC with OpenMP support
- Make
- Linux or macOS
######################################################

make : compile OpenMP version

make run : run OpenMP simulation

make test : run unit tests

make bench : measure OpenMP speedup

make mpi : compile MPI version

make run-mpi : run MPI simulation

make clean : remove binaries and object files


Ayoub Gounnou
Master in High-Performance Computing and Simulation
