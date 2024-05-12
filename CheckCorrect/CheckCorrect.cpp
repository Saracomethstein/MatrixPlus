#include "../s21_matrix_oop.h"

bool S21Matrix::IsSquareMatrix() const { return rows_ == cols_ ? true : false; }

bool S21Matrix::IsEqualSizeMatrix(const S21Matrix& other) const {
  return rows_ == other.rows_ && cols_ == other.cols_ ? true : false;
}

bool S21Matrix::IsCorrect() const {
  return rows_ < 0 || cols_ < 0 ? false : true;
}