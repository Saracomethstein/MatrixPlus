#include "../matrix.h"

void Matrix::SetMatrix() const {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      std::cin >> matrix_[i][j];
    }
  }
}