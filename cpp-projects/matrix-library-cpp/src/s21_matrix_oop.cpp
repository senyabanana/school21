#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() : _rows(0), _columns(0), _matrix(nullptr) {}

S21Matrix::S21Matrix(int rows, int columns) : _rows(rows), _columns(columns) {
  AllocateMemory(_rows, _columns);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : _rows(other._rows), _columns(other._columns), _matrix(nullptr) {
  AllocateMemory(_rows, _columns);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      _matrix[i][j] = other._matrix[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : _rows(other._rows), _columns(other._columns), _matrix(other._matrix) {
  other._rows = 0;
  other._columns = 0;
  other._matrix = nullptr;
}

S21Matrix::~S21Matrix() { FreeMemory(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    return false;
  } else {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        if (fabs(_matrix[i][j] - other._matrix[i][j] > EPS)) {
          return false;
        }
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        _matrix[i][j] += other._matrix[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (_rows != other._rows || _columns != other._columns) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        _matrix[i][j] -= other._matrix[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      _matrix[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (_rows != other._columns || _columns != other._rows) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  } else {
    double** result = AllocateMatrix(_rows, other._columns);
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < other._columns; j++) {
        for (int k = 0; k < _columns; k++) {
          result[i][j] += _matrix[i][k] * other._matrix[k][j];
        }
      }
    }
    FreeMemory();
    _matrix = result;
    _columns = other._columns;
  }
}

S21Matrix S21Matrix::Transpose() {
  double** result = AllocateMatrix(_columns, _rows);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      result[j][i] = _matrix[i][j];
    }
  }
  FreeMemory();
  _matrix = result;
  std::swap(_rows, _columns);
  return *this;
}

S21Matrix S21Matrix::CalcComplements() {
  if (_rows != _columns) {
    throw std::invalid_argument("The matrix is not square");
  }
  double** result = AllocateMatrix(_rows, _columns);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      S21Matrix minor(_rows - 1, _columns - 1);
      GetMinor(minor, i, j);
      minor.Determinant();
      result[i][j] = pow(-1, (i + j)) * minor.Determinant();
    }
  }
  FreeMemory();
  _matrix = result;
  return *this;
}

double S21Matrix::Determinant() {
  if (_rows != _columns) {
    throw std::invalid_argument("The matrix is not square");
  }
  double result = 0;
  if (_rows == 1) {
    result = _matrix[0][0];
  } else {
    for (int i = 0; i < _columns; i++) {
      S21Matrix minor(_rows - 1, _columns - 1);
      GetMinor(minor, 0, i);
      if (i % 2) {
        result -= _matrix[0][i] * minor.Determinant();
      } else {
        result += _matrix[0][i] * minor.Determinant();
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (determinant == 0) {
    throw std::invalid_argument("The determinant of the matrix is 0");
  }
  S21Matrix temp1 = this->CalcComplements();
  S21Matrix temp2 = temp1.Transpose();
  temp2.MulNumber(1. / determinant);
  return temp2;
}