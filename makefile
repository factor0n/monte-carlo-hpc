CC = gcc
CFLAGS = -O3 -Wall -Wextra -fopenmp -Iinclude
LDFLAGS = -lm

SRC = src/main.c src/monte_carlo.c
OBJ = $(SRC:.c=.o)

TARGET = monte_carlo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

test:
	$(CC) $(CFLAGS) tests/test_mc.c src/monte_carlo.c -o test $(LDFLAGS)
	./test

.PHONY: all clean test
