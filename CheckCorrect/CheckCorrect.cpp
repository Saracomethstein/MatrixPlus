#include "../matrix.h"

bool Matrix::IsSquareMatrix() const { return rows_ == cols_ ? true : false; }

bool Matrix::IsEqualSizeMatrix(const Matrix& other) const {
  return rows_ == other.rows_ && cols_ == other.cols_ ? true : false;
}

bool Matrix::IsCorrect() const {
  return rows_ < 0 || cols_ < 0 ? false : true;
}