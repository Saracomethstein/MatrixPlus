#include "../matrix.h"

void Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i != rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
  ZeroMatrix();
}