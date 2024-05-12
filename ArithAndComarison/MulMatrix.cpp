#include "../matrix.h"

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ == other.rows_) {
    Matrix res(rows_, other.cols_);
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != other.cols_; ++j) {
        for (int k = 0; k != other.rows_; ++k) {
          res.matrix_[i][j] += other.matrix_[k][j] * matrix_[i][k];
        }
      }
    }
    *this = std::move(res);
  } else {
    throw std::invalid_argument(
        "MulMatrixEx: The number of columns of the first matrix is not equal\n"
        "   * to the number of rows of the second matrix.");
  }
}