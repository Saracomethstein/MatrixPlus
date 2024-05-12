#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = 0.0;
  S21Matrix complements;
  S21Matrix transpose;

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