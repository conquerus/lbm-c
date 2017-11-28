.POSIX:
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -march=native -g
LDFLAGS = -lm
LDLIBS = 

OBJECTS = main.o solver.o grid.o node_state.o LBM.o

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o lbm $(OBJECTS) $(LDFLAGS) $(LDLIBS)

main.o: main.c 
solver.o: solver.c solver.h
grid.o: grid.c grid.h
node_state.o: node_state.c node_state.h
LBM.o: LBM.c LBM.h

.PHONY: clean

clean:
	rm -f *.o ./bin/*

