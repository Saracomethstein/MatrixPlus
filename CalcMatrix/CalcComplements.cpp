#include "../matrix.h"

Matrix Matrix::CalcComplements() {
  Matrix result;
  Matrix minor;

  if (IsCorrect() && IsSquareMatrix()) {
    result = Matrix(rows_, cols_);
    if (cols_ == 1) {
      result.matrix_[0][0] = matrix_[0][0];
    } else {
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
          minor = MinorMatrix(i, j);
          result.matrix_[i][j] = minor.Determinant();
          result.matrix_[i][j] *= pow(-1, (i + j));
        }
      }
    }
  } else {
    throw std::invalid_argument("CalcComplementsEx: The matrix is not square.");
  }

  return result;
}