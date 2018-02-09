#ifndef GRID_H
#define GRID_H

#ifndef LBM_H
#include "LBM.h"
#endif

#ifndef NODE_STATE_H
#include "node_state.h"
#endif

#define X_DIR 100
#define Y_DIR 100

#define PLATE_SPEED 0.005

extern boltzmann_node domain[X_DIR][Y_DIR];

int dm_init(boltzmann_node* dm);
int dm_output(boltzmann_node* dm);
int dm_output_node(boltzmann_node* dm, int i, int j);
int dm_swap_nodes(boltzmann_node* node1, boltzmann_node* node2);

#endif /*GRID_H*/
