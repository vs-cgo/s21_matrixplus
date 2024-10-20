#ifndef _S21_MATRIX_S21_MATRIX_OOP_H_
#define _S21_MATRIX_S21_MATRIX_OOP_H_
#include <iostream>

class S21Matrix {
  friend std::ostream &operator<<(std::ostream &, const S21Matrix &);
  friend S21Matrix operator*(const double num, const S21Matrix &right);

 public:
  S21Matrix();
  S21Matrix(int, int);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &right);
  S21Matrix operator-(const S21Matrix &right);
  S21Matrix operator*(const S21Matrix &right);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &right);
  S21Matrix &operator=(const S21Matrix &);
  S21Matrix &operator=(S21Matrix &&);
  S21Matrix &operator+=(const S21Matrix &right);
  S21Matrix &operator-=(const S21Matrix &right);
  S21Matrix &operator*=(const S21Matrix &right);
  S21Matrix &operator*=(const double num);
  double &operator()(int i, int j);

  void Clear();
  bool IsCorrect();
  void Fill(int x = 0);
  void FillArr(double *, int);

  int GetRows();
  int GetCols();
  void SetRows(int);
  void SetCols(int);

 protected:
  double RecDet();
  void Copy(const S21Matrix &, int x, int y);

 private:
  double **matrix_;
  int rows_;
  int cols_;
};

#endif  //_S21_MATRIX_S21_MATRIX_OOP_H_
