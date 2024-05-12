#include "../s21_matrix_oop.h"

void S21Matrix::SetMatrix() const {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      std::cin >> matrix_[i][j];
    }
  }
}