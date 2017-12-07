#ifndef SOLVER_H
#include "solver.h"
#endif

#include <string.h>

/* streaming - this is very slow right now because of the duplication
   of f, but it makes it easier to code :)*/
void solv_update_node(boltzmann_node* dm)
{
  for (int i = 0; i < VELOCITY_DIRECTIONS; i++){
    //f_new(x,y) = f(x,y + vec(e))
    dm->f_new[i] = (dm - (int)e[i].x * X_DIR - (int)e[i].y)->f[i];
  }
}

void solv_update_f(boltzmann_node* dm)
{
  for (int i = 0; i < X_DIR; i++){
    for (int j = 0; j < Y_DIR; j++){
      for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
        (dm + i * X_DIR + j)->f[k] = (dm + i * X_DIR + j)->f_new[k];
      }
    }
  }
}

void solv_stream(boltzmann_node* dm)
{
  int i;
  int j;
  double rho;
  
  //internal nodes
  for (i = 1; i < (X_DIR - 1); i++){
    for (j = 1; j < (Y_DIR - 1); j++){
      solv_update_node(dm + i * X_DIR + j);
    }
  }

  //solv_update_f(dm);


  //boundary nodes

  //east
  i = (X_DIR - 1);
  for (j = 1; j < (Y_DIR - 1); j++){
    for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
      if (e[k].x != -1.0){
        (dm + i * X_DIR + j)->f_new[k] =
          ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR -  (int)e[k].y)->f[k];
      }
    }
  }

  //west
  i = 0;
  for (j = 1; j < (Y_DIR - 1); j++){
    for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
      if (e[k].x != 1.0){
        (dm + i * X_DIR + j)->f_new[k] =
          ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR -  (int)e[k].y)->f[k];
      }
    }
  }

  //north
  j = (Y_DIR - 1);
  for (i = 1; i < (X_DIR - 1); i++){
    for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
      if (e[k].y != -1.0){
        (dm + i * X_DIR + j)->f_new[k] =
          ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR - (int)e[k].y)->f[k];
      }
    }
  }
  
  //south
  j = 0;
  for (i = 1; i < (X_DIR-1); i++){
    for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
      if (e[k].y != 1.0){
        (dm + i * X_DIR + j)->f_new[k] =
          ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR - (int)e[k].y)->f[k];
      }
    }
  }

  //corners
  //NW
  i = 0;
  j = (Y_DIR - 1);
  for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
    if (k == 2 || k == 3 || k == 6){
      (dm + i * X_DIR + j)->f_new[k] =
        ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR - (int)e[k].y)->f[k];
    }
  }
      
  //NE
  i = (X_DIR - 1);
  j = (Y_DIR - 1);
  for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
    if (k == 1 || k == 2 || k == 5){
      (dm + i * X_DIR + j)->f_new[k] =
        ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR - (int)e[k].y)->f[k];
    }
  }

  //SW
  i = 0;
  j = 0;
  for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
    if (k == 3 || k == 4 || k == 7){
      (dm + i * X_DIR + j)->f_new[k] =
        ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR - (int)e[k].y)->f[k];
    }
  }

  //SE
  i = (X_DIR - 1);
  j = 0;
  for (int k = 0; k < VELOCITY_DIRECTIONS; k++){
    if (k == 1 || k == 4 || k == 8){
      (dm + i * X_DIR + j)->f_new[k] =
        ((dm + i * X_DIR + j) - (int)e[k].x * X_DIR - (int)e[k].y)->f[k];
    }
  }


    
    //east
    i = (X_DIR - 1);
    for (j = 1; j < (Y_DIR - 1); j++){
      /*special stuff*/
      (dm + i * X_DIR + j)->f_new[3] = (dm + i * X_DIR + j)->f[1];
      (dm + i * X_DIR + j)->f_new[6] = (dm + i * X_DIR + j)->f[8];
      (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5];
    }

    //west
    i = 0;
    for (j = 1; j < (Y_DIR - 1); j++){
      /*special stuff*/
      (dm + i * X_DIR + j)->f_new[1] = (dm + i * X_DIR + j)->f[3];
      (dm + i * X_DIR + j)->f_new[5] = (dm + i * X_DIR + j)->f[7];
      (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6];
    }

    if(true){ //periodic
    //east
    i = (X_DIR - 1);
    for (j = 1; j < (Y_DIR -1 ); j++){
      /*special stuff*/
      (dm + i * X_DIR + j)->f_new[3] = (dm + 0 * X_DIR + j + 0)->f[3];
      (dm + i * X_DIR + j)->f_new[6] = (dm + 0 * X_DIR + j - 1)->f[6];
      (dm + i * X_DIR + j)->f_new[7] = (dm + 0 * X_DIR + j + 1)->f[7];
    }

    //west
    i = 0;
    for (j = 1; j < (Y_DIR - 1); j++){
      /*special stuff*/
      (dm + i * X_DIR + j)->f_new[1] = (dm + (X_DIR - 1) * X_DIR + j + 0)->f[1];
      (dm + i * X_DIR + j)->f_new[5] = (dm + (X_DIR - 1) * X_DIR + j - 1)->f[5];
      (dm + i * X_DIR + j)->f_new[8] = (dm + (X_DIR - 1) * X_DIR + j + 1)->f[8];
    }
    }      

    //south
    j = 0;
    for (i = 1; i < (X_DIR-1); i++){
      /*special stuff*/
      (dm + i * X_DIR + j)->f_new[2] = (dm + i * X_DIR + j)->f[4];
      (dm + i * X_DIR + j)->f_new[5] = (dm + i * X_DIR + j)->f[7];
      (dm + i * X_DIR + j)->f_new[6] = (dm + i * X_DIR + j)->f[8];
    }

    /**********************************/
    /* //////////////////////periodic */
    /**********************************/
        //SW
    i = 0;
    j = 0;  
    /*special stuff*/
    (dm + i * X_DIR + j)->f_new[2] = (dm + i * X_DIR + j)->f[4];
    (dm + i * X_DIR + j)->f_new[5] = (dm + i * X_DIR + j)->f[7];
    (dm + i * X_DIR + j)->f_new[6] = (dm + i * X_DIR + j)->f[8];

    (dm + i * X_DIR + j)->f_new[1] = (dm + (X_DIR - 1) * X_DIR + j + 0)->f[1];
    //(dm + i * X_DIR + j)->f_new[5] = (dm + (X_DIR - 1) * X_DIR + j)->f[5];
    (dm + i * X_DIR + j)->f_new[8] = (dm + (X_DIR - 1) * X_DIR + j + 1)->f[8];
    //SE
    i = (X_DIR - 1);
    j = 0;
    /*special stuff*/
    (dm + i * X_DIR + j)->f_new[2] = (dm + i * X_DIR + j)->f[4];
    (dm + i * X_DIR + j)->f_new[5] = (dm + i * X_DIR + j)->f[7];
  
    (dm + i * X_DIR + j)->f_new[3] = (dm + i * X_DIR + j)->f[1];
    (dm + i * X_DIR + j)->f_new[6] = (dm + i * X_DIR + j)->f[8];
    (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5];

    (dm + i * X_DIR + j)->f_new[3] = (dm + j + 0)->f[3];
    (dm + i * X_DIR + j)->f_new[7] = (dm + j + 1)->f[7];

    //north
    j = Y_DIR - 1;
    for (int i =1; i < X_DIR - 1; i++){
      (dm + i * X_DIR + j)->f_new[4] = (dm + i * X_DIR + j)->f[2];
      (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5] - 0.5*PLATE_SPEED;
      (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6] + 0.5*PLATE_SPEED;
    }
    
    //NW
    i = 0;
    j = Y_DIR - 1;
    /*special stuff*/

    (dm + i * X_DIR + j)->f_new[4] = (dm + i * X_DIR + j)->f[2];
    (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5];
    (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6];

    (dm + i * X_DIR + j)->f_new[1] = (dm + (X_DIR - 1) * X_DIR + j + 0)->f[1];
    (dm + i * X_DIR + j)->f_new[5] = (dm + (X_DIR - 1) * X_DIR + j - 1)->f[5];
    
    //NE
    i = X_DIR - 1;
    j = Y_DIR - 1;
    /*special stuff*/

    (dm + i * X_DIR + j)->f_new[4] = (dm + i * X_DIR + j)->f[2];
    (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5];
    (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6];
  
    (dm + i * X_DIR + j)->f_new[3] = (dm + j + 0)->f[3];
    (dm + i * X_DIR + j)->f_new[6] = (dm + j - 1)->f[6];
    ////////////////////////////////////

    /*       //initial condition */
    /* double e_dot_u; */
    /* double e_dot_u_sqr; */
    /* double u_dot_u; */

    /* vector_2D init_U; */
    /* init_U.x = PLATE_SPEED; */
    /* init_U.y = 0.0; */

    /* double init_rho = 1.0; */
    
    /* j= Y_DIR - 1; */
    /* for (i = 0; i < X_DIR; i++){ */
    /*   for (int k = 0; k < VELOCITY_DIRECTIONS; k++){ */
    /*     e_dot_u = e[k].x * init_U.x + e[k].y * init_U.y; */
    /*     e_dot_u_sqr = e_dot_u * e_dot_u; */
    /*     u_dot_u = init_U.x * init_U.x + init_U.y * init_U.y; */
    
    /*     (dm + i * X_DIR + j)->f[k] = (W[k] * init_rho) * ( 1.0 */
    /*                                                        + (3.0 * e_dot_u) */
    /*                                                        + ((9.0/2.0) * e_dot_u_sqr) */
    /*                                                        - ((3.0/2.0) * u_dot_u)); */
    /*     (dm + i * X_DIR + j)->f_new[k] = (W[k] * init_rho) * ( 1.0 */
    /*                                                            + (3.0 * e_dot_u) */
    /*                                                            + ((9.0/2.0) * e_dot_u_sqr) */
    /*                                                            - ((3.0/2.0) * u_dot_u)); */
    /*   } */
    /* } */

  //solv_update_f(dm); 
  if (false){
  //apply BCs
    //SW
    i = 0;
    j = 0;  
    /*special stuff*/
    (dm + i * X_DIR + j)->f_new[2] = (dm + i * X_DIR + j)->f[4];
    (dm + i * X_DIR + j)->f_new[5] = (dm + i * X_DIR + j)->f[7];
    (dm + i * X_DIR + j)->f_new[6] = (dm + i * X_DIR + j)->f[8];

    (dm + i * X_DIR + j)->f_new[1] = (dm + i * X_DIR + j)->f[3];
    (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6];

    //SE
    i = (X_DIR - 1);
    j = 0;
    /*special stuff*/
    (dm + i * X_DIR + j)->f_new[2] = (dm + i * X_DIR + j)->f[4];
    (dm + i * X_DIR + j)->f_new[5] = (dm + i * X_DIR + j)->f[7];
  
    (dm + i * X_DIR + j)->f_new[3] = (dm + i * X_DIR + j)->f[1];
    (dm + i * X_DIR + j)->f_new[6] = (dm + i * X_DIR + j)->f[8];
    (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5];

    //solv_update_f(dm);

    
    //NW
    i = 0;
    j = (Y_DIR - 1);
    /*special stuff*/
    rho = (dm + i * X_DIR + j)->f[0]
      +(dm + i * X_DIR + j)->f[1]
      +(dm + i * X_DIR + j)->f[3]
      + 2.0 * ((dm + i * X_DIR + j)->f[2]
               +(dm + i * X_DIR + j)->f[5]
               +(dm + i * X_DIR + j)->f[6]);
      
    (dm + i * X_DIR + j)->f_new[4] = (dm + i * X_DIR + j)->f[2];
    (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5]
    //+ (1.0/2.0) * ((dm + i * X_DIR + j)->f[1] - (dm + i * X_DIR + j)->f[3])
    //- (1.0/2.0) * rho * PLATE_SPEED;
      - (1.0/6.0) * rho * PLATE_SPEED;
    //assert((dm + i * X_DIR + j)->f_new[7] > 0.0);
    (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6]
      //+ (1.0/2.0) * ((dm + i * X_DIR + j)->f[3] - (dm + i * X_DIR + j)->f[1])
      //+ (1.0/2.0) * rho * PLATE_SPEED;
      + (1.0/6.0) * rho * PLATE_SPEED;
      
    //assert((dm + i * X_DIR + j)->f_new[8] > 0.0);
    (dm + i * X_DIR + j)->f_new[1] = (dm + i * X_DIR + j)->f[3];
    (dm + i * X_DIR + j)->f_new[5] = (dm + i * X_DIR + j)->f[7];

    //NE
    i = (X_DIR - 1);
    j = (Y_DIR - 1);
    /*special stuff*/
    rho = (dm + i * X_DIR + j)->f[0]
      +(dm + i * X_DIR + j)->f[1]
      +(dm + i * X_DIR + j)->f[3]
      + 2.0 * ((dm + i * X_DIR + j)->f[2]
               +(dm + i * X_DIR + j)->f[5]
               +(dm + i * X_DIR + j)->f[6]);
      
    (dm + i * X_DIR + j)->f_new[4] = (dm + i * X_DIR + j)->f[2];
    (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5]
      //+ (1.0/2.0) * ((dm + i * X_DIR + j)->f[1] - (dm + i * X_DIR + j)->f[3])
      //- (1.0/2.0) * rho * PLATE_SPEED;
      - (1.0/6.0) * rho * PLATE_SPEED;
    (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6]
      //+ (1.0/2.0) * ((dm + i * X_DIR + j)->f[3] - (dm + i * X_DIR + j)->f[1])
      //+ (1.0/2.0) * rho * PLATE_SPEED;
      + (1.0/6.0) * rho * PLATE_SPEED;

    //special stuff
    (dm + i * X_DIR + j)->f_new[3] = (dm + i * X_DIR + j)->f[1];
    (dm + i * X_DIR + j)->f_new[6] = (dm + i * X_DIR + j)->f[8];
    
    //north
    j = (Y_DIR - 1);
    for (i = 1; i < (X_DIR - 1); i++){
      /*special stuff*/
      rho = (dm + i * X_DIR + j)->f[0]
        +(dm + i * X_DIR + j)->f[1]
        +(dm + i * X_DIR + j)->f[3]
        + 2.0 * ((dm + i * X_DIR + j)->f[2]
                 +(dm + i * X_DIR + j)->f[5]
                 +(dm + i * X_DIR + j)->f[6]);
      
      (dm + i * X_DIR + j)->f_new[4] = (dm + i * X_DIR + j)->f[2];
      (dm + i * X_DIR + j)->f_new[7] = (dm + i * X_DIR + j)->f[5]
        //+ (1.0/2.0) * ((dm + i * X_DIR + j)->f[1] - (dm + i * X_DIR + j)->f[3])
        //
        - (1.0/6.0) * rho * PLATE_SPEED;
      //assert((dm + i * X_DIR + j)->f_new[7] > 0.0);
      (dm + i * X_DIR + j)->f_new[8] = (dm + i * X_DIR + j)->f[6]
        //+ (1.0/2.0) * ((dm + i * X_DIR + j)->f[3] - (dm + i * X_DIR + j)->f[1])
        //+ (1.0/2.0) * rho * PLATE_SPEED;
        + (1.0/6.0) * rho * PLATE_SPEED;
      //assert((dm + i * X_DIR + j)->f_new[8] > 0.0);
    }
  }

}

/* collisions */

void solv_collide_node(boltzmann_node* dm)
{
  double f_eq[VELOCITY_DIRECTIONS] = {0};
  bn_eq_dist(dm, f_eq);
  
  for (int i = 0; i < VELOCITY_DIRECTIONS; i++){
    dm->f[i] = dm->f[i] - (1.0/TAO) * (dm->f[i] - f_eq[i]);
    
    /* if (dm->f[i] < 0){ */
    /*   printf("ERROR negative distribution function"); */
    /*   assert(dm->f[i] > 0); */
    /* } */
    
  }
}

void solv_collide(boltzmann_node* dm)
{
  for (int i = 0; i < X_DIR; i++){
    for (int j = 0; j < Y_DIR; j++){
      solv_collide_node(dm + i * X_DIR + j);
    }
  }
}

/* update macro vars */
void solv_update_macro_node(boltzmann_node* dm)
{
  vector_2D temp_u;
    
  dm->rho = bn_get_rho(dm);
  temp_u = bn_get_u(dm);
  dm->u.x = temp_u.x;
  dm->u.y = temp_u.y;
}

/* update macro vars */
void solv_update_macro(boltzmann_node* dm)
{
  for (int i = 0; i < X_DIR; i++){
    for (int j = 0; j < Y_DIR; j++){
      solv_update_macro_node(dm + i * X_DIR + j);
    }
  }
}

/* calculate residual */
double solv_residual(boltzmann_node* dm, vector_2D* old_u)
{
  //WIP
  double residual = 0.0;
  double total = 0.0;
  
  for (int i = 0; i < X_DIR; i++){
    for (int j = 0; j < Y_DIR; j++){
        residual = residual + fabs( (dm + i * X_DIR + j)->u.x - (old_u + i * X_DIR + j)->x );
        total = total + fabs( (dm + i * X_DIR + j)->u.x );
    }
  }

  return residual;
}
