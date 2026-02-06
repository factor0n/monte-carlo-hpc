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

```text
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
