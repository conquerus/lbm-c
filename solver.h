#ifndef SOLVER_H
#define SOLVER_H

#ifndef GRID_H
#include "grid.h"
#endif

/* streaming - this is very slow right now because of the duplication
   of f, but it makes it easier to code :)*/
void solv_update_node(boltzmann_node* dm);
void solv_update_f(boltzmann_node* dm);
int solv_apply_BCs(boltzmann_node* dm);
void solv_stream(boltzmann_node* dm);

/* collisions */
void solv_collide_node(boltzmann_node* dm);
void solv_collide(boltzmann_node* dm);

/* update macro vars */
void solv_update_macro_node(boltzmann_node* dm);
void solv_update_macro(boltzmann_node* dm);

/* residual */
double solv_residual(boltzmann_node* dm, vector_2D* old_u);
#endif /*SOVER_H*/
