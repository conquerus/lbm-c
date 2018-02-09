#ifndef NODE_STATE_H
#define NODE_STATE_H

#ifndef LBM_H
#include "LBM.h"
#endif

typedef struct {
  double f_new[VELOCITY_DIRECTIONS];
  double f[VELOCITY_DIRECTIONS];
  double rho;
  vector_2D u;
  /*bool is_BC;*/
} boltzmann_node;

/* bn is boltzmann node :) */

/* calculate rho */
double bn_get_rho(boltzmann_node* bn);
/* calculate vec{u} */
vector_2D bn_get_u(boltzmann_node* bn);
/* calculate the equilibrium distribution */
void bn_eq_dist(boltzmann_node* bn, double f_eq[VELOCITY_DIRECTIONS]);


/* initialize rho=1 and vec{u}=0 */
int bn_init(boltzmann_node* bn);
/* output the distribution function and macroscopic vars */
int bn_output_state(boltzmann_node* bn);

#endif /*NODE_STATE_H*/
