#include "../matrix.h"

Matrix Matrix::InverseMatrix() {
  double determinant = 0.0;
  Matrix complements;
  Matrix transpose;

  determinant = Determinant();
  if (IsCorrect() && determinant != 0) {
    complements = CalcComplements();
    transpose = complements.Transpose();
    transpose.MulNumber(1.0 / determinant);
  } else {
    throw std::invalid_argument("InverseMatrix: Matrix determinant is 0.");
  }
  return transpose;
}