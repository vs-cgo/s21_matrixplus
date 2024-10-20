#include "s21_matrix_oop_test.h"

#include <gtest/gtest.h>

#include <iostream>

#include "../s21_matrix_oop.h"

TEST(Constructor, Default) {
  S21Matrix p;
  ASSERT_TRUE(p.IsCorrect());
  EXPECT_EQ(5, p.GetRows());
  EXPECT_EQ(5, p.GetCols());
}

TEST(Constructor, WithParametrs) {
  S21Matrix p(6, 3);
  ASSERT_TRUE(p.IsCorrect());
  EXPECT_EQ(6, p.GetRows());
  EXPECT_EQ(3, p.GetCols());

  S21Matrix p2(1, 1);
  ASSERT_TRUE(p2.IsCorrect());
  EXPECT_EQ(1, p2.GetRows());
  EXPECT_EQ(1, p2.GetCols());

  S21Matrix p3(100, 100);
  ASSERT_TRUE(p3.IsCorrect());
  EXPECT_EQ(100, p3.GetRows());
  EXPECT_EQ(100, p3.GetCols());

  // EXPECT_ANY_THROW(S21Matrix e(0, 11));
  // ASSERT_THROW(S21Matrix e(-1, 1), std::out_of_range);
}

TEST(Constructor, Assignment) {
  S21Matrix t(7, 5);
  ASSERT_TRUE(t.IsCorrect());
  t.Fill();

  S21Matrix e(t), e2 = t;
  ASSERT_TRUE(e.IsCorrect());
  EXPECT_EQ(7, e.GetRows());
  EXPECT_EQ(5, e.GetCols());

  ASSERT_TRUE(e2.IsCorrect());
  EXPECT_EQ(7, e2.GetRows());
  EXPECT_EQ(5, e2.GetCols());

  EXPECT_TRUE(t.EqMatrix(e));
  EXPECT_TRUE(t == e);
  EXPECT_TRUE(t.EqMatrix(e2));
  EXPECT_TRUE(t == e2);
  S21Matrix out(std::move(t));
  // ASSERT_THROW(S21Matrix t2(t), std::out_of_range);
}

TEST(Constructor, Movement) {
  S21Matrix t(7, 5);
  ASSERT_TRUE(t.IsCorrect());
  t.Fill();

  S21Matrix e(std::move(t));
  ASSERT_TRUE(e.IsCorrect());
  ASSERT_FALSE(t.IsCorrect());
  EXPECT_EQ(7, e.GetRows());
  EXPECT_EQ(5, e.GetCols());
  // ASSERT_THROW(e.EqMatrix(t), std::invalid_argument);
  // ASSERT_THROW(S21Matrix e2(std::move(t)), std::invalid_argument);
}

TEST_F(S21MatrixTest, EqMatrix) {
  ASSERT_TRUE(m0.IsCorrect());
  ASSERT_TRUE(m1.IsCorrect());
  ASSERT_TRUE(m2.IsCorrect());

  EXPECT_FALSE(m0.EqMatrix(m1));
  EXPECT_FALSE(m1 == m0);

  EXPECT_TRUE(m1.EqMatrix(m1));
  EXPECT_TRUE(m1 == m1);

  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_TRUE(m2 == m1);
  m2(0, 1) = 2 + kEps / 2;
  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_TRUE(m2 == m1);

  m2(0, 1) = 2 + kEps;
  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_TRUE(m2 == m1);

  m2(0, 1) = 2 + kEps + kEps / 8;
  EXPECT_FALSE(m1.EqMatrix(m2));
  EXPECT_FALSE(m2 == m1);
}

TEST_F(S21MatrixTest, SumMatrix) {
  ASSERT_TRUE(m0.IsCorrect());
  ASSERT_TRUE(m1.IsCorrect());
  ASSERT_TRUE(m2.IsCorrect());
  ASSERT_TRUE(r32.IsCorrect());

  // ASSERT_THROW(error.SumMatrix(m0), std::invalid_argument);
  // ASSERT_THROW(error + m0, std::invalid_argument);
  // ASSERT_THROW(m1.SumMatrix(m0), std::invalid_argument);
  {
    double a[] = {3, 5, -17, -1, 0, 10}, b[] = {-4, 3, -15, -5, -7, 0},
           r[] = {-1, 8, -32, -6, -7, 10};
    m1.FillArr(a, 6);
    m2.FillArr(b, 6);
    r32.FillArr(r, 6);
    S21Matrix c(m1), ans = m1 + m2;
    c.SumMatrix(m2);
    m1 += m2;
    Check(m1, r32);
    Check(c, r32);
    Check(ans, r32);
  }
  {
    double a[] = {1, 4, 2, 5, 3, 6, 33, -3, 3},
           b[] = {1, -1, 1, 2, 3, 4, 14, 24, -7},
           r[] = {2, 3, 3, 7, 6, 10, 47, 21, -4};
    m3.FillArr(a, 9);
    m4.FillArr(b, 9);
    r33.FillArr(r, 9);

    S21Matrix c(m3), ans = m3 + m4;
    c.SumMatrix(m4);
    m3 += m4;
    Check(m3, r33);
    Check(c, r33);
    Check(ans, r33);
  }
}

TEST_F(S21MatrixTest, SubMatrix) {
  // ASSERT_THROW(error.SubMatrix(m0), std::invalid_argument);
  // ASSERT_THROW(m1.SubMatrix(m0), std::invalid_argument);
  // ASSERT_THROW(m0 - m1, std::invalid_argument);
  // ASSERT_THROW(m0 -= m1, std::invalid_argument);

  ASSERT_TRUE(m1.IsCorrect());
  ASSERT_TRUE(m2.IsCorrect());
  ASSERT_TRUE(m3.IsCorrect());
  ASSERT_TRUE(m4.IsCorrect());
  ASSERT_TRUE(m9.IsCorrect());
  ASSERT_TRUE(m10.IsCorrect());
  ASSERT_TRUE(r32.IsCorrect());
  ASSERT_TRUE(r33.IsCorrect());
  ASSERT_TRUE(r72.IsCorrect());

  {
    double a[] = {3, 5, -17, -1, 0, 10}, b[] = {-4, 3, -15, -5, -7, 0},
           r[] = {7, 2, -2, 4, 7, 10};
    m1.FillArr(a, 6);
    m2.FillArr(b, 6);
    r32.FillArr(r, 6);

    S21Matrix c(m1), ans = m1 - m2;
    c -= m2;
    m1.SubMatrix(m2);
    Check(m1, r32);
    Check(c, r32);
    Check(ans, r32);
  }
  {
    double a[] = {1, 4, 2, 5, 3, 6, 33, -3, 3},
           b[] = {1, -1, 1, 2, 3, 4, 14, 24, -7},
           r[] = {0, 5, 1, 3, 0, 2, 19, -27, 10};
    m3.FillArr(a, 9);
    m4.FillArr(b, 9);
    r33.FillArr(r, 9);

    S21Matrix c(m3), ans = m3 - m4;
    c -= m4;
    m3.SubMatrix(m4);
    Check(m3, r33);
    Check(c, r33);
    Check(ans, r33);
  }
  {
    S21Matrix c(m9), ans = m9 - m10;
    ASSERT_TRUE(ans.IsCorrect());
    ASSERT_TRUE(c.IsCorrect());
    c -= m10;
    m9.SubMatrix(m10);

    Check(m9, r72);
    Check(c, r72);
    Check(ans, r72);
  }
}

TEST_F(S21MatrixTest, MulNumber) {
  // ASSERT_THROW(error.MulNumber(4), std::invalid_argument);
  // ASSERT_THROW(error *= 4, std::invalid_argument);
  // ASSERT_THROW(error * 4, std::invalid_argument);
  // ASSERT_THROW(4 * error, std::invalid_argument);

  {
    double a[] = {2, 4, 6, 8, 10, 12};
    S21Matrix ans = m1 * 2, ans2 = 2 * m1;
    m1.MulNumber(2);
    m2 *= 2;
    r32.FillArr(a, 6);
    Check(m1, r32);
    Check(m2, r32);
    Check(ans, r32);
    Check(ans2, r32);
  }
  {
    double a[] = {9, 11, 17, 12, 13, 22, 15, 15, 27},
           r[] = {13.5, 16.5, 25.5, 18, 19.5, 33, 22.5, 22.5, 40.5};
    m3.FillArr(a, 9);
    m4.FillArr(a, 9);
    r33.FillArr(r, 9);
    S21Matrix ans = m3 * 1.5, ans2 = 1.5 * m4;
    m3.MulNumber(1.5);
    m4 *= 1.5;
    Check(m3, r33);
    Check(m4, r33);
    Check(ans, r33);
    Check(ans2, r33);
  }
  {
    double a[] = {176,  154,  36,  78, -20, 94,   -21, -65,  -7, -4,
                  -30,  -55,  72,  37, -29, -117, 6,   55,   -8, -42,
                  -112, -322, -19, 79, 285, 16,   -94, -515, 108},
           r[] = {528,  462,  108, 234, -60, 282,  -63,  -195,  -21, -12,
                  -90,  -165, 216, 111, -87, -351, 18,   165,   -24, -126,
                  -336, -966, -57, 237, 855, 48,   -282, -1545, 324};
    m7.FillArr(a, 25);
    m8.FillArr(a, 25);
    r55.FillArr(r, 25);
    S21Matrix ans = 3 * m7, ans2 = m8 * 3;
    m7.MulNumber(3);
    m8 *= 3;
    Check(m7, r55);
    Check(m8, r55);
    Check(ans, r55);
    Check(ans2, r55);
  }
}

TEST_F(S21MatrixTest, MulMatrix) {
  // ASSERT_THROW(m0.MulMatrix(error), std::invalid_argument);
  // ASSERT_THROW(m0 *= m0, std::invalid_argument);
  // ASSERT_THROW(m0 * m0, std::invalid_argument);

  {
    double r[] = {22, 28, 49, 64};
    r22.FillArr(r, 4);
    S21Matrix ans1 = m0 * m1, ans2(m0), ans3(m0);
    ans2 *= m1;
    ans3.MulMatrix(m1);
    Check(ans1, r22);
    Check(ans2, r22);
    Check(ans3, r22);
  }
  {
    double r[] = {9, 12, 15, 19, 26, 33, 29, 40, 51};
    r33.FillArr(r, 9);
    S21Matrix ans1 = m1 * m0, ans2(m1), ans3(m1);
    ans2 *= m0;
    ans3.MulMatrix(m0);
    Check(ans1, r33);
    Check(ans2, r33);
    Check(ans3, r33);
  }
  {
    double r[] = {-10, -11, -12, -20, -22, -24, 98,  127, 156, 137, 205,
                  273, 24,  33,  42,  54,  93,  132, 37,  47,  57};
    r73.FillArr(r, 21);
    S21Matrix ans1 = m9 * m0, ans2(m9), ans3(m9);
    ans2 *= m0;
    ans3.MulMatrix(m0);
    Check(ans1, r73);
    Check(ans2, r73);
    Check(ans3, r73);
  }
  {
    double a[] = {5, 8, -4, 6, 9, -5, 4, 7, -3},
           b[] = {3, 2, 5, 4, -1, 3, 9, 6, 5},
           r[] = {11, -22, 29, 9, -27, 32, 13, -17, 26};
    m3.FillArr(a, 9);
    m4.FillArr(b, 9);
    r33.FillArr(r, 9);
    S21Matrix ans1 = m3 * m4, ans2(m3), ans3(m3);
    ans2 *= m4;
    ans3.MulMatrix(m4);
    Check(ans1, r33);
    Check(ans2, r33);
    Check(ans3, r33);
  }
}
TEST_F(S21MatrixTest, Transpose) {
  // ASSERT_THROW(error.Transpose(), std::invalid_argument);
  {
    double r[] = {1, 4, 2, 5, 3, 6};
    S21Matrix m1 = m0.Transpose(), ans(3, 2);
    ans.FillArr(r, 6);
    Check(m1, ans);
  }
  {
    double r[] = {4, 2, 7, 5, 11, 1}, a[] = {4, 5, 2, 11, 7, 1};
    S21Matrix ans(2, 3);
    ans.FillArr(r, 6);
    m1.FillArr(a, 6);
    m0 = m1.Transpose();
    Check(m0, ans);
  }
  {
    double r[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
    r33.FillArr(r, 9);
    m4 = m3.Transpose();
    Check(m4, r33);
  }
  {
    double a[] = {23, -54, 4, 7, 3, 5, 24, 4, 0, 19, -1, 45, 24, 4.3},
           r[] = {23, 4, 3, 24, 0, -1, 24, -54, 7, 5, 4, 19, 45, 4.3};
    S21Matrix ans(2, 7), res(2, 7);
    ans.FillArr(r, 14);
    m9.FillArr(a, 14);
    res = m9.Transpose();
    Check(res, ans);
  }
}

TEST_F(S21MatrixTest, CalcComplements) {
  // ASSERT_THROW(error.CalcComplements(), std::invalid_argument);
  // ASSERT_THROW(m0.CalcComplements(), std::invalid_argument);
  {
    double r[] = {-3, 6, -3, 6, -12, 6, -3, 6, -3};
    S21Matrix c(m3.CalcComplements());
    r33.FillArr(r, 9);
    Check(c, r33);
  }
  {
    double a[] = {1, 2, 3, 0, 4, 2, 5, 2, 1},
           r[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
    m3.FillArr(a, 9);
    r33.FillArr(r, 9);
    S21Matrix c = m3.CalcComplements();
    Check(c, r33);
  }
  {
    double a[] = {1,  2,  3, 4, 5, 6, 7, 8,  9,  10, 11, 12, 13,
                  14, 15, 0, 0, 0, 0, 0, 21, 22, 23, 24, 25};
    m7.FillArr(a, 25);
    S21Matrix c(m7.CalcComplements());
    Check(c, r55);
  }
  {
    m11 = m11.CalcComplements();
    r11(0, 0) = 1;
    Check(m11, r11);
  }
  {
    double a[] = {1,  2, 4,   -4, 3,  6, 7,   8,  9, 8,   1,  12, 13,
                  14, 1, -16, -1, 18, 1, -18, 21, 2, -23, 24, 23},
           r[] = {-43992, 6960,   -6360,  768,   32400, 24388, -9450,
                  8136,   -266,   -13032, -5876, 7320,  -3360, -80,
                  1452,   -12812, -1974,  -360,  2290,  9120,  -12516,
                  516,    -2136,  1788,   9060};
    m7.FillArr(a, 25);
    r55.FillArr(r, 25);
    S21Matrix c = m7.CalcComplements();
    Check(c, r55);
  }
  {
    double a[] = {5.3245, 23.21, -2,    -23.2344, 23.23,  45.345, 345.342,
                  345.12, 0,     7.345, 35.345,   34.456, 45,     4,
                  -3,     -7,    -45,   45.3,     4.040,  11,     46,
                  2,      45,    -7.36, 9.135},
           r[] = {1112035.9736539,  1878468.6445654,  -2324675.6714772,
                  10678193.2543245, 14043931.6355878, -587626.6401000,
                  -139037.5889131,  654447.6229888,   -2901594.2436183,
                  -2572192.2326329, 5205871.5823668,  4404293.3633876,
                  -5757433.7013937, 37390408.4746694, 31308072.6240436,
                  20254.2685645,    181232.5686691,   -407870.2890195,
                  10737323.3815713, 10518522.3429599, -670132.4798636,
                  -3436921.0386299, 3985721.9630647,  -25471434.1928689,
                  -21545544.0804576};
    m7.FillArr(a, 25);
    r55.FillArr(r, 25);
    S21Matrix c = m7.CalcComplements();
    Check(c, r55);
  }
}

TEST_F(S21MatrixTest, Determinant) {
  // ASSERT_THROW(error.Determinant(), std::invalid_argument);

  {
    double res = m3.Determinant();
    EXPECT_NEAR(res, 0, kEps);
  }
  {
    double res = m4.Determinant();
    EXPECT_NEAR(res, 0, kEps);
  }
  {
    double res = m11.Determinant();
    EXPECT_NEAR(res, m11(0, 0), kEps);
  }
  {
    double a[] = {1,  2,  3,  4,  -5, 6,  -4, 8,  9,  8,  11, 12, 13,
                  14, 13, 16, 17, 18, 12, 18, 21, 22, 23, 24, 23},
           res = 0, ans = 12320;
    m7.FillArr(a, 25);
    res = m7.Determinant();
    EXPECT_NEAR(res, ans, kEps);
  }
  {
    double a[] = {-10, 12, 53, 4, 3, 2, 2, 7, 1}, res = 0, ans = 1276;
    m3.FillArr(a, 9);
    res = m3.Determinant();
    EXPECT_NEAR(res, ans, kEps);
  }
  {
    double a[] = {5.3245, 23.21, -2,    -23.2344, 23.23,  45.345,   345.342,
                  345.12, 0,     7.345, 35.345,   34.456, 45,       4,
                  -3,     -7,    -45,   45.3,     4.040,  0.000001, 46,
                  2,      45,    -7.36, 9.135},
           res = 0, ans = 16605027.417426362;
    m7.FillArr(a, 25);
    res = m7.Determinant();
    EXPECT_NEAR(res, ans, kEps);
  }
  {
    double a[] = {5, 23, -2, -23, 23, 45, 345, 345, 0, 7,  35, 34, 45,
                  4, -3, -7, -45, 45, 4,  1,   46,  2, 45, -7, 9.5},
           res = 0, ans = 10836156;
    m7.FillArr(a, 25);
    res = m7.Determinant();
    EXPECT_NEAR(res, ans, kEps);
  }
  {
    double a[] = {5.24,  23.14, -2.134, 345.34, 14.13,
                  15.15, 64.24, -86.42, 13.35},
           res = 0, ans = -10687.663084;
    m3.FillArr(a, 9);
    res = m3.Determinant();
    EXPECT_NEAR(res, ans, kEps);
  }
}

TEST_F(S21MatrixTest, InverseMatrix) {
  // ASSERT_THROW(error.InverseMatrix(), std::invalid_argument);
  // ASSERT_THROW(m0.InverseMatrix(), std::invalid_argument);
  // ASSERT_THROW(m3.InverseMatrix(), std::overflow_error);

  {
    m11(0, 0) = -4;
    r11(0, 0) = -0.25;
    S21Matrix ans = m11.InverseMatrix();
    Check(ans, r11);
  }
  {
    m11(0, 0) = 7;
    r11(0, 0) = 1.0 / 7.0;
    S21Matrix ans = m11.InverseMatrix();
    Check(ans, r11);
  }
  {
    double a[] = {2, 5, 7, 6, 3, 4, 5, -2, -3},
           r[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
    m3.FillArr(a, 9);
    r33.FillArr(r, 9);
    m4 = m3.InverseMatrix();
    Check(m4, r33);
  }
  {
    double a[] = {2, 5, 7, 6, 3, 4, 5, -2, -3},
           r[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
    m3.FillArr(a, 9);
    r33.FillArr(r, 9);
    m4 = m3.InverseMatrix();
    Check(m4, r33);
  }
  {
    double a[] = {1,  2, 4,   -4, 3,  6, 7,   8,  9, 8,   1,  12, 13,
                  14, 1, -16, -1, 18, 1, -18, 21, 2, -23, 24, 23},
           r[] = {-1.1392169, 0.6315517,  -0.1521649, -0.3317796, -0.3241144,
                  0.1802362,  -0.2447172, 0.1895587,  -0.0511187, 0.0133623,
                  -0.1646986, 0.2106899,  -0.0870106, -0.0093226, -0.0553139,
                  0.0198881,  -0.0068883, -0.0020717, 0.0593018,  0.0463021,
                  0.8390305,  -0.3374767, 0.0376010,  0.2361715,  0.2346178};
    m7.FillArr(a, 25);
    r55.FillArr(r, 25);
    m8 = m7.InverseMatrix();
    Check(m8, r55);
  }
  {
    double a[] = {1, 2, 4, 3, 3, 5, 2, 4, 4},
           r[] = {-0.6666667, 0.6666667, -0.1666667, -0.1666667, -0.3333333,
                  0.5833333,  0.5000000, -0.0000000, -0.2500000};
    m3.FillArr(a, 9);
    r33.FillArr(r, 9);
    m4 = m3.InverseMatrix();
    Check(m4, r33);
  }
}

TEST_F(S21MatrixTest, OperatorCopy) {
  // ASSERT_THROW(m10 = error, std::invalid_argument);

  m3 = m5;
  EXPECT_EQ(4, m3.GetRows());
  EXPECT_EQ(4, m3.GetCols());
  Check(m3, m5);

  m2 *= 2;
  m1 = m2;
  Check(m1, m2);
}

TEST_F(S21MatrixTest, OperatorMove) {
  // ASSERT_THROW(m10 = std::move(error), std::invalid_argument);

  m5 = m5;
  EXPECT_TRUE(m5.IsCorrect());

  m3 = std::move(m5);
  EXPECT_FALSE(m5.IsCorrect());
}

TEST_F(S21MatrixTest, Indexation) {
  // ASSERT_THROW(error(1, 2), std::invalid_argument);
  // ASSERT_THROW(m1(-1, 1), std::out_of_range);
  // ASSERT_THROW(m1(2, 3), std::out_of_range);

  EXPECT_EQ(1, m1(0, 0));
  EXPECT_EQ(6, m1(2, 1));
}

TEST_F(S21MatrixTest, SetRows) {
  // ASSERT_THROW(error.SetRows(3), std::invalid_argument);
  // ASSERT_THROW(m1.SetRows(0), std::out_of_range);
  // ASSERT_THROW(m1.SetRows(-2), std::out_of_range);

  m1.SetRows(3);
  EXPECT_EQ(3, m1.GetRows());

  m1.SetRows(5);
  EXPECT_EQ(5, m1.GetRows());
  EXPECT_EQ(0, m1(4, 0));

  m1.SetRows(100);
  EXPECT_EQ(100, m1.GetRows());
  EXPECT_EQ(0, m1(99, 0));
}

TEST_F(S21MatrixTest, SetCols) {
  // ASSERT_THROW(error.SetCols(3), std::invalid_argument);
  // ASSERT_THROW(m1.SetCols(0), std::out_of_range);
  // ASSERT_THROW(m1.SetCols(-2), std::out_of_range);

  m1.SetCols(2);
  EXPECT_EQ(2, m1.GetCols());

  m1.SetCols(20);
  EXPECT_EQ(20, m1.GetCols());
  EXPECT_EQ(0, m1(1, 19));

  m1.SetCols(100);
  EXPECT_EQ(100, m1.GetCols());
  EXPECT_EQ(0, m1(0, 99));

  m1.SetCols(1);
  EXPECT_EQ(1, m1.GetCols());
  EXPECT_EQ(1, m1(0, 0));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
