#include "../matrix.h"

void Matrix::CopyMatrix(const Matrix &other) {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}