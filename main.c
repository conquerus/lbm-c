#ifndef GRID_H
#include "grid.h"
#endif

#ifndef SOLVER_H
#include "solver.h"
#endif

#define MAX_ITERATIONS 1E7

int main(int argc, char* argv[])
{

  boltzmann_node* domain;
  vector_2D* old_u;
    
  old_u = malloc(X_DIR*Y_DIR*sizeof(vector_2D));
  domain = malloc(X_DIR*Y_DIR*sizeof(boltzmann_node));
  
  dm_init(domain);


  double residual;
  
  //header
  printf("VARIABLES = \"X\" \"Y\" \"RHO\" \"U\" \"V\" \"V_MAG\"\n");
  printf("ZONE T=\"MAIN\" I = %d J = %d\n", X_DIR, Y_DIR);
  printf("DATAPACKING = POINT \n");
  
  for (int i = 0; i < MAX_ITERATIONS; i++){

    solv_collide(domain);
    solv_stream(domain);
    solv_update_f(domain);
    solv_update_macro(domain);

    if (i % 100 == 0){
      residual = solv_residual(domain, old_u);
      printf("iteration = %d     residual = %.14f\n", i, residual);
      if (residual < RESIDUAL_MIN){
        break;
      }
    }
    
    for (int i = 0; i < X_DIR; i++){
      for (int j = 0; j < Y_DIR; j++){
        (old_u + i * X_DIR + j)->x = (domain + i * X_DIR + j)->u.x;
        (old_u + i * X_DIR + j)->y = (domain + i * X_DIR + j)->u.y;
      }
    }
    
  }

  dm_output(domain);
  
  free(domain);
  free(old_u);
  
  return 0;
}
