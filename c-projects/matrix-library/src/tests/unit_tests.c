#include <check.h>

#include "../s21_matrix.h"

START_TEST(s21_create_matrix_invalid) {
  matrix_t invalid_matrix;
  int error_code = s21_create_matrix(0, 0, &invalid_matrix);
  ck_assert_int_eq(error_code, INCORRECT_MATRIX);
  ck_assert_ptr_eq(invalid_matrix.matrix, NULL);
}
END_TEST

START_TEST(s21_eq_matrix_test_1) {
  matrix_t A;
  s21_create_matrix(41, 41, &A);
  matrix_t B;
  s21_create_matrix(41, 41, &B);
  s21_fill(&A, 1);
  s21_fill(&B, 1);
  int expected_result = SUCCESS;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
  matrix_t A;
  s21_create_matrix(83, 83, &A);
  matrix_t B;
  s21_create_matrix(83, 83, &B);
  s21_fill(&A, 7);
  s21_fill(&B, 9);
  int expected_result = FAILURE;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
  matrix_t A;
  s21_create_matrix(32, 27, &A);
  matrix_t B;
  s21_create_matrix(32, 27, &B);
  s21_fill(&A, 41);
  s21_fill(&B, 42);
  int expected_result = FAILURE;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_4) {
  matrix_t A;
  s21_create_matrix(22, 22, &A);
  matrix_t B;
  s21_create_matrix(22, 11, &B);
  s21_fill(&A, 13);
  s21_fill(&B, 13);
  int expected_result = FAILURE;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_test_1) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  matrix_t B;
  s21_create_matrix(4, 4, &B);
  s21_fill(&A, 3);
  s21_fill(&B, 4);
  matrix_t expected_result;
  s21_create_matrix(4, 4, &expected_result);
  s21_fill(&expected_result, 7);
  matrix_t actual_result;
  s21_sum_matrix(&A, &B, &actual_result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  matrix_t B;
  s21_create_matrix(4, 4, &B);
  matrix_t expected_result;
  s21_create_matrix(2, 2, &expected_result);
  matrix_t actual_result;
  int result = s21_sum_matrix(&A, &B, &actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  if (!result) s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  matrix_t B;
  s21_create_matrix(4, 4, &B);
  B.matrix[0][0] = 1;
  B.matrix[1][1] = 1;
  B.matrix[2][2] = 1;
  B.matrix[3][3] = 1;
  matrix_t expected_result;
  s21_create_matrix(4, 4, &expected_result);
  expected_result.matrix[0][0] = 1;
  expected_result.matrix[1][1] = 1;
  expected_result.matrix[2][2] = 1;
  expected_result.matrix[3][3] = 1;
  matrix_t actual_result;
  s21_sum_matrix(&A, &B, &actual_result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 4, &matrix3);

  int count = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.matrix[i][j] = ++count + 1.01234567;
      matrix2.matrix[i][j] = count + 1.01234567;
      matrix3.matrix[i][j] = count + 1.01234567;
    }
  }

  int result = s21_eq_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  matrix2.matrix[2][2] += 0.0000009;

  result = s21_eq_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, OK);

  result = s21_eq_matrix(&matrix, &matrix3);

  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};
  matrix_t result_matrix = {NULL, 0, 0};

  s21_create_matrix(2, 2, &matrix);
  s21_create_matrix(2, 2, &matrix2);
  s21_create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter;
      matrix2.matrix[i][j] = counter;
      matrix3.matrix[i][j] = counter++;
    }
  }

  int result = s21_sum_matrix(&matrix, &matrix2, &result_matrix);

  ck_assert_int_eq(result_matrix.matrix[0][0], 2);
  ck_assert_int_eq(result_matrix.matrix[0][1], 4);
  ck_assert_int_eq(result_matrix.matrix[1][0], 6);
  ck_assert_int_eq(result_matrix.matrix[1][1], 8);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&result_matrix);

  result = s21_sum_matrix(&matrix, &matrix3, &result_matrix);

  ck_assert_int_eq(result, CALCULATION_ERROR);

  matrix3.rows = 0;

  s21_remove_matrix(&result_matrix);

  result = s21_sum_matrix(&matrix, &matrix3, &result_matrix);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&matrix3);
  s21_remove_matrix(&result_matrix);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};
  matrix_t result_matrix = {NULL, 0, 0};

  s21_create_matrix(2, 2, &matrix);
  s21_create_matrix(2, 2, &matrix2);
  s21_create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = 0;
      matrix2.matrix[i][j] = counter;
      matrix3.matrix[i][j] = counter++;
    }
  }

  int result = s21_sub_matrix(&matrix, &matrix2, &result_matrix);

  ck_assert_int_eq(result_matrix.matrix[0][0], -1);
  ck_assert_int_eq(result_matrix.matrix[0][1], -2);
  ck_assert_int_eq(result_matrix.matrix[1][0], -3);
  ck_assert_int_eq(result_matrix.matrix[1][1], -4);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&result_matrix);

  result = s21_sub_matrix(&matrix, &matrix3, &result_matrix);

  ck_assert_int_eq(result, CALCULATION_ERROR);

  matrix3.rows = 0;

  s21_remove_matrix(&result_matrix);

  result = s21_sub_matrix(&matrix, &matrix3, &result_matrix);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&matrix3);
  s21_remove_matrix(&result_matrix);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  s21_create_matrix(2, 2, &matrix);
  s21_create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter++;
    }
  }

  double test_number = 0.5;
  int result = s21_mult_number(&matrix, test_number, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][1], 1);
  ck_assert_int_eq(matrix2.matrix[1][1], 2);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&matrix2);

  result = s21_mult_number(&matrix3, test_number, &matrix2);

  ck_assert_int_eq(result, OK);

  matrix3.rows = 0;

  s21_remove_matrix(&matrix2);

  result = s21_mult_number(&matrix3, test_number, &matrix2);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  s21_create_matrix(2, 2, &matrix);
  s21_create_matrix(2, 2, &matrix2);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter;
      matrix2.matrix[i][j] = counter++;
    }
  }

  int result = s21_mult_matrix(&matrix, &matrix2, &matrix3);

  ck_assert_int_eq(matrix3.matrix[0][0], 7);
  ck_assert_int_eq(matrix3.matrix[0][1], 10);
  ck_assert_int_eq(matrix3.matrix[1][0], 15);
  ck_assert_int_eq(matrix3.matrix[1][1], 22);
  ck_assert_int_eq(result, OK);

  matrix.columns = 1;

  s21_remove_matrix(&matrix3);

  result = s21_mult_matrix(&matrix, &matrix2, &matrix3);

  ck_assert_int_eq(result, CALCULATION_ERROR);

  matrix.rows = 0;

  s21_remove_matrix(&matrix3);

  result = s21_mult_matrix(&matrix, &matrix2, &matrix3);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};
  matrix_t matrix3 = {NULL, 0, 0};

  s21_create_matrix(2, 2, &matrix);
  s21_create_matrix(3, 3, &matrix3);

  int counter = 1;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix.matrix[i][j] = counter++;
    }
  }

  int result = s21_transpose(&matrix, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][0], 1);
  ck_assert_int_eq(matrix2.matrix[0][1], 3);
  ck_assert_int_eq(matrix2.matrix[1][0], 2);
  ck_assert_int_eq(matrix2.matrix[1][1], 4);
  ck_assert_int_eq(result, OK);

  matrix3.rows = 0;

  s21_remove_matrix(&matrix2);

  result = s21_transpose(&matrix3, &matrix2);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&matrix3);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  s21_create_matrix(3, 3, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  int result = s21_calc_complements(&matrix, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][0], 0);
  ck_assert_int_eq(matrix2.matrix[0][1], 10);
  ck_assert_int_eq(matrix2.matrix[0][2], -20);
  ck_assert_int_eq(matrix2.matrix[1][0], 4);
  ck_assert_int_eq(matrix2.matrix[1][1], -14);
  ck_assert_int_eq(matrix2.matrix[1][2], 8);
  ck_assert_int_eq(matrix2.matrix[2][0], -8);
  ck_assert_int_eq(matrix2.matrix[2][1], -2);
  ck_assert_int_eq(matrix2.matrix[2][2], 4);
  ck_assert_int_eq(result, 0);

  matrix.columns = 1;

  s21_remove_matrix(&matrix2);

  result = s21_calc_complements(&matrix, &matrix2);

  ck_assert_int_eq(result, CALCULATION_ERROR);

  matrix.rows = 0;

  s21_remove_matrix(&matrix2);

  result = s21_calc_complements(&matrix, &matrix2);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_determinant) {
  double determinant = 0;
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 2, &matrix2);

  int counter = 1;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.matrix[i][j] = counter++;
    }
  }

  int result = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(result, OK);

  result = s21_determinant(&matrix2, &determinant);

  ck_assert_int_eq(result, CALCULATION_ERROR);

  matrix2.rows = 0;

  result = s21_determinant(&matrix2, &determinant);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_determinant_2) {
  double determinant = 0;
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  s21_create_matrix(4, 4, &matrix);
  s21_create_matrix(1, 1, &matrix2);

  matrix.matrix[0][0] = 9;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 2;
  matrix.matrix[0][3] = 4;

  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 4;
  matrix.matrix[1][3] = 4;

  matrix.matrix[2][0] = 4;
  matrix.matrix[2][1] = 4;
  matrix.matrix[2][2] = 9;
  matrix.matrix[2][3] = 9;

  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = 1;
  matrix.matrix[3][2] = 5;
  matrix.matrix[3][3] = 1;

  int result = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(determinant, -578);

  matrix2.matrix[0][0] = 10;
  result = s21_determinant(&matrix2, &determinant);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(determinant, 10);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  s21_create_matrix(3, 3, &matrix);

  matrix.matrix[0][0] = 4;
  matrix.matrix[0][1] = -2;
  matrix.matrix[0][2] = 1;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 6;
  matrix.matrix[1][2] = -2;
  matrix.matrix[2][0] = 1;
  matrix.matrix[2][1] = 0;
  matrix.matrix[2][2] = 0;

  int result = s21_inverse_matrix(&matrix, &matrix2);

  ck_assert_int_eq(matrix2.matrix[0][1], 0);
  ck_assert_int_eq(matrix2.matrix[0][2], 1);
  ck_assert_int_eq(matrix2.matrix[1][0], 1);
  ck_assert_int_eq(matrix2.matrix[2][0], 3);
  ck_assert_int_eq(matrix2.matrix[2][1], 1);
  ck_assert_int_eq(matrix2.matrix[2][2], -13);
  ck_assert_int_eq(result, OK);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 4;
  matrix.matrix[0][2] = 1;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 3;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  s21_remove_matrix(&matrix2);

  result = s21_inverse_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, CALCULATION_ERROR);

  matrix.rows = 2;

  s21_remove_matrix(&matrix2);

  result = s21_inverse_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, CALCULATION_ERROR);

  matrix.rows = 0;

  s21_remove_matrix(&matrix2);

  result = s21_inverse_matrix(&matrix, &matrix2);

  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
}
END_TEST

int main() {
  Suite *s1 = suite_create("а когда не ранинг");
  TCase *tc1_1 = tcase_create("s21_matrix");
  SRunner *sr = srunner_create(s1);
  int result = 0;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, s21_create_matrix_invalid);
  tcase_add_test(tc1_1, s21_sum_matrix_test_1);
  tcase_add_test(tc1_1, s21_sum_matrix_test_2);
  tcase_add_test(tc1_1, s21_sum_matrix_test_3);
  tcase_add_test(tc1_1, test_s21_eq_matrix);
  tcase_add_test(tc1_1, test_s21_sum_matrix);
  tcase_add_test(tc1_1, test_s21_sub_matrix);
  tcase_add_test(tc1_1, test_s21_mult_number);
  tcase_add_test(tc1_1, test_s21_mult_matrix);
  tcase_add_test(tc1_1, test_s21_transpose);
  tcase_add_test(tc1_1, test_s21_calc_complements);
  tcase_add_test(tc1_1, test_s21_determinant);
  tcase_add_test(tc1_1, test_s21_determinant_2);
  tcase_add_test(tc1_1, test_s21_inverse_matrix);
  tcase_add_test(tc1_1, s21_eq_matrix_test_1);
  tcase_add_test(tc1_1, s21_eq_matrix_test_2);
  tcase_add_test(tc1_1, s21_eq_matrix_test_3);
  tcase_add_test(tc1_1, s21_eq_matrix_test_4);

  srunner_run_all(sr, CK_VERBOSE);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);

  return result == 0 ? 0 : 1;
}