#include "../s21_matrix_oop.h"

double S21Matrix::Determinant() {
  double result = 0.0;
  S21Matrix minor;
  if (IsCorrect() && IsSquareMatrix()) {
    if (rows_ == 1) {
      result = matrix_[0][0];
    } else if (rows_ == 2) {
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
      for (int i = 0; i < cols_; ++i) {
        minor = MinorMatrix(0, i);
        result += matrix_[0][i] * minor.Determinant() * pow(-1, i);
      }
    }
  } else {
    throw std::invalid_argument("DeterminantEx: The matrix is not square.");
  }
  return result;
}
