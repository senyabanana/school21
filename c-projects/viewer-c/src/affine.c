#include "affine.h"

matrix_t translation(object_t *data, double a, double b, double c) {
  matrix_t temp, move;
  create_matrix(4, 4, &temp);
  for (int i = 0, j = 0; i < 4; i++, j++) {
    temp.matrix[i][j] = 1;
  }
  temp.matrix[0][3] = a;
  temp.matrix[1][3] = b;
  temp.matrix[2][3] = c;
  transpose(&temp, &move);
  remove_matrix(&temp);
  matrix_t matrix_3d = create_3d_matrix(data);
  matrix_t mult;
  mult_matrix(&matrix_3d, &move, &mult);
  remove_matrix(&move);
  remove_matrix(&matrix_3d);
  matrix_t result = create_result_matrix(data, &mult);
  remove_matrix(&mult);
  return result;
}

matrix_t rotation(object_t *data, double a, double b, double c) {
  matrix_t res_rotate_X = rotate_x(data, a);
  matrix_t res_rotate_Y = rotate_y(data, b);
  matrix_t res_rotate_Z = rotate_z(data, c);
  matrix_t result = create_result_matrix(data, &res_rotate_Z);
  remove_matrix(&res_rotate_X);
  remove_matrix(&res_rotate_Y);
  remove_matrix(&res_rotate_Z);
  return result;
}

matrix_t scalling(object_t *data, double a, double b, double c) {
  matrix_t scale;
  create_matrix(4, 4, &scale);
  scale.matrix[0][0] = a;
  scale.matrix[1][1] = b;
  scale.matrix[2][2] = c;
  scale.matrix[3][3] = 1;
  matrix_t matrix_3d = create_3d_matrix(data);
  matrix_t result_scale;
  mult_matrix(&matrix_3d, &scale, &result_scale);
  remove_matrix(&scale);
  remove_matrix(&matrix_3d);
  matrix_t result = create_result_matrix(data, &result_scale);
  remove_matrix(&result_scale);
  return result;
}

matrix_t create_3d_matrix(object_t *data) {
  matrix_t matrix_3d;
  create_matrix(data->count_of_vertices + 1, 4, &matrix_3d);
  for (int i = 1; i < data->count_of_vertices + 1; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 3) {
        matrix_3d.matrix[i][j] = 1;
      } else {
        matrix_3d.matrix[i][j] = data->matrix3d.matrix[i][j];
      }
    }
  }
  return matrix_3d;
}

matrix_t create_result_matrix(object_t *data, matrix_t *res) {
  matrix_t result;
  create_matrix(data->count_of_vertices + 1, 3, &result);
  for (int i = 1; i < data->count_of_vertices + 1; i++) {
    for (int j = 0; j < 3; j++) {
      result.matrix[i][j] = res->matrix[i][j];
    }
  }
  return result;
}

matrix_t rotate_x(object_t *data, double angle) {
  angle = (angle * PI) / 180;
  matrix_t rotate_X;
  create_matrix(4, 4, &rotate_X);
  rotate_X.matrix[0][0] = 1;
  rotate_X.matrix[1][1] = cos(angle);
  rotate_X.matrix[1][2] = sin(angle);
  rotate_X.matrix[2][1] = -sin(angle);
  rotate_X.matrix[2][2] = cos(angle);
  rotate_X.matrix[3][3] = 1;
  matrix_t res_rotate_X;
  mult_matrix(&data->matrix3d, &rotate_X, &res_rotate_X);
  remove_matrix(&rotate_X);
  return res_rotate_X;
}

matrix_t rotate_y(object_t *data, double angle) {
  angle = (angle * PI) / 180;
  matrix_t rotate_Y;
  create_matrix(4, 4, &rotate_Y);
  rotate_Y.matrix[0][0] = cos(angle);
  rotate_Y.matrix[0][2] = -sin(angle);
  rotate_Y.matrix[1][1] = 1;
  rotate_Y.matrix[2][0] = sin(angle);
  rotate_Y.matrix[2][2] = cos(angle);
  rotate_Y.matrix[3][3] = 1;
  matrix_t res_rotate_Y;
  mult_matrix(&data->matrix3d, &rotate_Y, &res_rotate_Y);
  remove_matrix(&rotate_Y);
  return res_rotate_Y;
}

matrix_t rotate_z(object_t *data, double angle) {
  angle = (angle * PI) / 180;
  matrix_t rotate_Z;
  create_matrix(4, 4, &rotate_Z);
  rotate_Z.matrix[0][0] = cos(angle);
  rotate_Z.matrix[0][1] = sin(angle);
  rotate_Z.matrix[1][0] = -sin(angle);
  rotate_Z.matrix[1][1] = cos(angle);
  rotate_Z.matrix[2][2] = 1;
  rotate_Z.matrix[3][3] = 1;
  matrix_t res_rotate_Z;
  mult_matrix(&data->matrix3d, &rotate_Z, &res_rotate_Z);
  remove_matrix(&rotate_Z);
  return res_rotate_Z;
}