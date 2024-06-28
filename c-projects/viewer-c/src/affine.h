#ifndef _SRC_AFFINE_H_
#define _SRC_AFFINE_H_

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "viewer.h"

matrix_t create_3d_matrix(object_t *data);
matrix_t create_result_matrix(object_t *data, matrix_t *res);
matrix_t rotate_x(object_t *data, double angle);
matrix_t rotate_y(object_t *data, double angle);
matrix_t rotate_z(object_t *data, double angle);
matrix_t translation(object_t *data, double a, double b, double c);
matrix_t rotation(object_t *data, double a, double b, double c);
matrix_t scalling(object_t *data, double a, double b, double c);

#endif