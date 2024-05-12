#include "../matrix.h"

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

bool Matrix::IsNull() const { return !matrix_; }

void Matrix::ResizeRows(int rows) {
  if (rows < 0) {
    throw std::invalid_argument("Rows never be negative.");
  }
  Matrix result(rows, cols_);
  int resultRows = rows > rows_ ? rows_ : rows;
  for (int i = 0; i < resultRows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(result);
}

void Matrix::ResizeCols(int cols) {
  if (cols < 0) {
    throw std::invalid_argument("Cols never be negative.");
  }
  Matrix result(rows_, cols);
  int resultCols = cols < cols_ ? cols : cols_;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < resultCols; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(result);
}

void Matrix::ResizeMatrix(int rows, int cols) {
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument("Rows and cols never be negative.");
  }
  this->ResizeRows(rows);
  this->ResizeCols(cols);
}