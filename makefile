.POSIX:
INC_DIR=./inc
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -march=native -g
CFLAGS += -I$(INC_DIR)
LDFLAGS = -lm
LDLIBS = 

OBJECTS = main.o solver.o grid.o node_state.o LBM.o

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o ./bin/lbm $(OBJECTS) $(LDFLAGS) $(LDLIBS)

main.o: main.c $(INC_DIR)/grid.h $(INC_DIR)/LBM.h $(INC_DIR)/node_state.h $(INC_DIR)/solver.h
LBM.o: LBM.c $(INC_DIR)/LBM.h
node_state.o: node_state.c $(INC_DIR)/node_state.h $(INC_DIR)/LBM.h
grid.o: grid.c $(INC_DIR)/grid.h $(INC_DIR)/LBM.h $(INC_DIR)/node_state.h
solver.o: solver.c $(INC_DIR)/solver.h $(INC_DIR)/grid.h $(INC_DIR)/LBM.h $(INC_DIR)/node_state.h

.PHONY: clean

clean:
	rm -f *.o ./bin/*

