#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

class Matrix {
 private:
  int rows_;
  int cols_;
  double** matrix_;

 public:
  //    CONSTRUCTORS    //
  Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

  Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows_ < 0 || cols_ < 0) {
      throw std::invalid_argument("Argument is not correct.");
    }
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
    }

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = 0.0;
      }
    }
  }

  Matrix(const Matrix& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocationMemory();
    CopyMatrix(other);
  }

  Matrix(Matrix&& other) noexcept
      : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

  ~Matrix() {
    rows_ = 0;
    cols_ = 0;
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }

    delete[] matrix_;
    matrix_ = nullptr;
  }

  //    METHODS    //

  // Arithmetic and comparison functions
  /**
   * @throws SumMatrixEx: Different matrix dimensions.
   */
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  /**
   * @throws SubMatrixEx: Different matrix dimensions.
   */
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  /**
   * @throws MulMatrixEx: The number of columns of the first matrix is not equal
   * to the number of rows of the second matrix.
   */
  bool EqMatrix(const Matrix& other);

  // Resize matrix and get private fields
  int GetRows() const;
  int GetCols() const;
  bool IsNull() const;
  void ResizeMatrix(int rows, int cols);
  void ResizeRows(int rows);
  void ResizeCols(int cols);

  // Calc functions
  double Determinant();
  /**
   * @throws DeterminantEx: The matrix is not square.
   */
  Matrix Transpose();
  Matrix CalcComplements();
  /**
   * @throws CalcComplementsEx: The matrix is not square.
   */
  Matrix InverseMatrix();
  /**
   * @throws InverseMatrix: Matrix determinant is 0.
   */
  Matrix MinorMatrix(int rows, int cols);

  // Tools for functions
  void PrintMatrix() const;
  void SetMatrix() const;
  void CopyMatrix(const Matrix& other);
  void CreateMatrix();
  void ZeroMatrix();
  void FreeMemory();
  void AllocationMemory();

  // Check correct matrix
  bool IsSquareMatrix() const;
  bool IsCorrect() const;
  bool IsEqualSizeMatrix(const Matrix& other) const;

  //    OVERLOADS    //
  Matrix& operator+=(const Matrix& other) {
    SumMatrix(other);
    return *this;
  }

  Matrix operator+(const Matrix& other) {
    Matrix sum(*this);
    sum.SumMatrix(other);
    return sum;
  }

  Matrix& operator-=(const Matrix& other) {
    SubMatrix(other);
    return *this;
  }

  Matrix operator-(const Matrix& other) const {
    Matrix sub(*this);
    sub.SubMatrix(other);
    return sub;
  }

  Matrix& operator*=(const double& other) {
    MulNumber(other);
    return *this;
  }

  Matrix operator*(const double& other) const noexcept {
    Matrix mul(*this);
    mul.MulNumber(other);
    return mul;
  }

  Matrix& operator*=(const Matrix& other) {
    MulMatrix(other);
    return *this;
  }

  Matrix operator*(const Matrix& other) const {
    Matrix mul(*this);
    mul.MulMatrix(other);
    return mul;
  }

  Matrix& operator=(Matrix&& other) noexcept {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
    return *this;
  }

  Matrix& operator=(const Matrix& other) {
    if (&other != this) {
      FreeMemory();
      rows_ = other.rows_;
      cols_ = other.cols_;
      AllocationMemory();
      ZeroMatrix();
    }
    return *this;
  }

  bool operator==(const Matrix& other) noexcept { return EqMatrix(other); }

  double& operator()(int row, int col) const {
    if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
      throw std::out_of_range("InvalidIndexError: Index is out of range.");
    }
    return matrix_[row][col];
  }
};
#endif
