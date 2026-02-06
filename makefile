CC = gcc
MPICC = mpicc

CFLAGS = -O3 -Wall -Wextra -fopenmp -Iinclude
LDFLAGS = -lm

TARGET = monte_carlo
TARGET_MPI = monte_carlo_mpi

SRC = src/main.c src/monte_carlo.c
OBJ = $(SRC:.c=.o)

SRC_MPI = src/monte_carlo_mpi.c src/monte_carlo.c

# =====================
# Build
# =====================
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# =====================
# Run
# =====================
run: $(TARGET)
	./$(TARGET)

# =====================
# Tests
# =====================
test:
	$(CC) $(CFLAGS) tests/test_mc.c src/monte_carlo.c -o test $(LDFLAGS)
	./test

# =====================
# MPI
# =====================
mpi:
	$(MPICC) $(CFLAGS) $(SRC_MPI) -o $(TARGET_MPI) $(LDFLAGS)

run-mpi: mpi
	mpirun -np 4 ./$(TARGET_MPI)

# =====================
# Benchmark
# =====================
bench: $(TARGET)
	@echo "Threads Time(s)"
	@for t in 1 2 4 8; do \
		OMP_NUM_THREADS=$$t ./$(TARGET); \
	done

# =====================
# Clean
# =====================
clean:
	rm -f $(OBJ) $(TARGET) $(TARGET_MPI) test

.PHONY: all run test mpi run-mpi bench clean
