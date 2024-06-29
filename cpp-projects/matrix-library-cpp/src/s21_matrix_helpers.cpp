#include "s21_matrix_oop.hpp"

void S21Matrix::AllocateMemory(int rows, int columns) {
  _rows = rows;
  _columns = columns;
  _matrix = new double *[_rows];
  for (int i = 0; i < _rows; i++) {
    _matrix[i] = new double[_columns]{0};
  }
}

void S21Matrix::FreeMemory() {
  for (int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
  _matrix = nullptr;
}

void S21Matrix::PrintMatrix() const {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      std::cout << _matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void S21Matrix::SetValue(int rows, int columns, double value) {
  if (rows >= 0 && rows < _rows && columns >= 0 && columns < _columns) {
    _matrix[rows][columns] = value;
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

void S21Matrix::SetRows(int new_rows) { MutateMatrix(new_rows, _columns); }

void S21Matrix::SetColumns(int new_columns) {
  MutateMatrix(_rows, new_columns);
}

void S21Matrix::MutateMatrix(int new_rows, int new_columns) {
  double **mutate = AllocateMatrix(new_rows, new_columns);
  for (int i = 0; i < std::min(_rows, new_rows); i++) {
    for (int j = 0; j < std::min(_columns, new_columns); j++) {
      mutate[i][j] = _matrix[i][j];
    }
  }
  FreeMemory();
  _matrix = mutate;
  _rows = new_rows;
  _columns = new_columns;
}

double S21Matrix::GetRows() { return _rows; }

double S21Matrix::GetColumns() { return _columns; }

double S21Matrix::GetValue(int rows, int columns) {
  if (rows >= 0 && rows < _rows && columns >= 0 && columns < _columns) {
    return _matrix[rows][columns];
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

double **S21Matrix::AllocateMatrix(int rows, int columns) {
  double **result = new double *[rows];
  for (int i = 0; i < rows; i++) {
    result[i] = new double[columns]{0};
  }
  return result;
}

void S21Matrix::GetMinor(S21Matrix &minor, int rows, int columns) {
  int index_rows = 0, index_columns = 0;
  for (int i = 0; i < _rows; i++) {
    if (i == rows) {
      continue;
    }
    index_columns = 0;
    for (int j = 0; j < _columns; j++) {
      if (j == columns) {
        continue;
      }
      minor._matrix[index_rows][index_columns] = _matrix[i][j];
      index_columns++;
    }
    index_rows++;
  }
}