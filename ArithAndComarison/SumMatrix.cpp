#include "../s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (IsEqualSizeMatrix(other)) {
    for (int i = 0; i != other.rows_; ++i) {
      for (int j = 0; j != other.cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument("SumMatrixEx: Different matrix dimensions.");
  }
}