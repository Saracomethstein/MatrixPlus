#include "../s21_matrix_oop.h"

void S21Matrix::FreeMemory() {
  rows_ = 0;
  cols_ = 0;
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::AllocationMemory() {
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