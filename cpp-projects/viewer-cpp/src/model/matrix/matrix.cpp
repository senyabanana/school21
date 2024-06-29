#include "matrix.h"

Matrix::Matrix() : rows_(0), columns_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
  AllocateMemory(rows_, columns_);
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), columns_(other.columns_), matrix_(nullptr) {
  AllocateMemory(rows_, columns_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other)
    : rows_(other.rows_), columns_(other.columns_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.columns_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() { FreeMemory(); }

void Matrix::MulMatrix(const Matrix& other) {
  double** result = AllocateMatrix(rows_, other.columns_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.columns_; j++) {
      for (int k = 0; k < columns_; k++) {
        result[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  FreeMemory();
  matrix_ = result;
  columns_ = other.columns_;
}

int Matrix::getRows() { return rows_; }

int Matrix::getColumns() { return columns_; }

Matrix& Matrix::operator=(const Matrix& other) {
  FreeMemory();
  rows_ = other.rows_;
  columns_ = other.columns_;
  AllocateMemory(rows_, columns_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

double& Matrix::operator()(int i, int j) { return matrix_[i][j]; }

void Matrix::AllocateMemory(int rows, int columns) {
  rows_ = rows;
  columns_ = columns;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[columns_]{0};
  }
}

void Matrix::FreeMemory() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

double** Matrix::AllocateMatrix(int rows, int columns) {
  double** result = new double*[rows];
  for (int i = 0; i < rows; i++) {
    result[i] = new double[columns]{0};
  }
  return result;
}

bool Matrix::EqMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < columns_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j] > EPS)) {
          return false;
        }
      }
    }
  }
  return true;
}

Matrix Matrix::Transpose() {
  double** result = AllocateMatrix(columns_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      result[j][i] = matrix_[i][j];
    }
  }
  FreeMemory();
  matrix_ = result;
  std::swap(rows_, columns_);
  return *this;
}
