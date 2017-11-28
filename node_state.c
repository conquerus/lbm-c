#ifndef NODE_STATE_H
#include "node_state.h"
#endif

/* calculate rho */
double bn_get_rho(boltzmann_node* bn)
{
  double rho = 0;
  
  for (int i = 0; i < VELOCITY_DIRECTIONS; i++) {
    rho += bn->f[i];
  }

  /* if (rho < 0) { */
  /*   printf("ERROR: Negative Density\n"); */
  /*   assert(rho>0); */
  /* } */

  return rho;

}

/* calculate vec{u} */
vector_2D bn_get_u(boltzmann_node* bn)
{
  vector_2D u;
  u.x = 0.0;
  u.y = 0.0;
  
  for (int i = 0; i < VELOCITY_DIRECTIONS; i++) {
    u.x += bn->f[i] * e[i].x;
    u.y += bn->f[i] * e[i].y;
  }
  
  return u;
}

/* constructor rho=1 and vec{u}=0 */
int bn_init(boltzmann_node* bn)
{
  //initialize the distributions to equilibrium with rho=1
  for (int i = 0; i < VELOCITY_DIRECTIONS; i++) {
    bn->f[i] = W[i];
    bn->f_new[i] = W[i];
  }
  
  bn->rho = bn_get_rho(bn);
  assert((bn->rho - 1.0) < TOL);
  
  bn->u = bn_get_u(bn);
  assert(bn->u.x == 0.0);
  assert(bn->u.y == 0.0);
  
  return 0;
}

/* output the distribution function and macroscopic vars */
int bn_output_state(boltzmann_node* bn)
{
  printf("\nNode state information:\n");
  for (int i = 0; i < VELOCITY_DIRECTIONS; i++) {
    printf("f[%i] = %f\n", i, bn->f[i]);
  }

  printf("rho = %f\n", bn->rho);
  printf("u = (%f,%f)\n", bn->u.x, bn->u.y);

  return 0;
}

void bn_eq_dist(boltzmann_node* bn, double f_eq[VELOCITY_DIRECTIONS])
{
  double e_dot_u;
  double e_dot_u_sqr;
  double u_dot_u;
  
  for(int i = 0; i < VELOCITY_DIRECTIONS; i++){
    
    e_dot_u = e[i].x * bn->u.x + e[i].y * bn->u.y;
    e_dot_u_sqr = e_dot_u * e_dot_u;
    u_dot_u = bn->u.x * bn->u.x + bn->u.y * bn->u.y;
    
    f_eq[i] = (W[i] * bn->rho) * ( 1.0
                                   + (3.0 * e_dot_u)
                                   + ((9.0/2.0) * e_dot_u_sqr)
                                   - ((3.0/2.0) * u_dot_u));

    /* if (f_eq[i] < 0){ */
    /*   printf("ERROR negative distribution function"); */
    /*   assert(f_eq[i] > 0); */
    /* } */

  }
}
