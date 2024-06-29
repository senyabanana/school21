#include "s21_matrix_oop.hpp"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size");
  }
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size");
  }
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  if (_rows != other._columns || _columns != other._rows) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  FreeMemory();
  _rows = other._rows;
  _columns = other._columns;
  AllocateMemory(_rows, _columns);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      _matrix[i][j] = other._matrix[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size");
  }
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size");
  }
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  if (_rows != other._columns || _columns != other._rows) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i > _rows || j > _columns || i < 0 || j < 0) {
    throw std::out_of_range("The index is outside the matrix");
  }
  return _matrix[i][j];
}