#ifndef _S21_MATRIX_S21_MATRIX_OOP_TEST_H_
#define _S21_MATRIX_S21_MATRIX_OOP_TEST_H_

#include <gtest/gtest.h>

#include <iostream>

#include "../s21_matrix_oop.h"

class S21MatrixTest : public testing::Test {
 protected:
  S21MatrixTest()
      : error(2, 3),
        m0(std::move(error)),
        m1(3, 2),
        m2(3, 2),
        m3(3, 3),
        m4(3, 3),
        m5(4, 4),
        m6(4, 4),
        m7(5, 5),
        m8(5, 5),
        m9(7, 2),
        m10(7, 2),
        m11(1, 1),
        r11(1, 1),
        r22(2, 2),
        r32(3, 2),
        r33(3, 3),
        r44(4, 4),
        r55(5, 5),
        r72(7, 2),
        r73(7, 3),
        arr1{2, -3, 4, -6, 6, 23, 45, 23, 4, 5, 34, 5, 1, 9},
        arr2{-6, 3, -15, 6, 5.3, 5, 5, 4, 7, 3, 1, 1, 51, 21},
        arr3{8, -6, 19, -12, 6 - 5.3, 18, 40, 19, -3, 2, 33, 4, -50, -12},
        kEps(1e-7) {}
  // void TearDown() override {}
  void SetUp() override {
    m0.Fill();
    m1.Fill();
    m2.Fill();
    m3.Fill();
    m4.Fill();
    m5.Fill();
    m6.Fill();
    m7.Fill();
    m8.Fill();
    m9.FillArr(arr1, 14);
    m10.FillArr(arr2, 14);
    m11(0, 0) = 9.25;
    r72.FillArr(arr3, 14);
  }
  void Check(S21Matrix &m, S21Matrix &r) const {
    for (int i = 0; i < m.GetRows(); ++i) {
      for (int k = 0; k < m.GetCols(); ++k) {
        EXPECT_NEAR(m(i, k), r(i, k), kEps);
      }
    }
  }
  // void TearDown() override {}
  S21Matrix error;
  S21Matrix m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11;
  S21Matrix r11, r22, r32, r33, r44, r55, r72, r73;
  double arr1[14], arr2[14], arr3[14];
  const double kEps;
};
#endif  //_S21_MATRIX_S21_MATRIX_OOP_TEST_H_
