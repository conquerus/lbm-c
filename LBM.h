#ifndef LBM_H
#define LBM_H

//standard libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define RESIDUAL_MIN 0.000000001
#define TOL 0.00001
#define VELOCITY_DIRECTIONS 9

#define TAO 0.53
//#define TAO 0.01

typedef struct {
  double x;
  double y;
} vector_2D;

extern const double W[VELOCITY_DIRECTIONS];
extern const vector_2D e[VELOCITY_DIRECTIONS];

#endif /*LBM_H*/
