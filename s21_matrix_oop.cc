#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>

#define EPS 1e-7

// CONSTRUCTIONS

// Construction default 5x5
S21Matrix::S21Matrix() : S21Matrix(5, 5) {}

// Construction with parametrs
S21Matrix::S21Matrix(int row, int col)
    : matrix_(nullptr), rows_(row), cols_(col) {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::out_of_range("Row or column out of range");
  matrix_ = new double *[rows_];
  if (!matrix_) throw std::bad_alloc();
  *matrix_ = new double[cols_ * rows_]{0};

  if (*matrix_) {
    for (int i = 1; i < rows_; ++i) {
      matrix_[i] = *matrix_ + i * cols_;
    }
  } else {
    delete[] matrix_;
    throw std::bad_alloc();
  }
}

// Constructions assignment
S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  if (!other.matrix_ || !*other.matrix_ || other.rows_ <= 0 || other.cols_ <= 0)
    throw std::invalid_argument("Incorrect");

  for (int k = 0; k < rows_; ++k) {
    for (int m = 0; m < cols_; ++m) {
      matrix_[k][m] = other.matrix_[k][m];
    }
  }
}

// Construction move
S21Matrix::S21Matrix(S21Matrix &&other) {
  if (!other.matrix_ || !*other.matrix_ || other.rows_ <= 0 || other.cols_ <= 0)
    throw std::invalid_argument("Incorrect");
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Destructor
S21Matrix::~S21Matrix() {
  if (matrix_) {
    if (*matrix_) delete[] * matrix_;
    delete[] matrix_;
  }
}

std::ostream &operator<<(std::ostream &output, const S21Matrix &m) {
  for (int i = 0; i < m.rows_; ++i) {
    for (int k = 0; k < m.cols_; ++k) {
      output << (m.matrix_)[i][k] << (k < m.cols_ - 1 ? " " : "");
    }
    output << '\n';
  }
  return output;
}

void S21Matrix::Clear() {
  rows_ = 0;
  cols_ = 0;
  if (matrix_) {
    if (*matrix_) delete[] * matrix_;
    delete[] matrix_;
  }
  matrix_ = nullptr;
}

// Check for correct matrix(matrix_ and *matrix_ != nullptr and row_ and cols_
// >= 1)
bool S21Matrix::IsCorrect() {
  bool res = true;
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0) res = false;
  return res;
}

// Fill matrix value(if val = 0 or not val, matrix filled nuture number from 1
// to ...)
void S21Matrix::Fill(int val) {
  if (IsCorrect()) {
    if (val == 0) val = 1;
    int c = GetCols();
    int r = GetRows();
    for (int i = 0; i < r; ++i) {
      for (int k = 0; k < c; ++k) {
        matrix_[i][k] = (i * c + k + 1) * val;
      }
    }
  }
}

// Fill from array
void S21Matrix::FillArr(double *arr, int size) {
  if (IsCorrect()) {
    int len = GetCols() * GetRows();
    for (int i = 0; i < len && i < size; ++i) {
      (*matrix_)[i] = arr[i];
    }
  }
}

// EqMatrix
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0 || !other.matrix_ ||
      !*other.matrix_ || other.rows_ <= 0 || other.cols_ <= 0)
    throw std::invalid_argument("Incorrect");

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else if (matrix_ == other.matrix_) {
    res = true;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int k = 0; k < cols_; ++k) {
        if (fabs(matrix_[i][k] - other.matrix_[i][k]) > EPS) {
          res = false;
          k = cols_ - 1;
          i = rows_ - 1;
        }
      }
    }
  }
  return res;
}

// SumMatrix
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!matrix_ || !*matrix_ || !other.matrix_ || !*other.matrix_) {
    throw std::invalid_argument("Incorrect");
  } else if (rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0 ||
             rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Incorrect");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int k = 0; k < cols_; k++) {
        matrix_[i][k] += other.matrix_[i][k];
      }
    }
  }
}

// SubMatrix
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!matrix_ || !*matrix_ || !other.matrix_ || !*other.matrix_) {
    throw std::invalid_argument("Incorrect matrices");
  } else if (rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0 ||
             rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Incorrect matrices");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int k = 0; k < cols_; k++) {
        matrix_[i][k] -= other.matrix_[i][k];
      }
    }
  }
}

// MulNumber
void S21Matrix::MulNumber(const double num) {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Incorrect matrix");

  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      matrix_[i][k] *= num;
    }
  }
}

// MulMatrix
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (!matrix_ || !*matrix_ || !other.matrix_ || !*other.matrix_ ||
      cols_ != other.rows_ || cols_ <= 0 || other.rows_ <= 0)
    throw std::invalid_argument("Incorrect");
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < other.cols_; k++) {
      for (int m = 0; m < cols_; m++) {
        tmp.matrix_[i][k] += matrix_[i][m] * other.matrix_[m][k];
      }
    }
  }
  *this = (std::move(tmp));
}

// Transpose
S21Matrix S21Matrix::Transpose() {
  if (!matrix_ || !*matrix_ || !cols_ || !rows_)
    throw std::invalid_argument("Incorrect");

  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      tmp.matrix_[k][i] = matrix_[i][k];
    }
  }
  return tmp;
}

// CalcComplements
S21Matrix S21Matrix::CalcComplements() {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0 || rows_ != cols_)
    throw std::invalid_argument("Incorrect");
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1;
  } else {
    S21Matrix temp(rows_ - 1, rows_ - 1);
    int sign = -1;
    for (int i = 0; i < rows_; ++i) {
      for (int k = 0; k < rows_; ++k) {
        temp.Copy(*this, i, k);
        res.matrix_[i][k] = temp.RecDet();
        if ((i + k) % 2) res.matrix_[i][k] *= sign;
      }
    }
  }
  return res;
}

// Determinant
double S21Matrix::Determinant() {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || rows_ != cols_)
    throw std::invalid_argument("Incorrect");
  return this->RecDet();
}

double S21Matrix::RecDet() {
  double res = 0;
  if (rows_ == 1) {
    res = matrix_[0][0];
  } else {
    S21Matrix temp(rows_ - 1, rows_ - 1);
    int sign = 1;
    for (int k = 0; k < rows_; ++k) {
      if (matrix_[0][k] != 0) {
        temp.Copy(*this, 0, k);
        res += sign * matrix_[0][k] * temp.RecDet();
      }
      sign = -sign;
    }
  }
  return res;
}

void S21Matrix::Copy(const S21Matrix &other, int x, int y) {
  if (!matrix_ || !*matrix_ || !other.matrix_ || !*other.matrix_ ||
      rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0)
    throw std::invalid_argument("Incorrect");
  for (int i = 0, m = 0; i < rows_; i++, m++) {
    if (m == x) m++;
    for (int k = 0, n = 0; k < rows_; k++, n++) {
      if (n == y) n++;
      matrix_[i][k] = other.matrix_[m][n];
    }
  }
}

// InverseMatrix
S21Matrix S21Matrix::InverseMatrix() {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || rows_ != cols_)
    throw std::invalid_argument("Incorrect");
  double det = this->RecDet();
  if (det == 0) throw std::overflow_error("Divide by zero exception");
  S21Matrix temp(std::move(CalcComplements().Transpose()));
  temp *= 1.0 / det;
  return temp;
}

// OPERATORS

// operator+ Addition of two matrices
S21Matrix S21Matrix::operator+(const S21Matrix &right) {
  if (!matrix_ || !*matrix_ || !right.matrix_ || !*right.matrix_ ||
      rows_ != right.rows_ || cols_ != right.cols_ || rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Incorrect");
  S21Matrix tmp(rows_, cols_);

  for (int k = 0; k < rows_; ++k) {
    for (int m = 0; m < cols_; ++m) {
      tmp.matrix_[k][m] = matrix_[k][m] + right.matrix_[k][m];
    }
  }
  return tmp;
}

// operator- Subtraction of one matrix from another
S21Matrix S21Matrix::operator-(const S21Matrix &right) {
  if (!matrix_ || !*matrix_ || !right.matrix_ || !*right.matrix_ ||
      rows_ != right.rows_ || cols_ != right.cols_ || rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Incorrect");
  S21Matrix tmp(rows_, cols_);

  for (int k = 0; k < rows_; ++k) {
    for (int m = 0; m < cols_; ++m) {
      tmp.matrix_[k][m] = matrix_[k][m] - right.matrix_[k][m];
    }
  }
  return tmp;
}

// operator* Matrix multiplication
S21Matrix S21Matrix::operator*(const S21Matrix &right) {
  if (!matrix_ || !*matrix_ || !right.matrix_ || !*right.matrix_ ||
      cols_ != right.rows_ || cols_ <= 0 || rows_ <= 0 || right.cols_ <= 0 ||
      right.rows_ <= 0)
    throw std::invalid_argument("Incorrect");
  S21Matrix tmp(rows_, right.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < right.cols_; k++) {
      for (int m = 0; m < cols_; m++) {
        tmp.matrix_[i][k] += matrix_[i][m] * right.matrix_[m][k];
      }
    }
  }
  return tmp;
}

// operator* Matrix multiplication by a number
S21Matrix S21Matrix::operator*(const double num) {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Incorrect");

  S21Matrix tmp(*this);
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      tmp.matrix_[i][k] *= num;
    }
  }
  return tmp;
}

// operator* Number multiplication by a matrix
S21Matrix operator*(const double num, const S21Matrix &right) {
  if (!right.matrix_ || !*right.matrix_ || right.rows_ <= 0 || right.cols_ <= 0)
    throw std::invalid_argument("Incorrect");

  S21Matrix tmp(right.rows_, right.cols_);
  for (int i = 0; i < right.rows_; i++) {
    for (int k = 0; k < right.cols_; k++) {
      tmp.matrix_[i][k] = right.matrix_[i][k] * num;
    }
  }
  return tmp;
}

// operator== Checks for matrices equality (EqMatrix)
bool S21Matrix::operator==(const S21Matrix &right) {
  return this->EqMatrix(right);
}

// operator= Assignment of values from one matrix to another one
S21Matrix &S21Matrix::operator=(const S21Matrix &right) {
  if (!matrix_ || !*matrix_ || !right.matrix_ || !*right.matrix_ ||
      right.rows_ <= 0 || right.cols_ <= 0)
    throw std::invalid_argument("Incorrect");

  if (this != &right) {
    if (rows_ != right.rows_ || cols_ != right.cols_) {
      Clear();
      *this = (std::move(S21Matrix(right.rows_, right.cols_)));
    }
    for (int k = 0; k < rows_; ++k) {
      for (int m = 0; m < cols_; ++m) {
        matrix_[k][m] = right.matrix_[k][m];
      }
    }
  }
  return *this;
}

// operator= Movement from one matrix to another one
S21Matrix &S21Matrix::operator=(S21Matrix &&right) {
  if (!right.matrix_ || !*right.matrix_ || right.rows_ <= 0 || right.cols_ <= 0)
    throw std::invalid_argument("Incorrect");

  if (this != &right) {
    Clear();
    rows_ = right.rows_;
    cols_ = right.cols_;
    matrix_ = right.matrix_;
    right.rows_ = 0;
    right.cols_ = 0;
    right.matrix_ = nullptr;
  }
  return *this;
}

// operator+= Addition assignment (SumMatrix)
S21Matrix &S21Matrix::operator+=(const S21Matrix &right) {
  this->SumMatrix(right);
  return *this;
}

// operator-= Difference assignment (SubMatrix)
S21Matrix &S21Matrix::operator-=(const S21Matrix &right) {
  this->SubMatrix(right);
  return *this;
}

// operator*= Multiplication assignment (MulMatrix)
S21Matrix &S21Matrix::operator*=(const S21Matrix &right) {
  this->MulMatrix(right);
  return *this;
}

// operator*= Multiplication assignment (MulNumber)
S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

// operator() Indexation by matrix elements (row, column)
double &S21Matrix::operator()(int i, int j) {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Incorrect");
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::out_of_range("Row or column out of range");

  return this->matrix_[i][j];
}

// Set and Get

int S21Matrix::GetRows() { return rows_; }
int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int row) {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Incorrect");
  if (row <= 0) throw std::out_of_range("Row out of range");

  if (row != rows_) {
    S21Matrix temp(row, cols_);
    int lim = row < rows_ ? row : rows_;
    for (int i = 0; i < lim; ++i) {
      for (int k = 0; k < cols_; ++k) {
        temp.matrix_[i][k] = matrix_[i][k];
      }
    }
    Clear();
    *this = std::move(temp);
  }
}

void S21Matrix::SetCols(int col) {
  if (!matrix_ || !*matrix_ || rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Incorrect");
  if (col <= 0) throw std::out_of_range("Column out of range");

  if (col != cols_) {
    S21Matrix temp(rows_, col);
    int lim = col < cols_ ? col : cols_;
    for (int i = 0; i < rows_; ++i) {
      for (int k = 0; k < lim; ++k) {
        temp.matrix_[i][k] = matrix_[i][k];
      }
    }
    Clear();
    *this = std::move(temp);
  }
}
