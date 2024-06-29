#ifndef _S21_MATRIX_OOP_H_
#define _S21_MATRIX_OOP_H_

#include <math.h>

#include <exception>
#include <iostream>

#define EPS 1e-07

class S21Matrix {
 private:
  int _rows;
  int _columns;
  double** _matrix;

  void AllocateMemory(int rows, int columns);
  void FreeMemory();
  double** AllocateMatrix(int rows, int columns);
  void MutateMatrix(int new_rows, int new_columns);
  void GetMinor(S21Matrix& minor, int rows, int columns);

 public:
  S21Matrix();
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double& operator()(int i, int j);

  void PrintMatrix() const;
  void SetValue(int rows, int columns, double value);
  void SetRows(int new_rows);
  void SetColumns(int new_columns);
  double GetRows();
  double GetColumns();
  double GetValue(int rows, int columns);
};

#endif