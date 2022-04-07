#include "../include/matrix.h"

Matrix::Matrix() {
  _rows = 1;
  _cols = 1;
  values = new float* [1];
}

Matrix::~Matrix() {
  for (int i = 0; i < _rows; i++) {
    delete[] values[i];
  }
  delete[] values;
}

Matrix::Matrix(int rows, int cols) {
  _rows = rows;
  _cols = cols;
  values = new float* [rows];
  for (int i = 0; i < rows; i++) {
    values[i] = new float[cols];
  }
}

Matrix Matrix::identity(int rows, int cols) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result.set(i, j, (i == j) ? 1 : 0);
      }
    }
    return result;
  }

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result(_rows, other.cols());
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other.cols(); j++) {
      float sum = 0;
      for (int k = 0; k < _cols; k++) {
        sum += values[i][k] * other.values[k][j];
      }
      result.set(i, j, sum);
    }
  }
  return result;
}

Matrix Matrix::operator*(float scalar) const {
  Matrix result(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      result.set(i, j, values[i][j] * scalar);
    }
  }
  return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (_rows != other._rows || _cols != other._cols) {
    for (int i = 0; i < _rows; i++) {
      delete[] values[i];
    }
    delete[] values;
    _rows = other._rows;
    _cols = other._cols;
    values = new float* [_rows];
    for (int i = 0; i < _rows; i++) {
      values[i] = new float[_cols];
    }
  }
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      values[i][j] = other.values[i][j];
    }
  }
  return *this;
}
