#include "../matrix.h"

Matrix Matrix::Transpose() {
  Matrix result(cols_, rows_);
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}