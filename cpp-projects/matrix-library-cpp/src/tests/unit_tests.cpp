#include <gtest/gtest.h>

#include "../s21_matrix_oop.hpp"

TEST(EqualMatrix, SuccessEqual) {
  S21Matrix first(4, 4);
  first.SetValue(1, 1, 6);
  first.SetValue(2, 2, 9);
  S21Matrix second(4, 4);
  second.SetValue(1, 1, 6);
  second.SetValue(2, 2, 9);
  ASSERT_TRUE(first.EqMatrix(second));
}

TEST(EqualMatrix, DifferentMatrix) {
  S21Matrix first(4, 4);
  first.SetValue(1, 1, 9);
  first.SetValue(2, 2, 9);
  S21Matrix second(3, 3);
  second.SetValue(1, 1, 6);
  second.SetValue(2, 2, 9);
  ASSERT_FALSE(first.EqMatrix(second));
}

TEST(EqualMatrix, DifferentRows) {
  S21Matrix first(3, 4);
  S21Matrix second(4, 4);
  ASSERT_FALSE(first.EqMatrix(second));
}

TEST(EqualMatrix, DifferentColumns) {
  S21Matrix first(4, 3);
  S21Matrix second(4, 4);
  ASSERT_FALSE(first.EqMatrix(second));
}

TEST(Equalmatrix, FailureEqual) {
  S21Matrix first(4, 4);
  first.SetValue(1, 1, 9);
  first.SetValue(2, 2, 9);
  S21Matrix second(4, 4);
  second.SetValue(1, 1, 6);
  second.SetValue(2, 2, 9);
  ASSERT_FALSE(first.EqMatrix(second));
}

TEST(SumMatrix, SuccessSum) {
  S21Matrix first(3, 3);
  first.SetValue(0, 0, 1);
  first.SetValue(0, 1, 2);
  first.SetValue(0, 2, 3);
  S21Matrix second(3, 3);
  second.SetValue(0, 0, 2);
  second.SetValue(0, 1, 4);
  second.SetValue(0, 2, 6);
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 3);
  expected.SetValue(0, 1, 6);
  expected.SetValue(0, 2, 9);
  first.SumMatrix(second);
  ASSERT_TRUE(first.EqMatrix(expected));
}

TEST(SumMatrix, IncorrectInput) {
  S21Matrix first(3, 3);
  S21Matrix second(4, 4);
  try {
    first.SumMatrix(second);
    FAIL()
        << "Expected std::out_of_range exception, but no exception was thrown.";
  } catch (const std::out_of_range& e) {
    ASSERT_STREQ("Incorrect input, matrices should have the same size",
                 e.what());
  } catch (...) {
    FAIL() << "Unexpected exception type.";
  }
}

TEST(SubMatrix, SuccessSub) {
  S21Matrix first(3, 3);
  first.SetValue(0, 0, 3);
  first.SetValue(0, 1, 6);
  first.SetValue(0, 2, 9);
  S21Matrix second(3, 3);
  second.SetValue(0, 0, 2);
  second.SetValue(0, 1, 4);
  second.SetValue(0, 2, 6);
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 1);
  expected.SetValue(0, 1, 2);
  expected.SetValue(0, 2, 3);
  first.SubMatrix(second);
  ASSERT_TRUE(first.EqMatrix(expected));
}

TEST(SubMatrix, IncorrectInput) {
  S21Matrix first(3, 3);
  S21Matrix second(4, 4);
  try {
    first.SubMatrix(second);
    FAIL()
        << "Expected std::out_of_range exception, but no exception was thrown.";
  } catch (const std::out_of_range& e) {
    ASSERT_STREQ("Incorrect input, matrices should have the same size",
                 e.what());
  } catch (...) {
    FAIL() << "Unexpected exception type.";
  }
}

TEST(MulNumber, SuccessMultiply) {
  S21Matrix matrix(3, 3);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(0, 1, 2);
  matrix.SetValue(0, 2, 3);
  matrix.SetValue(1, 0, 4);
  matrix.SetValue(1, 1, 5);
  matrix.SetValue(1, 2, 6);
  matrix.SetValue(2, 0, 7);
  matrix.SetValue(2, 1, 8);
  matrix.SetValue(2, 2, 9);
  const double multiplier = 2.5;
  matrix.MulNumber(multiplier);
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 2.5);
  expected.SetValue(0, 1, 5);
  expected.SetValue(0, 2, 7.5);
  expected.SetValue(1, 0, 10);
  expected.SetValue(1, 1, 12.5);
  expected.SetValue(1, 2, 15);
  expected.SetValue(2, 0, 17.5);
  expected.SetValue(2, 1, 20);
  expected.SetValue(2, 2, 22.5);
  ASSERT_TRUE(matrix.EqMatrix(expected));
}

TEST(MulMatrix, SuccessMultiply) {
  S21Matrix first(3, 3);
  first.SetValue(0, 0, 1);
  first.SetValue(0, 1, 2);
  first.SetValue(0, 2, 3);
  first.SetValue(1, 0, 4);
  first.SetValue(1, 1, 5);
  first.SetValue(1, 2, 6);
  S21Matrix second(3, 3);
  second.SetValue(0, 0, 1);
  second.SetValue(0, 1, 2);
  second.SetValue(1, 0, 3);
  second.SetValue(1, 1, 4);
  second.SetValue(2, 0, 5);
  second.SetValue(2, 1, 6);
  first.MulMatrix(second);
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 22);
  expected.SetValue(0, 1, 28);
  expected.SetValue(0, 2, 0);
  expected.SetValue(1, 0, 49);
  expected.SetValue(1, 1, 64);
  expected.SetValue(1, 2, 0);
  expected.SetValue(2, 0, 0);
  expected.SetValue(2, 1, 0);
  expected.SetValue(2, 2, 0);
  ASSERT_TRUE(first.EqMatrix(expected));
}

TEST(MulMatrix, InvalidDimensions) {
  S21Matrix first(3, 2);
  first.SetValue(0, 0, 1);
  first.SetValue(0, 1, 2);
  first.SetValue(1, 0, 3);
  first.SetValue(1, 1, 4);
  first.SetValue(2, 0, 5);
  first.SetValue(2, 1, 6);
  S21Matrix second(3, 3);
  second.SetValue(0, 0, 1);
  second.SetValue(0, 1, 2);
  second.SetValue(1, 0, 3);
  second.SetValue(1, 1, 4);
  second.SetValue(2, 0, 5);
  second.SetValue(2, 1, 6);
  ASSERT_THROW(first.MulMatrix(second), std::invalid_argument);
}

TEST(TransposeMatrix, SuccessTranspose) {
  S21Matrix original(3, 2);
  original.SetValue(0, 0, 1);
  original.SetValue(0, 1, 2);
  original.SetValue(1, 0, 3);
  original.SetValue(1, 1, 4);
  original.SetValue(2, 0, 5);
  original.SetValue(2, 1, 6);
  S21Matrix transposed = original.Transpose();
  ASSERT_EQ(transposed.GetValue(0, 0), 1);
  ASSERT_EQ(transposed.GetValue(1, 0), 2);
  ASSERT_EQ(transposed.GetValue(0, 1), 3);
  ASSERT_EQ(transposed.GetValue(1, 1), 4);
  ASSERT_EQ(transposed.GetValue(0, 2), 5);
  ASSERT_EQ(transposed.GetValue(1, 2), 6);
  ASSERT_EQ(transposed.GetRows(), 2);
  ASSERT_EQ(transposed.GetColumns(), 3);
}

TEST(Determinant, OneByOneMatrix) {
  S21Matrix matrix(1, 1);
  matrix.SetValue(0, 0, 5.0);
  ASSERT_DOUBLE_EQ(matrix.Determinant(), 5.0);
}

TEST(Determinant, TwoByTwoMatrix) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 2.0);
  matrix.SetValue(0, 1, 3.0);
  matrix.SetValue(1, 0, 4.0);
  matrix.SetValue(1, 1, 5.0);
  ASSERT_DOUBLE_EQ(matrix.Determinant(), -2.0);
}

TEST(Determinant, ThreeByThreeMatrix) {
  S21Matrix matrix(3, 3);
  matrix.SetValue(0, 0, 1.0);
  matrix.SetValue(0, 1, 2.0);
  matrix.SetValue(0, 2, 3.0);
  matrix.SetValue(1, 0, 4.0);
  matrix.SetValue(1, 1, 5.0);
  matrix.SetValue(1, 2, 6.0);
  matrix.SetValue(2, 0, 7.0);
  matrix.SetValue(2, 1, 8.0);
  matrix.SetValue(2, 2, 9.0);
  ASSERT_DOUBLE_EQ(matrix.Determinant(), 0.0);
}

TEST(Determinant, NonSquareMatrix) {
  S21Matrix matrix(2, 3);  // Non-square matrix
  ASSERT_THROW(matrix.Determinant(), std::invalid_argument);
}

TEST(MatrixCalcComplements, CorrectComplements) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 4);
  matrix.SetValue(0, 1, 7);
  matrix.SetValue(1, 0, 2);
  matrix.SetValue(1, 1, 6);
  matrix.CalcComplements();
  S21Matrix expected(2, 2);
  expected.SetValue(0, 0, 6);
  expected.SetValue(0, 1, -2);
  expected.SetValue(1, 0, -7);
  expected.SetValue(1, 1, 4);
  ASSERT_TRUE(matrix.EqMatrix(expected));
}

TEST(MatrixCalcComplements, NonSquareMatrix) {
  S21Matrix matrix(2, 3);  // Non-square matrix
  ASSERT_THROW(matrix.CalcComplements(), std::invalid_argument);
}

TEST(InverseMatrix, NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  ASSERT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(InverseMatrix, SingularMatrix) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 2.0);
  matrix.SetValue(0, 1, 2.0);
  matrix.SetValue(1, 0, 4.0);
  matrix.SetValue(1, 1, 4.0);
  ASSERT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(MatrixInverse, CorrectInverse) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 4);
  matrix.SetValue(0, 1, 7);
  matrix.SetValue(1, 0, 2);
  matrix.SetValue(1, 1, 6);
  S21Matrix inverse = matrix.InverseMatrix();
  double determinant = 4 * 6 - 7 * 2;
  S21Matrix expected(2, 2);
  expected.SetValue(0, 0, 6 / determinant);
  expected.SetValue(0, 1, -7 / determinant);
  expected.SetValue(1, 0, -2 / determinant);
  expected.SetValue(1, 1, 4 / determinant);
  ASSERT_TRUE(inverse.EqMatrix(expected));
}

TEST(MatrixOperators, Addition) {
  S21Matrix matrix1(3, 3);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(1, 1, 2);
  matrix1.SetValue(2, 2, 3);
  S21Matrix matrix2(3, 3);
  matrix2.SetValue(0, 0, 4);
  matrix2.SetValue(1, 1, 5);
  matrix2.SetValue(2, 2, 6);
  S21Matrix result = matrix1 + matrix2;
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 5);
  expected.SetValue(1, 1, 7);
  expected.SetValue(2, 2, 9);
  ASSERT_TRUE(result.EqMatrix(expected));
}

TEST(MatrixOperators, Subtraction) {
  S21Matrix matrix1(3, 3);
  matrix1.SetValue(0, 0, 7);
  matrix1.SetValue(1, 1, 8);
  matrix1.SetValue(2, 2, 9);
  S21Matrix matrix2(3, 3);
  matrix2.SetValue(0, 0, 4);
  matrix2.SetValue(1, 1, 5);
  matrix2.SetValue(2, 2, 6);
  S21Matrix result = matrix1 - matrix2;
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 3);
  expected.SetValue(1, 1, 3);
  expected.SetValue(2, 2, 3);
  ASSERT_TRUE(result.EqMatrix(expected));
}

TEST(MatrixOperators, Multiplication) {
  S21Matrix matrix1(2, 3);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(0, 1, 2);
  matrix1.SetValue(0, 2, 3);
  matrix1.SetValue(1, 0, 4);
  matrix1.SetValue(1, 1, 5);
  matrix1.SetValue(1, 2, 6);
  S21Matrix matrix2(3, 2);
  matrix2.PrintMatrix();
  matrix2.SetValue(0, 0, 7);
  matrix2.SetValue(0, 1, 8);
  matrix2.SetValue(1, 0, 9);
  matrix2.SetValue(1, 1, 10);
  matrix2.SetValue(2, 0, 11);
  matrix2.SetValue(2, 1, 12);
  S21Matrix result = matrix1 * matrix2;
  S21Matrix expected(2, 2);
  expected.SetValue(0, 0, 58);
  expected.SetValue(0, 1, 64);
  expected.SetValue(1, 0, 139);
  expected.SetValue(1, 1, 154);
  ASSERT_TRUE(result.EqMatrix(expected));
}

TEST(MatrixOperators, MultiplicationByNumber) {
  S21Matrix matrix(3, 3);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(1, 1, 2);
  matrix.SetValue(2, 2, 3);
  double num = 2.5;
  S21Matrix result = matrix * num;
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 2.5);
  expected.SetValue(1, 1, 5);
  expected.SetValue(2, 2, 7.5);
  ASSERT_TRUE(result.EqMatrix(expected));
}

TEST(MatrixOperators, Equality) {
  S21Matrix matrix1(2, 2);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(1, 1, 2);
  S21Matrix matrix2(2, 2);
  matrix2.SetValue(0, 0, 1);
  matrix2.SetValue(1, 1, 2);
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(MatrixOperators, Assignment) {
  S21Matrix matrix1(3, 3);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(1, 1, 2);
  matrix1.SetValue(2, 2, 3);
  S21Matrix matrix2(3, 3);
  matrix2 = matrix1;
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixOperators, AddAndAssign) {
  S21Matrix matrix1(2, 2);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(1, 1, 2);
  S21Matrix matrix2(2, 2);
  matrix2.SetValue(0, 0, 3);
  matrix2.SetValue(1, 1, 4);
  matrix1 += matrix2;
  S21Matrix expected(2, 2);
  expected.SetValue(0, 0, 4);
  expected.SetValue(1, 1, 6);
  ASSERT_TRUE(matrix1.EqMatrix(expected));
}

TEST(MatrixOperators, SubtractAndAssign) {
  S21Matrix matrix1(2, 2);
  matrix1.SetValue(0, 0, 5);
  matrix1.SetValue(1, 1, 6);
  S21Matrix matrix2(2, 2);
  matrix2.SetValue(0, 0, 2);
  matrix2.SetValue(1, 1, 3);
  matrix1 -= matrix2;
  S21Matrix expected(2, 2);
  expected.SetValue(0, 0, 3);
  expected.SetValue(1, 1, 3);
  ASSERT_TRUE(matrix1.EqMatrix(expected));
}

TEST(MatrixOperators, MultiplyAndAssign) {
  S21Matrix matrix1(2, 3);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(0, 1, 2);
  matrix1.SetValue(0, 2, 3);
  matrix1.SetValue(1, 0, 4);
  matrix1.SetValue(1, 1, 5);
  matrix1.SetValue(1, 2, 6);
  S21Matrix matrix2(3, 2);
  matrix2.SetValue(0, 0, 7);
  matrix2.SetValue(0, 1, 8);
  matrix2.SetValue(1, 0, 9);
  matrix2.SetValue(1, 1, 10);
  matrix2.SetValue(2, 0, 11);
  matrix2.SetValue(2, 1, 12);
  matrix1 *= matrix2;
  S21Matrix expected(2, 2);
  expected.SetValue(0, 0, 58);
  expected.SetValue(0, 1, 64);
  expected.SetValue(1, 0, 139);
  expected.SetValue(1, 1, 154);
  ASSERT_TRUE(matrix1.EqMatrix(expected));
}

TEST(MatrixOperators, MultiplyByNumberAndAssign) {
  S21Matrix matrix(3, 3);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(1, 1, 2);
  matrix.SetValue(2, 2, 3);
  double num = 2.5;
  matrix *= num;
  S21Matrix expected(3, 3);
  expected.SetValue(0, 0, 2.5);
  expected.SetValue(1, 1, 5);
  expected.SetValue(2, 2, 7.5);
  ASSERT_TRUE(matrix.EqMatrix(expected));
}

TEST(MatrixOperators, Indexing) {
  S21Matrix matrix(3, 3);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(1, 1, 2);
  matrix.SetValue(2, 2, 3);
  double value = matrix(1, 1);
  ASSERT_EQ(value, 2);
}

TEST(MatrixOperators, IndexingOutOfRange) {
  S21Matrix matrix(3, 3);
  ASSERT_THROW(matrix(4, 3), std::out_of_range);
}

TEST(MatrixOperators, Addition_ThrowOnDifferentDimensions) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);
  ASSERT_THROW(matrix1 + matrix2, std::invalid_argument);
}

TEST(MatrixOperators, Subtraction_ThrowOnDifferentDimensions) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);
  ASSERT_THROW(matrix1 - matrix2, std::invalid_argument);
}

TEST(MatrixOperators, Multiplication_ThrowOnInvalidDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(4, 5);
  ASSERT_THROW(matrix1 * matrix2, std::invalid_argument);
}

TEST(MatrixOperators, Assignment_SelfAssignment) {
  S21Matrix matrix(3, 3);
  S21Matrix second;
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(1, 1, 5);
  second = matrix;
  ASSERT_EQ(second.GetValue(0, 0), 1);
  ASSERT_EQ(second.GetValue(1, 1), 5);
}

TEST(MatrixOperators, PlusEqual_IncorrectSize) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(matrix1 += matrix2, std::invalid_argument);
}

TEST(MatrixOperators, Subtract_IncorrectSize) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(4, 4);
  ASSERT_THROW(matrix1 -= matrix2, std::invalid_argument);
}

TEST(MatrixOperators, Multiply_IncorrectSize) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 4);
  ASSERT_THROW(matrix1 *= matrix2, std::invalid_argument);
}

TEST(MatrixFunctionality, SetValue_OutOfBounds) {
  S21Matrix matrix(3, 3);
  ASSERT_THROW(matrix.SetValue(3, 0, 1.0), std::out_of_range);
}

TEST(MatrixFunctionality, GetValue_OutOfBounds) {
  S21Matrix matrix(3, 3);
  ASSERT_THROW(matrix.GetValue(3, 0), std::out_of_range);
}

TEST(MatrixMoveConstructor, MovesResourceSuccessfully) {
  S21Matrix original(2, 2);
  original.SetValue(0, 0, 1.0);
  original.SetValue(0, 1, 2.0);
  original.SetValue(1, 0, 3.0);
  original.SetValue(1, 1, 4.0);
  S21Matrix moved(std::move(original));
  EXPECT_EQ(moved(0, 0), 1.0);
  EXPECT_EQ(moved(0, 1), 2.0);
  EXPECT_EQ(moved(1, 0), 3.0);
  EXPECT_EQ(moved(1, 1), 4.0);
}

TEST(MatrixMutateTest, SetRowsDecrease) {
  S21Matrix matrix(3, 2);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(0, 1, 2);
  matrix.SetValue(1, 0, 3);
  matrix.SetValue(1, 1, 4);
  matrix.SetValue(2, 0, 5);
  matrix.SetValue(2, 1, 6);
  matrix.SetRows(2);
  ASSERT_EQ(matrix.GetRows(), 2);
  ASSERT_EQ(matrix.GetColumns(), 2);
}

TEST(MatrixMutateTest, SetRowsIncrease) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(0, 1, 2);
  matrix.SetValue(1, 0, 3);
  matrix.SetValue(1, 1, 4);
  matrix.SetRows(4);
  ASSERT_EQ(matrix.GetRows(), 4);
  ASSERT_EQ(matrix.GetColumns(), 2);
}

TEST(MatrixMutateTest, SetColumnsDecrease) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(0, 1, 2);
  matrix.SetValue(1, 0, 3);
  matrix.SetValue(1, 1, 4);
  matrix.SetColumns(1);
  ASSERT_EQ(matrix.GetRows(), 2);
  ASSERT_EQ(matrix.GetColumns(), 1);
}

TEST(MatrixMutateTest, SetColumnsIncrease) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(0, 1, 2);
  matrix.SetValue(1, 0, 3);
  matrix.SetValue(1, 1, 4);
  matrix.SetColumns(3);
  ASSERT_EQ(matrix.GetRows(), 2);
  ASSERT_EQ(matrix.GetColumns(), 3);
}

TEST(S21Matrix, AssignmentOperator) {
  // Создаем исходную матрицу
  S21Matrix original(2, 2);
  original.SetValue(0, 0, 1);
  original.SetValue(0, 1, 2);
  original.SetValue(1, 0, 3);
  original.SetValue(1, 1, 4);

  // Создаем вторую матрицу и присваиваем ей значения первой
  S21Matrix assigned;
  assigned = original;

  // Проверяем, что матрицы идентичны
  ASSERT_TRUE(original.EqMatrix(assigned));

  // Модифицируем исходную матрицу
  original.SetValue(0, 0, 10);

  // Проверяем, что вторая матрица осталась неизменной
  ASSERT_FALSE(original.EqMatrix(assigned));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}