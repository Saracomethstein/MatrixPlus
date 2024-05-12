#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

/*
 * To-DO:
 *  make
 *  testing
 */

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double** matrix_;

 public:
  //    CONSTRUCTORS    //
  S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

  S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
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

  S21Matrix(const S21Matrix& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocationMemory();
    CopyMatrix(other);
  }

  S21Matrix(S21Matrix&& other) noexcept
      : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

  ~S21Matrix() {
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
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  /**
   * @throws SubMatrixEx: Different matrix dimensions.
   */
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  /**
   * @throws MulMatrixEx: The number of columns of the first matrix is not equal
   * to the number of rows of the second matrix.
   */
  bool EqMatrix(const S21Matrix& other);

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
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  /**
   * @throws CalcComplementsEx: The matrix is not square.
   */
  S21Matrix InverseMatrix();
  /**
   * @throws InverseMatrix: Matrix determinant is 0.
   */
  S21Matrix MinorMatrix(int rows, int cols);

  // Tools for functions
  void PrintMatrix() const;
  void SetMatrix() const;
  void CopyMatrix(const S21Matrix& other);
  void CreateMatrix();
  void ZeroMatrix();
  void FreeMemory();
  void AllocationMemory();

  // Check correct matrix
  bool IsSquareMatrix() const;
  bool IsCorrect() const;
  bool IsEqualSizeMatrix(const S21Matrix& other) const;

  //    OVERLOADS    //
  S21Matrix& operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
  }

  S21Matrix operator+(const S21Matrix& other) {
    S21Matrix sum(*this);
    sum.SumMatrix(other);
    return sum;
  }

  S21Matrix& operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
  }

  S21Matrix operator-(const S21Matrix& other) const {
    S21Matrix sub(*this);
    sub.SubMatrix(other);
    return sub;
  }

  S21Matrix& operator*=(const double& other) {
    MulNumber(other);
    return *this;
  }

  S21Matrix operator*(const double& other) const noexcept {
    S21Matrix mul(*this);
    mul.MulNumber(other);
    return mul;
  }

  S21Matrix& operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
  }

  S21Matrix operator*(const S21Matrix& other) const {
    S21Matrix mul(*this);
    mul.MulMatrix(other);
    return mul;
  }

  S21Matrix& operator=(S21Matrix&& other) noexcept {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
    return *this;
  }

  S21Matrix& operator=(const S21Matrix& other) {
    if (&other != this) {
      FreeMemory();
      rows_ = other.rows_;
      cols_ = other.cols_;
      AllocationMemory();
      ZeroMatrix();
    }
    return *this;
  }

  bool operator==(const S21Matrix& other) noexcept { return EqMatrix(other); }

  double& operator()(int row, int col) const {
    if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
      throw std::out_of_range("InvalidIndexError: Index is out of range.");
    }
    return matrix_[row][col];
  }
};

#endif
