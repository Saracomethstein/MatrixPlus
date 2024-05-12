#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../matrix.h"

TEST(MatrixTest, EqMatrixElementsAreEqual) {
  Matrix matrix1;
  Matrix matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixElementsAreDifferent) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;
  matrix1(2, 0) = 2.0;
  matrix1(2, 1) = 3.0;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 3.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;
  matrix2(1, 2) = 3.0;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixSizesAreDifferent) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 3.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;
  matrix2(1, 2) = 3.0;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixEpsilon) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.000001;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.000000;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixOperatorElementsAreEqual) {
  Matrix matrix1;
  Matrix matrix2;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, SumMatrixBasic) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);

  for (int i = 0; i < matrix1.GetRows(); ++i) {
    for (int j = 0; j < matrix1.GetCols(); ++j) {
      matrix1(i, j) = i + j;
      matrix2(i, j) = i - j;
    }
  }

  matrix1.SumMatrix(matrix2);

  const Matrix const_matrix1 = std::move(matrix1);

  for (int i = 0; i < const_matrix1.GetRows(); ++i) {
    for (int j = 0; j < const_matrix1.GetCols(); ++j) {
      double expected_value = (i + j) + (i - j);
      EXPECT_DOUBLE_EQ(const_matrix1(i, j), expected_value);
    }
  }
}

TEST(MatrixTest, SumMatrixMatricesOfDifferentSizes) {
  Matrix matrix1;
  matrix1.ResizeCols(1);
  Matrix matrix2;
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(MatrixTest, SumOperatorMatrix) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  Matrix actual(3, 3);
  Matrix expected(3, 3);
  actual = matrix1 + matrix2;
  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, SumOperatorMatrixMatricesOfDifferentSizes) {
  Matrix matrix1;
  matrix1.ResizeCols(1);
  Matrix matrix2;
  EXPECT_THROW(matrix1 + matrix2, std::invalid_argument);
}

TEST(MatrixTest, AdditionAssignmentOperatorMatrix) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  Matrix expected_matrix(3, 3);

  for (int i = 0; i < expected_matrix.GetRows(); ++i) {
    for (int j = 0; j < expected_matrix.GetCols(); ++j) {
      double value = 2 * matrix1(i, j);
      expected_matrix(i, j) = value;
    }
  }

  Matrix actual_result = matrix1 += matrix2;

  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, AdditionAssignmentOperatorMatricesOfDifferentSizes) {
  Matrix matrix1;
  matrix1.ResizeCols(1);
  Matrix matrix2;

  EXPECT_THROW(matrix1 += matrix2, std::invalid_argument);
}

TEST(MatrixTest, SubMatrixBasic) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  Matrix expected_matrix(3, 3);
  for (int i = 0; i < expected_matrix.GetRows(); ++i) {
    for (int j = 0; j < expected_matrix.GetCols(); ++j) {
      expected_matrix(i, j) = 0.0;
    }
  }
  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, SubMatrixMatricesOfDifferentSizes) {
  Matrix matrix1;
  matrix1.ResizeCols(1);
  Matrix matrix2;
  Matrix expected_matrix;
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(MatrixTest, SubOperatorMatrix) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  Matrix expected_matrix(3, 3);
  for (int i = 0; i < expected_matrix.GetRows(); ++i) {
    for (int j = 0; j < expected_matrix.GetCols(); ++j) {
      expected_matrix(i, j) = 0.0;
    }
  }
  Matrix actual_result = matrix1 - matrix2;
  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, SubOperatorMatricesOfDifferentSizes) {
  Matrix matrix1;
  matrix1.ResizeCols(1);
  Matrix matrix2;

  EXPECT_THROW(matrix1 - matrix2, std::invalid_argument);
}

TEST(MatrixTest, DifferenceAssignmentOperatorMatrix) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  Matrix expected_matrix(3, 3);
  for (int i = 0; i < expected_matrix.GetRows(); ++i) {
    for (int j = 0; j < expected_matrix.GetCols(); ++j) {
      expected_matrix(i, j) = 0.0;
    }
  }
  Matrix actual_result = matrix1 -= matrix2;
  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, DifferenceAssignmentOperatorMatricesOfDifferentSizes) {
  Matrix matrix1;
  matrix1.ResizeCols(1);
  Matrix matrix2;

  EXPECT_THROW(matrix1 -= matrix2, std::invalid_argument);
}

TEST(MatrixTest, MultByNumberBasic) {
  Matrix matrix1(3, 3);
  Matrix expected_matrix(3, 3);
  for (int i = 0; i < expected_matrix.GetRows(); ++i) {
    for (int j = 0; j < expected_matrix.GetCols(); ++j) {
      expected_matrix(i, j) = matrix1(i, j) * 3.0;
    }
  }
  matrix1.MulNumber(3.0);
  EXPECT_TRUE(matrix1.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultByNumberOperator) {
  Matrix matrix1(3, 3);
  Matrix expected_matrix(3, 3);
  for (int i = 0; i < expected_matrix.GetRows(); ++i) {
    for (int j = 0; j < expected_matrix.GetCols(); ++j) {
      expected_matrix(i, j) = matrix1(i, j) * 3.0;
    }
  }
  Matrix actual_result = matrix1 * 3.0;
  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultiplicationAssignmentOperatorMultNumber) {
  Matrix matrix1(3, 3);
  Matrix expected_matrix(3, 3);
  for (int i = 0; i < expected_matrix.GetRows(); ++i) {
    for (int j = 0; j < expected_matrix.GetCols(); ++j) {
      expected_matrix(i, j) = matrix1(i, j) * 3.0;
    }
  }
  Matrix actual_result = matrix1 *= 3.0;
  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultMatrixBasic) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;
  matrix1(2, 0) = 2.0;
  matrix1(2, 1) = 3.0;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;
  matrix2(1, 2) = 3.0;

  Matrix expected_matrix(3, 3);

  expected_matrix(0, 0) = 3.0;
  expected_matrix(0, 1) = 6.0;
  expected_matrix(0, 2) = 9.0;
  expected_matrix(1, 0) = 4.0;
  expected_matrix(1, 1) = 8.0;
  expected_matrix(1, 2) = 12.0;
  expected_matrix(2, 0) = 5.0;
  expected_matrix(2, 1) = 10.0;
  expected_matrix(2, 2) = 15.0;

  Matrix actual_result = matrix1;
  actual_result.MulMatrix(matrix2);

  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultMatrixMultIndalidMatrixSizeException) {
  Matrix matrix1(3, 1);
  matrix1(0, 0) = 1.0;
  matrix1(1, 0) = 3.0;
  matrix1(2, 0) = 2.0;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;
  matrix2(1, 2) = 3.0;

  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

TEST(MatrixTest, MultMatrixOperator) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;
  matrix1(2, 0) = 2.0;
  matrix1(2, 1) = 3.0;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;
  matrix2(1, 2) = 3.0;

  Matrix expected_matrix(3, 3);
  expected_matrix(0, 0) = 3.0;
  expected_matrix(0, 1) = 6.0;
  expected_matrix(0, 2) = 9.0;
  expected_matrix(1, 0) = 4.0;
  expected_matrix(1, 1) = 8.0;
  expected_matrix(1, 2) = 12.0;
  expected_matrix(2, 0) = 5.0;
  expected_matrix(2, 1) = 10.0;
  expected_matrix(2, 2) = 15.0;

  Matrix actual_result = matrix1 * matrix2;

  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, MultiplicationAssignmentOperatorMultMatrix) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;
  matrix1(2, 0) = 2.0;
  matrix1(2, 1) = 3.0;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;
  matrix2(1, 2) = 3.0;

  Matrix expected_matrix(3, 3);
  expected_matrix(0, 0) = 3.0;
  expected_matrix(0, 1) = 6.0;
  expected_matrix(0, 2) = 9.0;
  expected_matrix(1, 0) = 4.0;
  expected_matrix(1, 1) = 8.0;
  expected_matrix(1, 2) = 12.0;
  expected_matrix(2, 0) = 5.0;
  expected_matrix(2, 1) = 10.0;
  expected_matrix(2, 2) = 15.0;

  Matrix actual_result = matrix1 *= matrix2;

  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, EqMatrixOperator) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;
  matrix1(2, 0) = 2.0;
  matrix1(2, 1) = 3.0;

  Matrix matrix2(3, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 1.0;
  matrix2(2, 0) = 2.0;
  matrix2(2, 1) = 3.0;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, TransposeMatrixBasic) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 1.0;
  matrix1(2, 0) = 2.0;
  matrix1(2, 1) = 3.0;

  Matrix expected_matrix(2, 3);
  expected_matrix(0, 0) = 1.0;
  expected_matrix(0, 1) = 3.0;
  expected_matrix(0, 2) = 2.0;
  expected_matrix(1, 0) = 2.0;
  expected_matrix(1, 1) = 1.0;
  expected_matrix(1, 2) = 3.0;

  Matrix transposed_matrix = matrix1.Transpose();

  EXPECT_TRUE(transposed_matrix.EqMatrix(expected_matrix));
}

TEST(MatrixTest, CalcComplementsMatrixBasic00) {
  Matrix input_matrix(1, 1);
  input_matrix(0, 0) = 21.0;

  Matrix expected_result(1, 1);
  expected_result(0, 0) = 21.0;

  Matrix actual_result = input_matrix.CalcComplements();

  EXPECT_TRUE(actual_result.EqMatrix(expected_result));
}

TEST(MatrixTest, CalcComplementsMatrixBasic02) {
  Matrix input_matrix(3, 3);
  input_matrix(0, 0) = 1.0;
  input_matrix(0, 1) = 2.0;
  input_matrix(0, 2) = 3.0;
  input_matrix(1, 0) = 1.0;
  input_matrix(1, 1) = 3.0;
  input_matrix(1, 2) = 2.0;
  input_matrix(2, 0) = 5.0;
  input_matrix(2, 1) = 2.0;
  input_matrix(2, 2) = 1.0;

  Matrix expected_matrix(3, 3);
  expected_matrix(0, 0) = -1.0;
  expected_matrix(0, 1) = 9.0;
  expected_matrix(0, 2) = -13.0;
  expected_matrix(1, 0) = 4.0;
  expected_matrix(1, 1) = -14.0;
  expected_matrix(1, 2) = 8.0;
  expected_matrix(2, 0) = -5.0;
  expected_matrix(2, 1) = 1.0;
  expected_matrix(2, 2) = 1.0;

  Matrix actual_result = input_matrix.CalcComplements();

  EXPECT_TRUE(actual_result.EqMatrix(expected_matrix));
}

TEST(MatrixTest, CalcComplementsMatrixNotSquaredMatrixException) {
  Matrix input_matrix(3, 1);

  EXPECT_THROW(input_matrix.CalcComplements(), std::invalid_argument);
}

TEST(MatrixTest, DeterminantMatrixBasic00) {
  Matrix input_matrix(3, 3);
  input_matrix(0, 0) = 21.0;
  input_matrix(0, 1) = 42.0;
  input_matrix(0, 2) = 13.0;
  input_matrix(1, 0) = 21.0;
  input_matrix(1, 1) = 42.0;
  input_matrix(1, 2) = 13.0;
  input_matrix(2, 0) = 21.0;
  input_matrix(2, 1) = 42.0;
  input_matrix(2, 2) = 13.0;

  double expected_result = 0.0;

  double actual_result = input_matrix.Determinant();

  ASSERT_DOUBLE_EQ(expected_result, actual_result);
}

TEST(MatrixTest, DeterminantMatrixBasic01) {
  Matrix input_matrix(3, 3);
  input_matrix(0, 0) = 2.0;
  input_matrix(0, 1) = 5.0;
  input_matrix(0, 2) = 7.0;
  input_matrix(1, 0) = 6.0;
  input_matrix(1, 1) = 3.0;
  input_matrix(1, 2) = 4.0;
  input_matrix(2, 0) = 5.0;
  input_matrix(2, 1) = -2.0;
  input_matrix(2, 2) = -3.0;

  double expected_result = -1.0;

  double actual_result = input_matrix.Determinant();

  ASSERT_DOUBLE_EQ(expected_result, actual_result);
}

TEST(MatrixTest, DeterminantMatrixBasic02) {
  Matrix input_matrix(1, 1);
  input_matrix(0, 0) = 21.0;

  double expected_result = 21.0;

  double actual_result = input_matrix.Determinant();

  ASSERT_DOUBLE_EQ(expected_result, actual_result);
}

TEST(MatrixTest, DeterminantNotSquaredMatrixException) {
  Matrix input_matrix(3, 1);

  EXPECT_THROW(input_matrix.Determinant(), std::invalid_argument);
}

TEST(MatrixTest, InverseMatrixBasic) {
  Matrix input(3, 3);
  input(0, 0) = 2.0;
  input(0, 1) = 5.0;
  input(0, 2) = 7.0;
  input(1, 0) = 6.0;
  input(1, 1) = 3.0;
  input(1, 2) = 4.0;
  input(2, 0) = 5.0;
  input(2, 1) = -2.0;
  input(2, 2) = -3.0;

  Matrix expected(3, 3);
  expected(0, 0) = 1.0;
  expected(0, 1) = -1.0;
  expected(0, 2) = 1.0;
  expected(1, 0) = -38.0;
  expected(1, 1) = 41.0;
  expected(1, 2) = -34.0;
  expected(2, 0) = 27.0;
  expected(2, 1) = -29.0;
  expected(2, 2) = 24.0;

  Matrix actual = input.InverseMatrix();

  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, InverseMatrixZeroException) {
  Matrix input(3, 3);
  input(0, 0) = 1.0;
  input(0, 1) = 2.0;
  input(0, 2) = 3.0;
  input(1, 0) = 4.0;
  input(1, 1) = 5.0;
  input(1, 2) = 6.0;
  input(2, 0) = 7.0;
  input(2, 1) = 8.0;
  input(2, 2) = 9.0;

  EXPECT_THROW(input.InverseMatrix(), std::invalid_argument);
}

TEST(MatrixTest, ParametrizedConstructorTest) {
  Matrix actual(3, 3);

  Matrix expected(3, 3);
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      expected(row, col) = 0.0;
    }
  }

  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, ParametrizedConstructorTestInvalidIndex00) {
  EXPECT_THROW(Matrix expected(2, -42), std::invalid_argument);
}

TEST(MatrixTest, ParametrizedConstructorTestInvalidIndex01) {
  EXPECT_THROW(Matrix expected(-42, -42), std::invalid_argument);
}

TEST(MatrixTest, ParametrizedConstructorTestInvalidIndex03) {
  EXPECT_THROW(Matrix expected(-42, 42), std::invalid_argument);
}

TEST(MatrixTest, RectangleMatrixTestRows) {
  Matrix actual(3, 3);
  actual.ResizeRows(5);

  Matrix expected(5, 3);
  for (int row = 0; row < 5; ++row) {
    for (int col = 0; col < 3; ++col) {
      expected(row, col) = 0.0;
    }
  }

  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, RectangleMatrixTestCols) {
  Matrix actual(3, 3);
  actual.ResizeCols(5);

  Matrix expected(3, 5);
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 5; ++col) {
      expected(row, col) = 0.0;
    }
  }

  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, SetRowsToBelowZeroTest) {
  Matrix actual(3, 3);
  EXPECT_THROW(actual.ResizeRows(-5), std::invalid_argument);
}

TEST(MatrixTest, SetColsToBelowZeroTest) {
  Matrix actual(3, 3);
  EXPECT_THROW(actual.ResizeCols(-5), std::invalid_argument);
}

TEST(MatrixTest, GetInvalidElementTest) {
  Matrix actual(3, 3);
  EXPECT_THROW(actual(-5, 0), std::out_of_range);
}

TEST(MatrixTest, SetInvalidElementTest) {
  Matrix actual(3, 3);
  EXPECT_THROW(actual(-5, 0) = 42.0, std::out_of_range);
}

TEST(MatrixTest, CopyConstructorTest) {
  Matrix input(3, 3);
  input(0, 0) = 1.0;
  input(0, 1) = 2.0;
  input(0, 2) = 3.0;
  input(1, 0) = 4.0;
  input(1, 1) = 5.0;
  input(1, 2) = 6.0;
  input(2, 0) = 7.0;
  input(2, 1) = 8.0;
  input(2, 2) = 9.0;

  Matrix expected(3, 3);
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      expected(row, col) = input(row, col);
    }
  }

  Matrix actual(input);

  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, CopyAssignmentOperatorTest) {
  Matrix input(3, 3);
  input(0, 0) = 1.0;
  input(0, 1) = 2.0;
  input(0, 2) = 3.0;
  input(1, 0) = 4.0;
  input(1, 1) = 5.0;
  input(1, 2) = 6.0;
  input(2, 0) = 7.0;
  input(2, 1) = 8.0;
  input(2, 2) = 9.0;

  Matrix expected(3, 3);
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      expected(row, col) = input(row, col);
    }
  }

  Matrix actual = input;

  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, MovementConstructorTest) {
  Matrix input(3, 3);
  input(0, 0) = 1.0;
  input(0, 1) = 2.0;
  input(0, 2) = 3.0;
  input(1, 0) = 4.0;
  input(1, 1) = 5.0;
  input(1, 2) = 6.0;
  input(2, 0) = 7.0;
  input(2, 1) = 8.0;
  input(2, 2) = 9.0;

  Matrix expected(3, 3);
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      expected(row, col) = input(row, col);
    }
  }

  Matrix actual(std::move(input));

  EXPECT_TRUE(actual.EqMatrix(expected));
}

TEST(MatrixTest, DestructorTest) {
  Matrix input(3, 3);
  input(0, 0) = 1.0;
  input(0, 1) = 2.0;
  input(0, 2) = 3.0;
  input(1, 0) = 4.0;
  input(1, 1) = 5.0;
  input(1, 2) = 6.0;
  input(2, 0) = 7.0;
  input(2, 1) = 8.0;
  input(2, 2) = 9.0;

  input.~Matrix();

  int rows = input.GetRows();
  int cols = input.GetCols();
  bool is_null = input.IsNull();

  ASSERT_EQ(rows, 0);
  ASSERT_EQ(cols, 0);
  EXPECT_TRUE(is_null);
}

TEST(MatrixTest, IndexationByMatrixElements) {
  Matrix input(3, 3);
  input(0, 0) = 1.0;
  input(0, 1) = 2.0;
  input(0, 2) = 3.0;
  input(1, 0) = 4.0;
  input(1, 1) = 5.0;
  input(1, 2) = 6.0;
  input(2, 0) = 7.0;
  input(2, 1) = 8.0;
  input(2, 2) = 9.0;

  double actual = input(1, 1);
  double expected = 5.0;

  ASSERT_DOUBLE_EQ(expected, actual);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
