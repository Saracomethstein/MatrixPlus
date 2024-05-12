#include "../matrix.h"

void Matrix::PrintMatrix() const {
  std::cout << "Matrix Print:\n";
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      std::cout << matrix_[i][j] << ' ';
    }
    std::cout << '\n';
  }
}
