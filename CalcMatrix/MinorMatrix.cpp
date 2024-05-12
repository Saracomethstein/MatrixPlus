#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::MinorMatrix(int rows, int cols) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  int rows_i = 0;
  int columns_j = 0;

  for (int i = 0; i != result.rows_; ++i) {
    if (i == rows) rows_i++;
    columns_j = 0;
    for (int j = 0; j != result.cols_; ++j) {
      if (j == cols) columns_j++;
      result.matrix_[i][j] = matrix_[i + rows_i][j + columns_j];
    }
  }
  return result;
}