#include <check.h>
#include <math.h>

#include "../affine.h"
#include "../matrix.h"
#include "../viewer.h"

START_TEST(create_matrix_invalid) {
  matrix_t invalid_matrix;
  int error_code = create_matrix(0, 0, &invalid_matrix);
  ck_assert_int_eq(error_code, INCORRECT_MATRIX);
  ck_assert_ptr_eq(invalid_matrix.matrix, NULL);
}
END_TEST

START_TEST(test_transpose) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  create_matrix(2, 2, &matrix);
  create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter++;
    }
  }

  int result = transpose(&matrix, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][0], 1);
  ck_assert_int_eq(matrix2.matrix[0][1], 3);
  ck_assert_int_eq(matrix2.matrix[1][0], 2);
  ck_assert_int_eq(matrix2.matrix[1][1], 4);
  ck_assert_int_eq(result, OK);

  matrix3.rows = 0;

  remove_matrix(&matrix2);

  result = transpose(&matrix3, &matrix2);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  remove_matrix(&matrix);
  remove_matrix(&matrix2);
  remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_process_input_data) {
  object_t data;
  int result = process_input_data(&data, "./objects/cube.obj");
  ck_assert_int_eq(data.count_of_vertices, 8);
  ck_assert_int_eq(data.count_of_facets, 6);
  ck_assert_int_eq(result, 0);
  remove_matrix(&data.matrix3d);
  for (int i = 0; i < data.count_of_facets + 1; i++) {
    free(data.polygons[i].vertices);
  }
  free(data.polygons);
}
END_TEST

START_TEST(test_process_input_data_incorrent_file) {
  object_t data;
  int result = process_input_data(&data, "./objects/cubeeeee.obj");
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_vertices_to_array) {
  object_t data;
  process_input_data(&data, "./objects/cube.obj");
  vertices_to_array(&data);
  ck_assert_double_eq(data.min, -2);
  ck_assert_double_eq(data.max, 2);
  remove_matrix(&data.matrix3d);
  free(data.array_for_vertices);
  for (int i = 0; i < data.count_of_facets + 1; i++) {
    free(data.polygons[i].vertices);
  }
  free(data.polygons);
}
END_TEST

START_TEST(test_facets_to_array) {
  object_t data;
  process_input_data(&data, "./objects/cube.obj");

  facets_to_array(&data);

  ck_assert_ptr_ne(data.array_for_facets, NULL);

  ck_assert_int_eq(data.count_v * 2, 48);
  ck_assert_int_eq(data.array_for_facets[0], 1);
  ck_assert_int_eq(data.array_for_facets[1], 5);
  ck_assert_int_eq(data.array_for_facets[2], 5);

  remove_matrix(&data.matrix3d);
  free(data.array_for_facets);
}
END_TEST

START_TEST(test_rotation_x) {
  object_t data;
  process_input_data(&data, "./objects/pyramid.obj");
  double x = 180;
  matrix_t result = rotation(&data, x, 0, 0);

  matrix_t expected_matrix = {0};
  create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {{0.000000, 0.000000, 0.000000},
                               {1.000000, -0.10134628, -0.69980635},
                               {-1.000000, -0.10134628, -0.69980635},
                               {-1.000000, 0.69980635, -0.10134628},
                               {1.000000, 0.69980635, -0.10134628},
                               {0.000000, -0.29923003, 0.40057631}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(0, ret);

  remove_matrix(&expected_matrix);
  remove_matrix(&data.matrix3d);
  for (int i = 0; i < data.count_of_facets + 1; i++) {
    free(data.polygons[i].vertices);
  }
  free(data.polygons);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_rotation_y) {
  object_t data;
  process_input_data(&data, "./objects/pyramid.obj");
  double y = 90;
  matrix_t result = rotation(&data, 0, y, 0);
  matrix_t expected_matrix = {0};
  create_matrix(6, 3, &expected_matrix);
  double exp_matrix_0[6][3] = {
      {0.000000, 0.000000, 0.000000},       {-0.8950719, -0.500000, 0.6699599},
      {0.0010753, -0.500000, -1.1180335},   {0.8950719, -0.500000, -0.6699599},
      {-0.001075335, -0.500000, 1.1180335}, {0.000000, 0.500000, 0.000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(0, ret);

  remove_matrix(&expected_matrix);
  remove_matrix(&data.matrix3d);
  for (int i = 0; i < data.count_of_facets + 1; i++) {
    free(data.polygons[i].vertices);
  }
  free(data.polygons);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_rotation_z) {
  object_t data;
  process_input_data(&data, "./objects/pyramid.obj");
  double z = -90;
  matrix_t result = rotation(&data, 0, 0, z);

  matrix_t expected_matrix = {0};
  create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {
      {0.000000, 0.000000, 0.000000},      {-0.0010753, 1.1180335, 0.5000000},
      {0.8950719, -0.6699599, 0.5000000},  {0.8950719, -0.6699599, -0.5000000},
      {-0.0010753, 1.1180335, -0.5000000}, {-0.4469983, -0.2240368, 0.0000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(0, ret);

  remove_matrix(&expected_matrix);
  remove_matrix(&data.matrix3d);
  for (int i = 0; i < data.count_of_facets + 1; i++) {
    free(data.polygons[i].vertices);
  }
  free(data.polygons);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_scalling) {
  object_t data;
  process_input_data(&data, "./objects/pyramid.obj");
  matrix_t result = scalling(&data, 2, 2, 2);

  matrix_t expected_matrix = {0};
  create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {
      {0.0000000, 0.0000000, 0.0000000},   {2.0000000, -1.0000000, 1.0000000},
      {-2.0000000, -1.0000000, 1.0000000}, {-2.0000000, -1.0000000, -1.0000000},
      {2.0000000, -1.0000000, -1.0000000}, {0.0000000, 1.0000000, 0.0000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(0, ret);

  remove_matrix(&expected_matrix);
  remove_matrix(&data.matrix3d);
  for (int i = 0; i < data.count_of_facets + 1; i++) {
    free(data.polygons[i].vertices);
  }
  free(data.polygons);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_translation) {
  object_t data;
  process_input_data(&data, "./objects/pyramid.obj");
  matrix_t result = translation(&data, 2, 3, 4);

  matrix_t expected_matrix = {0};
  create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {
      {0.0000000, 0.0000000, 0.0000000}, {2.0000000, 4.0000000, 4.0000000},
      {1.0000000, 3.0000000, 3.0000000}, {3.0000000, 3.0000000, 3.0000000},
      {3.0000000, 3.0000000, 5.0000000}, {1.0000000, 3.0000000, 5.0000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(1, ret);

  remove_matrix(&expected_matrix);
  remove_matrix(&data.matrix3d);
  for (int i = 0; i < data.count_of_facets + 1; i++) {
    free(data.polygons[i].vertices);
  }
  free(data.polygons);
  remove_matrix(&result);
}
END_TEST

int main() {
  Suite *suite = suite_create("а когда не ранинг:");
  TCase *tc = tcase_create("viewer");
  SRunner *srunner = srunner_create(suite);
  int result;
  suite_add_tcase(suite, tc);

  tcase_add_test(tc, create_matrix_invalid);
  tcase_add_test(tc, test_transpose);
  tcase_add_test(tc, test_process_input_data);
  tcase_add_test(tc, test_process_input_data_incorrent_file);
  tcase_add_test(tc, test_vertices_to_array);
  tcase_add_test(tc, test_facets_to_array);
  tcase_add_test(tc, test_rotation_x);
  tcase_add_test(tc, test_rotation_y);
  tcase_add_test(tc, test_rotation_z);
  tcase_add_test(tc, test_scalling);
  tcase_add_test(tc, test_translation);

  srunner_run_all(srunner, CK_VERBOSE);
  result = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return result == 0 ? 0 : 1;
}