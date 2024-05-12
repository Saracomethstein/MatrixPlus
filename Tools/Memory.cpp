#include "../matrix.h"

void Matrix::FreeMemory() {
  rows_ = 0;
  cols_ = 0;
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void Matrix::AllocationMemory() {
  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}