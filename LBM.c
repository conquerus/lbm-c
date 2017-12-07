#ifndef LBM_H
#include "LBM.h"
#endif

/* equilibrium distribution weights */
const double W[VELOCITY_DIRECTIONS] = {4.0/9.0,
                                       1.0/9.0,
                                       1.0/9.0,
                                       1.0/9.0,
                                       1.0/9.0,
                                       1.0/36.0,
                                       1.0/36.0,
                                       1.0/36.0,
                                       1.0/36.0};

/* D2Q9 velocity vectors */
const vector_2D e[VELOCITY_DIRECTIONS] = {{0.0 , 0.0 },
                                          {1.0 , 0.0 },
                                          {0.0 , 1.0 },
                                          {-1.0, 0.0 },
                                          {0.0 , -1.0},
                                          {1.0 , 1.0 },
                                          {-1.0, 1.0 },
                                          {-1.0, -1.0},
                                          {1.0 , -1.0}};
