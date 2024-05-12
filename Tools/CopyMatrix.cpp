#include "../s21_matrix_oop.h"

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}