#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

#include <iostream>
#include <vector>

#define EPS 1e-04

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int columns);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  Matrix Transpose();
  bool EqMatrix(const Matrix& other);
  void MulMatrix(const Matrix& other);
  int getRows();
  int getColumns();

  Matrix& operator=(const Matrix& other);
  double& operator()(int i, int j);

 private:
  int rows_;
  int columns_;
  double** matrix_;

  void AllocateMemory(int rows, int columns);
  void FreeMemory();
  double** AllocateMatrix(int rows, int columns);
};

#endif
