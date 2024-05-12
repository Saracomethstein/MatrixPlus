#include "../matrix.h"

void Matrix::ZeroMatrix() {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      matrix_[i][j] = 0.0;
    }
  }
}