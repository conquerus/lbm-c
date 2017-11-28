#ifndef GRID_H
#include "grid.h"
#endif

int dm_init(boltzmann_node* dm)
{
  for (int i = 0; i < X_DIR; i++){
    for (int j = 0; j < Y_DIR; j++){
        bn_init(dm + i * X_DIR + j);
    }
  }

  //initial condition
  double e_dot_u;
  double e_dot_u_sqr;
  double u_dot_u;

  vector_2D init_U;
  init_U.x = PLATE_SPEED;
  init_U.y = 0.0;

  double init_rho = 1.0;
    
  int j= Y_DIR - 1;
  for (int i = 0; i < X_DIR; i++){
    for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
      e_dot_u = e[k].x * init_U.x + e[k].y * init_U.y;
      e_dot_u_sqr = e_dot_u * e_dot_u;
      u_dot_u = init_U.x * init_U.x + init_U.y * init_U.y;
    
      (dm + i * X_DIR + j)->f[k] = (W[k] * init_rho) * ( 1.0
                                                         + (3.0 * e_dot_u)
                                                         + ((9.0/2.0) * e_dot_u_sqr)
                                                         - ((3.0/2.0) * u_dot_u));
      (dm + i * X_DIR + j)->f_new[k] = (W[k] * init_rho) * ( 1.0
                                                         + (3.0 * e_dot_u)
                                                         + ((9.0/2.0) * e_dot_u_sqr)
                                                         - ((3.0/2.0) * u_dot_u));
    }
  }
  
  return 0;
}

int dm_output(boltzmann_node* dm)
{
  boltzmann_node * p;
  for (int i = 0; i < X_DIR; i++){
    for (int j = 0; j < Y_DIR; j++){
      p = (dm + i * X_DIR + j);
      printf("%d    %d    %f    %f    %f    %f\n", i, j, p->rho, p->u.x, p->u.y, p->u.x*p->u.x + p->u.y*p->u.y);
    }
  }

  return 0;
}

int dm_output_node(boltzmann_node* dm, int i, int j)
{
  bn_output_state(dm + i * X_DIR + j);

  return 0;
}

int dm_swap_nodes(boltzmann_node* node1, boltzmann_node* node2)
{
  boltzmann_node temp = *node1;
  *node1 = *node2;
  *node2 = temp;

  return 0;
}
